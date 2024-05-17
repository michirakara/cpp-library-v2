---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: math/montgomery-reduction.hpp
    title: math/montgomery-reduction.hpp
  - icon: ':question:'
    path: random/xorshift.hpp
    title: random/xorshift.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: tests/math/enumerate_primes.test.cpp
    title: tests/math/enumerate_primes.test.cpp
  - icon: ':heavy_check_mark:'
    path: tests/math/is_prime.test.cpp
    title: tests/math/is_prime.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    document_title: "n**\u4EE5\u4E0B**\u306E\u7D20\u6570\u306Evector\u3092\u8FD4\u3059"
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
    \        return redc(x);\n    }\n};\n} // namespace libmcr\n#line 1 \"random/xorshift.hpp\"\
    \n#include <ctime>\nnamespace libmcr {\nunsigned int xorshift128_32() {\n    static\
    \ unsigned int x = 123456789, y = 362436069, z = 521288629,\n                \
    \        w = std::time(nullptr);\n    unsigned int t = x ^ (x << 11);\n    x =\
    \ y;\n    y = z;\n    z = w;\n    w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));\n    return\
    \ w;\n}\n\nunsigned long long xorshift128_64() {\n    static unsigned long long\
    \ x = 123456789, y = 362436069, z = 521288629,\n                             \
    \ w = std::time(nullptr);\n    unsigned long long t = x ^ (x << 11);\n    x =\
    \ y;\n    y = z;\n    z = w;\n    w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));\n    return\
    \ w;\n}\n} // namespace libmcr\n#line 3 \"math/prime.hpp\"\n#include <algorithm>\n\
    #include <concepts>\n#include <numeric>\n#include <vector>\n\nnamespace libmcr\
    \ {\nnamespace internal {\n\nbool fermat_test(unsigned long long n, const size_t\
    \ REP_NUM) {\n    montgomery_reduction MR(n);\n    for (size_t rep = 0; rep <\
    \ REP_NUM; rep++) {\n        unsigned long long a = xorshift128_64() % (n - 1)\
    \ + 1;\n        if (MR.pow(a, n - 1) != 1)\n            return false;\n    }\n\
    \    return true;\n}\n\nbool miller_rabin(unsigned long long n) {\n    if (n <=\
    \ 1) {\n        return false;\n    }\n    unsigned long long k = 0;\n    unsigned\
    \ long long m = n - 1;\n    while (!(m & 1)) {\n        k += 1;\n        m >>=\
    \ 1;\n    }\n    montgomery_reduction MR(n);\n    for (unsigned long long a :\n\
    \         {2, 325, 9375, 28178, 450775, 9780504, 1795265022}) {\n        if (a\
    \ % n == 0)\n            continue;\n        unsigned long long b = MR.pow(a, m);\n\
    \n        if (b == 1)\n            continue;\n\n        bool flag = false;\n \
    \       for (size_t rep2 = 0; rep2 < k; rep2++) {\n            if (b == n - 1)\
    \ {\n                flag = true;\n                break;\n            }\n   \
    \         b = MR.mult(b, b);\n        }\n        if (!flag)\n            return\
    \ false;\n    }\n    return true;\n}\n\n} // namespace internal\nbool is_prime(unsigned\
    \ long long num) {\n    if (num <= 1) {\n        return false;\n    } else if\
    \ (num <= 3) {\n        return true;\n    }\n    if (!(num & 1))\n        return\
    \ false;\n    if (internal::miller_rabin(num)) {\n        return true;\n    }\n\
    \    return false;\n}\n/**\n * @brief n**\u4EE5\u4E0B**\u306E\u7D20\u6570\u306E\
    vector\u3092\u8FD4\u3059\n *\n * @param n\n * @return std::vector<unsigned long\
    \ long>\n */\nstd::vector<unsigned long long> enumerate_primes(unsigned long long\
    \ n) {\n    if (n <= 1)\n        return {};\n    if (n == 2)\n        return {2};\n\
    \    std::vector<unsigned long long> to_ret{2, 3};\n    for (int i = 6; i - 1\
    \ <= n; i += 6) {\n        if (is_prime(i - 1))\n            to_ret.push_back(i\
    \ - 1);\n        if (i + 1 <= n && is_prime(i + 1))\n            to_ret.push_back(i\
    \ + 1);\n    }\n    return to_ret;\n}\n} // namespace libmcr\n"
  code: "#include \"../math/montgomery-reduction.hpp\"\n#include \"../random/xorshift.hpp\"\
    \n#include <algorithm>\n#include <concepts>\n#include <numeric>\n#include <vector>\n\
    \nnamespace libmcr {\nnamespace internal {\n\nbool fermat_test(unsigned long long\
    \ n, const size_t REP_NUM) {\n    montgomery_reduction MR(n);\n    for (size_t\
    \ rep = 0; rep < REP_NUM; rep++) {\n        unsigned long long a = xorshift128_64()\
    \ % (n - 1) + 1;\n        if (MR.pow(a, n - 1) != 1)\n            return false;\n\
    \    }\n    return true;\n}\n\nbool miller_rabin(unsigned long long n) {\n   \
    \ if (n <= 1) {\n        return false;\n    }\n    unsigned long long k = 0;\n\
    \    unsigned long long m = n - 1;\n    while (!(m & 1)) {\n        k += 1;\n\
    \        m >>= 1;\n    }\n    montgomery_reduction MR(n);\n    for (unsigned long\
    \ long a :\n         {2, 325, 9375, 28178, 450775, 9780504, 1795265022}) {\n \
    \       if (a % n == 0)\n            continue;\n        unsigned long long b =\
    \ MR.pow(a, m);\n\n        if (b == 1)\n            continue;\n\n        bool\
    \ flag = false;\n        for (size_t rep2 = 0; rep2 < k; rep2++) {\n         \
    \   if (b == n - 1) {\n                flag = true;\n                break;\n\
    \            }\n            b = MR.mult(b, b);\n        }\n        if (!flag)\n\
    \            return false;\n    }\n    return true;\n}\n\n} // namespace internal\n\
    bool is_prime(unsigned long long num) {\n    if (num <= 1) {\n        return false;\n\
    \    } else if (num <= 3) {\n        return true;\n    }\n    if (!(num & 1))\n\
    \        return false;\n    if (internal::miller_rabin(num)) {\n        return\
    \ true;\n    }\n    return false;\n}\n/**\n * @brief n**\u4EE5\u4E0B**\u306E\u7D20\
    \u6570\u306Evector\u3092\u8FD4\u3059\n *\n * @param n\n * @return std::vector<unsigned\
    \ long long>\n */\nstd::vector<unsigned long long> enumerate_primes(unsigned long\
    \ long n) {\n    if (n <= 1)\n        return {};\n    if (n == 2)\n        return\
    \ {2};\n    std::vector<unsigned long long> to_ret{2, 3};\n    for (int i = 6;\
    \ i - 1 <= n; i += 6) {\n        if (is_prime(i - 1))\n            to_ret.push_back(i\
    \ - 1);\n        if (i + 1 <= n && is_prime(i + 1))\n            to_ret.push_back(i\
    \ + 1);\n    }\n    return to_ret;\n}\n} // namespace libmcr"
  dependsOn:
  - math/montgomery-reduction.hpp
  - random/xorshift.hpp
  isVerificationFile: false
  path: math/prime.hpp
  requiredBy: []
  timestamp: '2024-05-17 09:28:03-07:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - tests/math/enumerate_primes.test.cpp
  - tests/math/is_prime.test.cpp
documentation_of: math/prime.hpp
layout: document
redirect_from:
- /library/math/prime.hpp
- /library/math/prime.hpp.html
title: "n**\u4EE5\u4E0B**\u306E\u7D20\u6570\u306Evector\u3092\u8FD4\u3059"
---
