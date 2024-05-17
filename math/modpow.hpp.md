---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/montgomery-reduction.hpp
    title: math/montgomery-reduction.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/montgomery-reduction.hpp\"\n#include <iostream>\n\n\
    namespace libmcr {\nclass montgomery_reduction {\n    __uint128_t N;\n    __uint128_t\
    \ N_dash;\n    __uint128_t R2;\n\n    unsigned long long redc(__uint128_t t) {\n\
    \        unsigned long long m = N_dash * t;\n        __uint128_t to_ret = (t +\
    \ N * __uint128_t(m)) >> 64;\n        return to_ret < N ? to_ret : to_ret - N;\n\
    \    }\n\n  public:\n    montgomery_reduction(unsigned long long mod) : N(mod)\
    \ {\n        N_dash = 0;\n        __uint128_t t = 0;\n        __uint128_t vi =\
    \ 1;\n        for (int i = 0; i < 64; i++) {\n            if ((t & 1) == 0) {\n\
    \                t += N;\n                N_dash += vi;\n            }\n     \
    \       t >>= 1;\n            vi <<= 1;\n        }\n        R2 = (__uint128_t)(0ull\
    \ - mod) * (__uint128_t)(0ull - mod) % N;\n    }\n\n    unsigned long long mult(__uint128_t\
    \ a, __uint128_t b) {\n        return redc(redc(a * b) * R2);\n    }\n\n    unsigned\
    \ long long pow(__uint128_t a, __uint128_t b) {\n        __uint128_t p = redc(R2\
    \ * a);\n        __uint128_t x = redc(R2);\n        __uint128_t y = b;\n     \
    \   while (y) {\n            if (y & 1) {\n                x = redc(x * p);\n\
    \            }\n            p = redc(p * p);\n            y >>= 1;\n        }\n\
    \        return redc(x);\n    }\n};\n} // namespace libmcr\n#line 2 \"math/modpow.hpp\"\
    \n\nnamespace libmcr {\ntemplate <typename T> T modpow(T x, T n, T mod) {\n  \
    \  if (mod & 1) {\n        montgomery_reduction mr(mod);\n        return mr.pow(x,\
    \ n);\n    }\n    __uint128_t ans = 1;\n    __uint128_t xx = x;\n    while (n)\
    \ {\n        if (n & 1) {\n            ans = ans * xx % mod;\n        }\n    \
    \    xx = xx * xx % mod;\n        n >>= 1;\n    }\n    return ans;\n}\n} // namespace\
    \ libmcr\n"
  code: "#include \"../math/montgomery-reduction.hpp\"\n\nnamespace libmcr {\ntemplate\
    \ <typename T> T modpow(T x, T n, T mod) {\n    if (mod & 1) {\n        montgomery_reduction\
    \ mr(mod);\n        return mr.pow(x, n);\n    }\n    __uint128_t ans = 1;\n  \
    \  __uint128_t xx = x;\n    while (n) {\n        if (n & 1) {\n            ans\
    \ = ans * xx % mod;\n        }\n        xx = xx * xx % mod;\n        n >>= 1;\n\
    \    }\n    return ans;\n}\n} // namespace libmcr"
  dependsOn:
  - math/montgomery-reduction.hpp
  isVerificationFile: false
  path: math/modpow.hpp
  requiredBy: []
  timestamp: '2024-05-16 21:55:44-07:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: math/modpow.hpp
layout: document
redirect_from:
- /library/math/modpow.hpp
- /library/math/modpow.hpp.html
title: math/modpow.hpp
---
