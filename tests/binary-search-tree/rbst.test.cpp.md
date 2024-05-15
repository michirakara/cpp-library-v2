---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: algebra/concepts.hpp
    title: "monoid\u304B\u3069\u3046\u304B\u3092\u5224\u5B9A\u3059\u308Bconcept"
  - icon: ':heavy_check_mark:'
    path: binary-search-tree/rbst.hpp
    title: RBST ordered set
  - icon: ':heavy_check_mark:'
    path: internal/dummy.hpp
    title: "\u30C0\u30DF\u30FC\u69CB\u9020\u4F53"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/predecessor_problem
    links:
    - https://judge.yosupo.jp/problem/predecessor_problem
  bundledCode: "#line 1 \"tests/binary-search-tree/rbst.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/predecessor_problem\"\n\n#line 1 \"binary-search-tree/rbst.hpp\"\
    \n/**\n * @file rbst.hpp\n * @author michirakara\n * @brief RBST ordered set\n\
    \ * @date 2024-05-14\n */\n\n#line 1 \"algebra/concepts.hpp\"\n#include <concepts>\n\
    namespace libmcr {\n/**\n * @brief monoid\u304B\u3069\u3046\u304B\u3092\u5224\u5B9A\
    \u3059\u308Bconcept\n * `value_type`, `value_type op(value_type x,value_type x)`,\n\
    \ * `value_type e()`\u304C\u5B58\u5728\u3059\u308B\u304B\u5224\u5B9A\u3059\u308B\
    \n *\n * @tparam Monoid\n */\ntemplate <class Monoid>\nconcept monoid = requires(Monoid\
    \ a, Monoid::value_type x) {\n    { a.op(x, x) } -> std::same_as<typename Monoid::value_type>;\n\
    \    { a.e() } -> std::same_as<typename Monoid::value_type>;\n};\n} // namespace\
    \ libmcr\n#line 1 \"internal/dummy.hpp\"\nnamespace libmcr {\n/**\n * @brief \u30C0\
    \u30DF\u30FC\u69CB\u9020\u4F53\n *\n */\nstruct dummy {};\n} // namespace libmcr\n\
    #line 10 \"binary-search-tree/rbst.hpp\"\n#include <algorithm>\n#include <array>\n\
    #include <cassert>\n#include <iostream>\n#include <ranges>\n#include <utility>\n\
    #include <vector>\n\nnamespace libmcr {\n\ntemplate <class S> consteval auto to_val()\
    \ {\n    if constexpr (monoid<S>)\n        return typename S::value_type{};\n\
    \    else\n        return S{};\n}\n/**\n * @brief RBST ordered set\n * S\u306E\
    \u578B\u306B\u5FDC\u3058\u3066\u533A\u9593\u30AF\u30A8\u30EA\u6A5F\u80FD\u3092\
    on/off\u3059\u308B\n *\n * @tparam S\n * algebra/concepts.hpp\u306B\u3042\u308B\
    monoid\u3092\u6E80\u305F\u3059\u578B\u304C\u4E0E\u3048\u3089\u308C\u305F\u5834\
    \u5408\u3001\u533A\u9593\u30AF\u30A8\u30EA\u6A5F\u80FD\u3092\u3064\u3051\u308B\
    \n * \u305D\u3046\u3067\u306A\u3044\u5834\u5408\u3001\u533A\u9593\u30AF\u30A8\u30EA\
    \u6A5F\u80FD\u3092\u3064\u3051\u306A\u3044set\u304C\u751F\u6210\u3055\u308C\u308B\
    \n * @tparam DEFAULT_POOL_SIZE \u30C7\u30D5\u30A9\u30EB\u30C8\u306E\u30E1\u30E2\
    \u30EA\u30D7\u30FC\u30EB\u306E\u9577\u3055\n * \u6307\u5B9A\u3055\u308C\u306A\u3044\
    \u5834\u5408\u306F $10000000$ \u306B\u306A\u308B\n */\ntemplate <class S, size_t\
    \ DEFAULT_POOL_SIZE = 10000000> class rbst {\n  protected:\n    using val_t =\
    \ decltype(to_val<S>());\n\n    struct node_t {\n        val_t val;\n        [[no_unique_address]]\
    \ std::conditional_t<monoid<S>, val_t, dummy>\n            product;\n        node_t\
    \ *lch = nullptr, *rch = nullptr;\n        size_t siz = 1;\n        node_t() =\
    \ default;\n        node_t(val_t value) {\n            val = value;\n        \
    \    if constexpr (monoid<S>)\n                product = value;\n        }\n \
    \   };\n    unsigned int xorshift128() {\n        static unsigned int x = 123456789,\
    \ y = 362436069, z = 521288629,\n                            w = time(0);\n  \
    \      unsigned int t = x ^ (x << 11);\n        x = y;\n        y = z;\n     \
    \   z = w;\n        w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));\n        return w;\n\
    \    }\n    std::vector<node_t> pool;\n    size_t pool_idx = 0;\n\n    node_t\
    \ *top_node = nullptr;\n\n    node_t *make_ptr(val_t val) {\n        if (pool_idx\
    \ < DEFAULT_POOL_SIZE) {\n            pool[pool_idx] = node_t(val);\n        \
    \    return &pool[pool_idx++];\n        }\n        pool.push_back(node_t(val));\n\
    \        return &pool[pool_idx++];\n    }\n\n    size_t get_product(node_t *node)\n\
    \        requires monoid<S>\n    {\n        return !node ? S().e() : node->product;\n\
    \    }\n\n    size_t get_size(node_t *node) { return !node ? 0 : node->siz; }\n\
    \n    node_t *update(node_t *node) {\n        node->siz = get_size(node->lch)\
    \ + get_size(node->rch) + 1;\n        if constexpr (monoid<S>)\n            node->product\
    \ = S().op(S().op(get_product(node->lch), node->val),\n                      \
    \             get_product(node->rch));\n        return node;\n    }\n\n    node_t\
    \ *merge(node_t *l, node_t *r) {\n        if (!l || !r)\n            return !l\
    \ ? r : l;\n\n        unsigned int rand_num = xorshift128() % (l->siz + r->siz);\n\
    \        if (rand_num < l->siz) {\n            l->rch = merge(l->rch, r);\n  \
    \          return update(l);\n        } else {\n            r->lch = merge(l,\
    \ r->lch);\n            return update(r);\n        }\n    }\n    std::pair<node_t\
    \ *, node_t *> split(node_t *node, size_t index) {\n        if (!node)\n     \
    \       return std::make_pair(nullptr, nullptr);\n\n        if (index <= get_size(node->lch))\
    \ {\n            std::pair<node_t *, node_t *> s = split(node->lch, index);\n\
    \            node->lch = s.second;\n            return std::make_pair(s.first,\
    \ update(node));\n        } else {\n            std::pair<node_t *, node_t *>\
    \ s =\n                split(node->rch, index - get_size(node->lch) - 1);\n  \
    \          node->rch = s.first;\n            return std::make_pair(update(node),\
    \ s.second);\n        }\n    }\n    size_t lower_bound(node_t *node, val_t val)\
    \ {\n        if (!node)\n            return 0;\n        if (val <= node->val)\
    \ {\n            return lower_bound(node->lch, val);\n        } else {\n     \
    \       return get_size(node->lch) + 1 + lower_bound(node->rch, val);\n      \
    \  }\n    }\n    size_t upper_bound(node_t *node, val_t val) {\n        if (!node)\n\
    \            return 0;\n        if (val < node->val) {\n            return upper_bound(node->lch,\
    \ val);\n        } else {\n            return get_size(node->lch) + 1 + upper_bound(node->rch,\
    \ val);\n        }\n    }\n    val_t get_val(node_t *node, size_t index) {\n \
    \       if (index < get_size(node->lch)) {\n            return get_val(node->lch,\
    \ index);\n        } else if (index == get_size(node->lch)) {\n            return\
    \ node->val;\n        } else {\n            return get_val(node->rch, index -\
    \ get_size(node->lch) - 1);\n        }\n    }\n    node_t *insert(node_t *node,\
    \ val_t val) {\n        if (!node) {\n            return make_ptr(val);\n    \
    \    }\n        size_t index = lower_bound(node, val);\n        auto [l, r] =\
    \ split(node, index);\n        return merge(merge(l, make_ptr(val)), r);\n   \
    \ }\n    node_t *erase_by_index(node_t *node, size_t index) {\n        auto [l,\
    \ tmp] = split(node, index);\n        auto [to_del, r] = split(tmp, 1);\n    \
    \    return merge(l, r);\n    }\n    node_t *erase_by_val(node_t *node, val_t\
    \ val) {\n        size_t index = lower_bound(node, val);\n        return erase_by_index(node,\
    \ index);\n    }\n\n    val_t prod(node_t *node, size_t l, size_t r)\n       \
    \ requires monoid<S>\n    {\n        if (!node)\n            return S().e();\n\
    \        if (l == 0 && r == get_size(node->lch) + 1 + get_size(node->rch))\n \
    \           return node->product;\n        val_t ret = S().e();\n        if (l\
    \ < get_size(node->lch)) {\n            ret = S().op(ret,\n                  \
    \       prod(node->lch, l, std::min(get_size(node->lch), r)));\n        }\n  \
    \      if (l <= get_size(node->lch) && get_size(node->lch) < r) {\n          \
    \  ret = S().op(ret, node->val);\n        }\n        if (get_size(node->lch) +\
    \ 1 < r) {\n            ret = S().op(ret, prod(node->rch,\n                  \
    \                 std::max(l, get_size(node->lch) + 1) -\n                   \
    \                    (get_size(node->lch) + 1),\n                            \
    \       r - (get_size(node->lch) + 1)));\n        }\n        return ret;\n   \
    \ }\n\n  public:\n    /**\n     * @brief Construct a new rbst object\n     *\n\
    \     */\n    rbst() : pool(DEFAULT_POOL_SIZE) {}\n    /**\n     * @brief Construct\
    \ a new rbst object\n     *\n     * @param init\n     * set\u3092init\u3067\u521D\
    \u671F\u5316\u3059\u308B\n     */\n    rbst(std::vector<val_t> init) : pool(DEFAULT_POOL_SIZE)\
    \ {\n        for (val_t i : init)\n            insert(i);\n    }\n    /**\n  \
    \   * @brief `val`\u3092\u8FFD\u52A0\u3059\u308B\n     *\n     * @param val\n\
    \     */\n    void insert(val_t val) { top_node = insert(top_node, val); }\n \
    \   /**\n     * @brief `rbst[index]`\u306B\u3042\u308B\u8981\u7D20\u3092\u524A\
    \u9664\u3059\u308B\n     *\n     * @param index 0-indexed\n     */\n    void erase_by_index(size_t\
    \ index) {\n        assert(0 <= index && index < top_node->siz);\n        top_node\
    \ = erase_by_index(top_node, index);\n    }\n    /**\n     * @brief `val`\u3092\
    set\u304B\u3089\u524A\u9664\u3059\u308B\n     * \u5B58\u5728\u3057\u306A\u3044\
    \u5834\u5408\u306F\u30A8\u30E9\u30FC\u306B\u306A\u308B\n     *\n     * @param\
    \ val\n     */\n    void erase_by_val(val_t val) {\n        assert(includes(val));\n\
    \        top_node = erase_by_val(top_node, val);\n    }\n    /**\n     * @brief\
    \ \u5C0F\u3055\u3044\u65B9\u304B\u3089`index`\u756A\u76EE\u306E\u8981\u7D20\u3092\
    \u8FD4\u3059\n     *\n     * @param index 0-indexed\n     * @return val_t\n  \
    \   */\n    val_t operator[](size_t index) {\n        assert(0 <= index && index\
    \ < top_node->siz);\n        return get_val(top_node, index);\n    }\n    /**\n\
    \     * @brief set\u306E\u9577\u3055\u3092\u8FD4\u3059\n     *\n     * @return\
    \ size_t\n     */\n    size_t size() { return top_node ? top_node->siz : 0; }\n\
    \    /**\n     * @brief \u8981\u7D20\u304C`val`\u4EE5\u4E0A\u3067\u3042\u308B\u6700\
    \u5C0F\u306Eindex\u3092\u8FD4\u3059\n     * \u5B58\u5728\u3057\u306A\u3044\u5834\
    \u5408\u306Fsize()\u3092\u8FD4\u3059\n     *\n     * @param val\n     * @return\
    \ size_t\n     */\n    size_t lower_bound(val_t val) { return lower_bound(top_node,\
    \ val); }\n    /**\n     * @brief \u8981\u7D20\u304C`val`\u3088\u308A\u5927\u304D\
    \u3044\u6700\u5C0F\u306Eindex\u3092\u8FD4\u3059\n     *\n     * @param val\n \
    \    * @return size_t\n     */\n    size_t upper_bound(val_t val) { return upper_bound(top_node,\
    \ val); }\n    /**\n     * @brief `val`\u304Cset\u306B\u5B58\u5728\u3059\u308B\
    \u306A\u3089`true`\u3001\u305D\u3046\u3067\u306A\u3051\u308C\u3070`false`\u3092\
    \u8FD4\u3059\n     *\n     * @param val\n     * @return true\n     * @return false\n\
    \     */\n    bool includes(val_t val) {\n        size_t tmp = lower_bound(val);\n\
    \        return tmp < size() ? operator[](tmp) == val : false;\n    }\n    /**\n\
    \     * @brief op[l,r)\u3092\u8FD4\u3059\n     * S\u306B\u30E2\u30CE\u30A4\u30C9\
    \u304C\u4E0E\u3048\u3089\u308C\u305F\u5834\u5408\u306E\u307F\u5B58\u5728\u3059\
    \u308B\u95A2\u6570\n     *\n     * @param l\n     * @param r\n     * @return val_t\n\
    \     */\n    val_t prod(size_t l, size_t r) { return prod(top_node, l, r); }\n\
    };\n\n} // namespace libmcr\n#line 4 \"tests/binary-search-tree/rbst.test.cpp\"\
    \n\n#include <bits/stdc++.h>\nusing namespace std;\nint main() {\n    libmcr::rbst<long\
    \ long> tree;\n\n    int n, q;\n    cin >> n >> q;\n\n    string s;\n    cin >>\
    \ s;\n    for (int i = 0; i < n; i++) {\n        if (s[i] == '1')\n          \
    \  tree.insert(i);\n    }\n    while (q--) {\n        int c, k;\n        cin >>\
    \ c >> k;\n        if (c == 0) {\n            if (!tree.includes(k))\n       \
    \         tree.insert(k);\n        } else if (c == 1) {\n            if (tree.includes(k))\n\
    \                tree.erase_by_val(k);\n        } else if (c == 2) {\n       \
    \     if (tree.includes(k)) {\n                cout << 1 << endl;\n          \
    \  } else {\n                cout << 0 << endl;\n            }\n        } else\
    \ if (c == 3) {\n            int idx = tree.lower_bound(k);\n            if (idx\
    \ < tree.size())\n                cout << tree[idx] << endl;\n            else\n\
    \                cout << -1 << endl;\n        } else {\n            int idx =\
    \ tree.upper_bound(k) - 1;\n            if (0 <= idx)\n                cout <<\
    \ tree[idx] << endl;\n            else\n                cout << -1 << endl;\n\
    \        }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/predecessor_problem\"\n\
    \n#include \"../../binary-search-tree/rbst.hpp\"\n\n#include <bits/stdc++.h>\n\
    using namespace std;\nint main() {\n    libmcr::rbst<long long> tree;\n\n    int\
    \ n, q;\n    cin >> n >> q;\n\n    string s;\n    cin >> s;\n    for (int i =\
    \ 0; i < n; i++) {\n        if (s[i] == '1')\n            tree.insert(i);\n  \
    \  }\n    while (q--) {\n        int c, k;\n        cin >> c >> k;\n        if\
    \ (c == 0) {\n            if (!tree.includes(k))\n                tree.insert(k);\n\
    \        } else if (c == 1) {\n            if (tree.includes(k))\n           \
    \     tree.erase_by_val(k);\n        } else if (c == 2) {\n            if (tree.includes(k))\
    \ {\n                cout << 1 << endl;\n            } else {\n              \
    \  cout << 0 << endl;\n            }\n        } else if (c == 3) {\n         \
    \   int idx = tree.lower_bound(k);\n            if (idx < tree.size())\n     \
    \           cout << tree[idx] << endl;\n            else\n                cout\
    \ << -1 << endl;\n        } else {\n            int idx = tree.upper_bound(k)\
    \ - 1;\n            if (0 <= idx)\n                cout << tree[idx] << endl;\n\
    \            else\n                cout << -1 << endl;\n        }\n    }\n}"
  dependsOn:
  - binary-search-tree/rbst.hpp
  - algebra/concepts.hpp
  - internal/dummy.hpp
  isVerificationFile: true
  path: tests/binary-search-tree/rbst.test.cpp
  requiredBy: []
  timestamp: '2024-05-14 20:58:24-07:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: tests/binary-search-tree/rbst.test.cpp
layout: document
redirect_from:
- /verify/tests/binary-search-tree/rbst.test.cpp
- /verify/tests/binary-search-tree/rbst.test.cpp.html
title: tests/binary-search-tree/rbst.test.cpp
---
