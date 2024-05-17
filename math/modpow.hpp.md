---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: math/montgomery-reduction.hpp
    title: "\u30E2\u30F3\u30B4\u30E1\u30EA\u4E57\u7B97"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: modpow
    links: []
  bundledCode: "#line 1 \"math/modpow.hpp\"\n/**\n * @file modpow.hpp\n * @author\
    \ michirakara\n * @brief modpow\n * @date 2024-05-17\n */\n#line 1 \"math/montgomery-reduction.hpp\"\
    \n/**\n * @file montgomery-reduction.hpp\n * @author michirakara\n * @brief \u30E2\
    \u30F3\u30B4\u30E1\u30EA\u4E57\u7B97\n * @date 2024-05-17\n */\n\n#include <iostream>\n\
    \nnamespace libmcr {\n/**\n * @brief \u30E2\u30F3\u30B4\u30E1\u30EA\u4E57\u7B97\
    \n *\n */\nclass montgomery_reduction {\n    __uint128_t N;\n    __uint128_t N_dash;\n\
    \    __uint128_t R2;\n\n    unsigned long long redc(__uint128_t t) {\n       \
    \ unsigned long long m = N_dash * t;\n        __uint128_t to_ret = (t + N * __uint128_t(m))\
    \ >> 64;\n        return to_ret < N ? to_ret : to_ret - N;\n    }\n\n  public:\n\
    \    /**\n     * @brief \u6CD5 mod \u306E\u30E2\u30F3\u30B4\u30E1\u30EA\u4E57\u7B97\
    \u306E\u30B3\u30F3\u30B9\u30C8\u30E9\u30AF\u30BF\n     *\n     * @param mod \u5947\
    \u6570\u306E\u6CD5\n     */\n    montgomery_reduction(unsigned long long mod)\
    \ : N(mod) {\n        N_dash = 0;\n        __uint128_t t = 0;\n        __uint128_t\
    \ vi = 1;\n        for (int i = 0; i < 64; i++) {\n            if ((t & 1) ==\
    \ 0) {\n                t += N;\n                N_dash += vi;\n            }\n\
    \            t >>= 1;\n            vi <<= 1;\n        }\n        R2 = (__uint128_t)(0ull\
    \ - mod) * (__uint128_t)(0ull - mod) % N;\n    }\n    /**\n     * @brief a*b mod\
    \ mod\u3092\u8A08\u7B97\u3059\u308B\n     *\n     * @param a\n     * @param b\n\
    \     * @return unsigned long long\n     */\n    unsigned long long mult(__uint128_t\
    \ a, __uint128_t b) {\n        return redc(redc(a * b) * R2);\n    }\n    /**\n\
    \     * @brief a^b mod mod\u3092\u8A08\u7B97\u3059\u308B\n     *\n     * @param\
    \ a\n     * @param b\n     * @return unsigned long long\n     */\n    unsigned\
    \ long long pow(__uint128_t a, __uint128_t b) {\n        __uint128_t p = redc(R2\
    \ * a);\n        __uint128_t x = redc(R2);\n        __uint128_t y = b;\n     \
    \   while (y) {\n            if (y & 1) {\n                x = redc(x * p);\n\
    \            }\n            p = redc(p * p);\n            y >>= 1;\n        }\n\
    \        return redc(x);\n    }\n};\n} // namespace libmcr\n#line 8 \"math/modpow.hpp\"\
    \n\nnamespace libmcr {\n/**\n * @brief x ^ n % mod \u3092\u6C42\u3081\u308B\n\
    \ *\n * @tparam T\n * @param x\n * @param n\n * @param mod\n * @return T\n */\n\
    template <typename T> T modpow(T x, T n, T mod) {\n    if (mod & 1) {\n      \
    \  montgomery_reduction mr(mod);\n        return mr.pow(x, n);\n    }\n    __uint128_t\
    \ ans = 1;\n    __uint128_t xx = x;\n    while (n) {\n        if (n & 1) {\n \
    \           ans = ans * xx % mod;\n        }\n        xx = xx * xx % mod;\n  \
    \      n >>= 1;\n    }\n    return ans;\n}\n} // namespace libmcr\n"
  code: "/**\n * @file modpow.hpp\n * @author michirakara\n * @brief modpow\n * @date\
    \ 2024-05-17\n */\n#include \"../math/montgomery-reduction.hpp\"\n\nnamespace\
    \ libmcr {\n/**\n * @brief x ^ n % mod \u3092\u6C42\u3081\u308B\n *\n * @tparam\
    \ T\n * @param x\n * @param n\n * @param mod\n * @return T\n */\ntemplate <typename\
    \ T> T modpow(T x, T n, T mod) {\n    if (mod & 1) {\n        montgomery_reduction\
    \ mr(mod);\n        return mr.pow(x, n);\n    }\n    __uint128_t ans = 1;\n  \
    \  __uint128_t xx = x;\n    while (n) {\n        if (n & 1) {\n            ans\
    \ = ans * xx % mod;\n        }\n        xx = xx * xx % mod;\n        n >>= 1;\n\
    \    }\n    return ans;\n}\n} // namespace libmcr"
  dependsOn:
  - math/montgomery-reduction.hpp
  isVerificationFile: false
  path: math/modpow.hpp
  requiredBy: []
  timestamp: '2024-05-17 10:07:50-07:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: math/modpow.hpp
layout: document
redirect_from:
- /library/math/modpow.hpp
- /library/math/modpow.hpp.html
title: modpow
---
