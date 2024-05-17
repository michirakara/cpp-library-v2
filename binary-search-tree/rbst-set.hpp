/**
 * @file rbst-set.hpp
 * @author michirakara
 * @brief RBST ordered set
 * @date 2024-05-14
 */

#include "../algebra/concepts.hpp"
#include "../internal/dummy.hpp"
#include <algorithm>
#include <array>
#include <cassert>
#include <iostream>
#include <ranges>
#include <utility>
#include <vector>

namespace libmcr {

template <class S> consteval auto to_val() {
    if constexpr (monoid<S>)
        return typename S::value_type{};
    else
        return S{};
}
/**
 * @brief RBST ordered set
 * Sの型に応じて区間クエリ機能をon/offする
 *
 * @tparam S
 * algebra/concepts.hppにあるmonoidを満たす型が与えられた場合、区間クエリ機能をつける
 * そうでない場合、区間クエリ機能をつけないsetが生成される
 * @tparam DEFAULT_POOL_SIZE デフォルトのメモリプールの長さ
 * 指定されない場合は $10000000$ になる
 */
template <class S, size_t DEFAULT_POOL_SIZE = 10000000> class rbst_set {
  protected:
    using val_t = decltype(to_val<S>());

    struct node_t {
        val_t val;
        [[no_unique_address]] std::conditional_t<monoid<S>, val_t,
                                                 internal::dummy> product;
        node_t *lch = nullptr, *rch = nullptr;
        size_t siz = 1;
        node_t() = default;
        node_t(val_t value) {
            val = value;
            if constexpr (monoid<S>)
                product = value;
        }
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

    node_t *make_ptr(val_t val) {
        if (pool_idx < DEFAULT_POOL_SIZE) {
            pool[pool_idx] = node_t(val);
            return &pool[pool_idx++];
        }
        pool.push_back(node_t(val));
        return &pool[pool_idx++];
    }

    size_t get_product(node_t *node)
        requires monoid<S>
    {
        return !node ? S().e() : node->product;
    }

    size_t get_size(node_t *node) { return !node ? 0 : node->siz; }

    node_t *update(node_t *node) {
        node->siz = get_size(node->lch) + get_size(node->rch) + 1;
        if constexpr (monoid<S>)
            node->product = S().op(S().op(get_product(node->lch), node->val),
                                   get_product(node->rch));
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
    size_t lower_bound(node_t *node, val_t val) {
        if (!node)
            return 0;
        if (val <= node->val) {
            return lower_bound(node->lch, val);
        } else {
            return get_size(node->lch) + 1 + lower_bound(node->rch, val);
        }
    }
    size_t upper_bound(node_t *node, val_t val) {
        if (!node)
            return 0;
        if (val < node->val) {
            return upper_bound(node->lch, val);
        } else {
            return get_size(node->lch) + 1 + upper_bound(node->rch, val);
        }
    }
    val_t get_val(node_t *node, size_t index) {
        if (index < get_size(node->lch)) {
            return get_val(node->lch, index);
        } else if (index == get_size(node->lch)) {
            return node->val;
        } else {
            return get_val(node->rch, index - get_size(node->lch) - 1);
        }
    }
    node_t *insert(node_t *node, val_t val) {
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
    node_t *erase_by_val(node_t *node, val_t val) {
        size_t index = lower_bound(node, val);
        return erase_by_index(node, index);
    }

    val_t prod(node_t *node, size_t l, size_t r)
        requires monoid<S>
    {
        if (!node)
            return S().e();
        if (l == 0 && r == get_size(node->lch) + 1 + get_size(node->rch))
            return node->product;
        val_t ret = S().e();
        if (l < get_size(node->lch)) {
            ret = S().op(ret,
                         prod(node->lch, l, std::min(get_size(node->lch), r)));
        }
        if (l <= get_size(node->lch) && get_size(node->lch) < r) {
            ret = S().op(ret, node->val);
        }
        if (get_size(node->lch) + 1 < r) {
            ret = S().op(ret, prod(node->rch,
                                   std::max(l, get_size(node->lch) + 1) -
                                       (get_size(node->lch) + 1),
                                   r - (get_size(node->lch) + 1)));
        }
        return ret;
    }

  public:
    /**
     * @brief Construct a new rbst_set object
     *
     */
    rbst_set() : pool(DEFAULT_POOL_SIZE) {}
    /**
     * @brief Construct a new rbst_set object
     *
     * @param init
     * setをinitで初期化する
     */
    rbst_set(std::vector<val_t> init) : pool(DEFAULT_POOL_SIZE) {
        for (val_t i : init)
            insert(i);
    }
    /**
     * @brief `val`を追加する
     *
     * @param val
     */
    void insert(val_t val) { top_node = insert(top_node, val); }
    /**
     * @brief `rbst[index]`にある要素を削除する
     *
     * @param index 0-indexed
     */
    void erase_by_index(size_t index) {
        assert(0 <= index && index < top_node->siz);
        top_node = erase_by_index(top_node, index);
    }
    /**
     * @brief `val`をsetから削除する
     * 存在しない場合はエラーになる
     *
     * @param val
     */
    void erase_by_val(val_t val) {
        assert(includes(val));
        top_node = erase_by_val(top_node, val);
    }
    /**
     * @brief 小さい方から`index`番目の要素を返す
     *
     * @param index 0-indexed
     * @return val_t
     */
    val_t operator[](size_t index) {
        assert(0 <= index && index < top_node->siz);
        return get_val(top_node, index);
    }
    /**
     * @brief setの長さを返す
     *
     * @return size_t
     */
    size_t size() { return top_node ? top_node->siz : 0; }
    /**
     * @brief 要素が`val`以上である最小のindexを返す
     * 存在しない場合はsize()を返す
     *
     * @param val
     * @return size_t
     */
    size_t lower_bound(val_t val) { return lower_bound(top_node, val); }
    /**
     * @brief 要素が`val`より大きい最小のindexを返す
     *
     * @param val
     * @return size_t
     */
    size_t upper_bound(val_t val) { return upper_bound(top_node, val); }
    /**
     * @brief `val`がsetに存在するなら`true`、そうでなければ`false`を返す
     *
     * @param val
     * @return true
     * @return false
     */
    bool includes(val_t val) {
        size_t tmp = lower_bound(val);
        return tmp < size() ? operator[](tmp) == val : false;
    }
    /**
     * @brief op[l,r)を返す
     * Sにモノイドが与えられた場合のみ存在する関数
     *
     * @param l
     * @param r
     * @return val_t
     */
    val_t prod(size_t l, size_t r) { return prod(top_node, l, r); }
};

} // namespace libmcr