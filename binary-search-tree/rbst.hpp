#include "../algebra/concepts.hpp"
#include <algorithm>
#include <array>
#include <cassert>
#include <iostream>
#include <ranges>
#include <utility>
#include <vector>

namespace libmcr {
template <class S, size_t DEFAULT_POOL_SIZE = 10000000> class rbst {
  protected:
    struct node_t {
        S val, product;
        node_t *lch = nullptr, *rch = nullptr;
        size_t siz = 1;
        node_t() = default;
        node_t(S val) : val(val), product(val) {}
    };
    unsigned int xorshift128() {
        static unsigned int x = 123456789, y = 362436069, z = 521288629,
                            w = time(0);
        unsigned int t = x ^ (x << 11);
        x = y;
        y = z;
        z = w;
        w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
        return w;
    }
    std::vector<node_t> pool;
    size_t pool_idx = 0;

    node_t *top_node = nullptr;

    node_t *make_ptr(S val) {
        if (pool_idx < DEFAULT_POOL_SIZE) {
            pool[pool_idx] = node_t(val);
            return &pool[pool_idx++];
        }
        pool.push_back(node_t(val));
        return &pool[pool_idx++];
    }

    size_t get_size(node_t *node) { return !node ? 0 : node->siz; }

    virtual node_t *update(node_t *node) {
        node->siz = get_size(node->lch) + get_size(node->rch) + 1;
        return node;
    }
    node_t *merge(node_t *l, node_t *r) {
        if (!l || !r)
            return !l ? r : l;

        unsigned int rand_num = xorshift128() % (l->siz + r->siz);
        if (rand_num < l->siz) {
            l->rch = merge(l->rch, r);
            return update(l);
        } else {
            r->lch = merge(l, r->lch);
            return update(r);
        }
    }
    std::pair<node_t *, node_t *> split(node_t *node, size_t index) {
        if (!node)
            return std::make_pair(nullptr, nullptr);

        if (index <= get_size(node->lch)) {
            std::pair<node_t *, node_t *> s = split(node->lch, index);
            node->lch = s.second;
            return std::make_pair(s.first, update(node));
        } else {
            std::pair<node_t *, node_t *> s =
                split(node->rch, index - get_size(node->lch) - 1);
            node->rch = s.first;
            return std::make_pair(update(node), s.second);
        }
    }
    size_t lower_bound(node_t *node, S val) {
        if (!node)
            return 0;
        if (val <= node->val) {
            return lower_bound(node->lch, val);
        } else {
            return get_size(node->lch) + 1 + lower_bound(node->rch, val);
        }
    }
    size_t upper_bound(node_t *node, S val) {
        if (!node)
            return 0;
        if (val < node->val) {
            return upper_bound(node->lch, val);
        } else {
            return get_size(node->lch) + 1 + upper_bound(node->rch, val);
        }
    }
    S get_val(node_t *node, size_t index) {
        if (index < get_size(node->lch)) {
            return get_val(node->lch, index);
        } else if (index == get_size(node->lch)) {
            return node->val;
        } else {
            return get_val(node->rch, index - get_size(node->lch) - 1);
        }
    }
    node_t *insert(node_t *node, S val) {
        if (!node) {
            return make_ptr(val);
        }
        size_t index = lower_bound(node, val);
        auto [l, r] = split(node, index);
        return merge(merge(l, make_ptr(val)), r);
    }
    node_t *erase_by_index(node_t *node, size_t index) {
        auto [l, tmp] = split(node, index);
        auto [to_del, r] = split(tmp, 1);
        return merge(l, r);
    }
    node_t *erase_by_val(node_t *node, S val) {
        size_t index = lower_bound(node, val);
        return erase_by_index(node, index);
    }

  public:
    rbst() : pool(DEFAULT_POOL_SIZE) {}
    rbst(std::vector<S> init) : pool(DEFAULT_POOL_SIZE) {
        for (S i : init)
            insert(i);
    }

    void insert(S val) { top_node = insert(top_node, val); }
    void erase_by_index(size_t index) {
        assert(0 <= index && index < top_node->siz);
        top_node = erase_by_index(top_node, index);
    }
    void erase_by_val(S val) {
        assert(includes(val));
        top_node = erase_by_val(top_node, val);
    }
    S operator[](size_t index) {
        assert(0 <= index && index < top_node->siz);
        return get_val(top_node, index);
    }
    size_t size() { return top_node ? top_node->siz : 0; }
    size_t lower_bound(S val) { return lower_bound(top_node, val); }
    size_t upper_bound(S val) { return upper_bound(top_node, val); }
    bool includes(S val) {
        size_t tmp = lower_bound(val);
        return tmp < size() ? operator[](tmp) == val : false;
    }
};
template <monoid S, size_t DEFAULT_POOL_SIZE = 10000000>
class rbst_query : public rbst<typename S::value_type, DEFAULT_POOL_SIZE> {
    using node_t =
        typename rbst<typename S::value_type, DEFAULT_POOL_SIZE>::node_t;
    typename S::value_type get_product(node_t *node) {
        return !node ? S().e() : node->product;
    }
    node_t *update(node_t *node) override {
        node->siz = this->get_size(node->lch) + this->get_size(node->rch) + 1;
        node->product = S().op(S().op(get_product(node->lch), node->val),
                               get_product(node->rch));
        return node;
    }
    typename S::value_type prod(node_t *node, size_t l, size_t r) {
        if (!node)
            return S().e();
        if (l == 0 &&
            r == this->get_size(node->lch) + 1 + this->get_size(node->rch))
            return node->product;
        typename S::value_type ret = S().e();
        if (l < this->get_size(node->lch)) {
            ret = S().op(ret, prod(node->lch, l,
                                   std::min(this->get_size(node->lch), r)));
        }
        if (l <= this->get_size(node->lch) && this->get_size(node->lch) < r) {
            ret = S().op(ret, node->val);
        }
        if (this->get_size(node->lch) + 1 < r) {
            ret = S().op(ret, prod(node->rch,
                                   std::max(l, this->get_size(node->lch) + 1) -
                                       (this->get_size(node->lch) + 1),
                                   r - (this->get_size(node->lch) + 1)));
        }
        return ret;
    }

  public:
    typename S::value_type prod(size_t l, size_t r) {
        return prod(this->top_node, l, r);
    }
};
} // namespace libmcr