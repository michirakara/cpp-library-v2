---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: "\u62E1\u5F35\u30E6\u30FC\u30AF\u30EA\u30C3\u30C9\u306E\u4E92\u9664\
      \u6CD5"
    links: []
  bundledCode: "#line 1 \"math/extgcd.hpp\"\n/**\n * @file extgcd.hpp\n * @author\
    \ michirakara\n * @brief \u62E1\u5F35\u30E6\u30FC\u30AF\u30EA\u30C3\u30C9\u306E\
    \u4E92\u9664\u6CD5\n * @date 2024-05-17\n */\n\n#include <utility>\n\nnamespace\
    \ libmcr {\n/**\n * @brief \u62E1\u5F35\u30E6\u30FC\u30AF\u30EA\u30C3\u30C9\u306E\
    \u4E92\u9664\u6CD5\u3067ax+by=GCD(a,b)\u3068\u306A\u308Bx,y\u3092\u6C42\u3081\u308B\
    \n *\n * @param a\n * @param b\n * @return std::pair<long long, long long>\n */\n\
    std::pair<long long, long long> extgcd(long long a, long long b) {\n    long long\
    \ x = 1, y = 1, u = 1, v = 1;\n    while (b) {\n        long long k = a / b;\n\
    \        x -= k * u;\n        y -= k * v;\n        std::swap(x, u);\n        std::swap(y,\
    \ v);\n        k = a % b;\n        a = b;\n        b = k;\n    }\n    return std::make_pair(x,\
    \ y);\n}\n/**\n * @brief \u62E1\u5F35\u30E6\u30FC\u30AF\u30EA\u30C3\u30C9\u306E\
    \u4E92\u9664\u6CD5\u3067ax+by=GCD(a,b)\u3068\u306A\u308Bx,y\u3092\u6C42\u3081\u308B\
    \n *\n * @param a\n * @param b\n * @return std::pair<__int128_t, __int128_t>\n\
    \ */\nstd::pair<__int128_t, __int128_t> extgcd(__int128_t a, __int128_t b) {\n\
    \    __int128_t x = 1, y = 1, u = 1, v = 1;\n    while (b) {\n        __int128_t\
    \ k = a / b;\n        x -= k * u;\n        y -= k * v;\n        std::swap(x, u);\n\
    \        std::swap(y, v);\n        k = a % b;\n        a = b;\n        b = k;\n\
    \    }\n    return std::make_pair(x, y);\n}\n} // namespace libmcr\n"
  code: "/**\n * @file extgcd.hpp\n * @author michirakara\n * @brief \u62E1\u5F35\u30E6\
    \u30FC\u30AF\u30EA\u30C3\u30C9\u306E\u4E92\u9664\u6CD5\n * @date 2024-05-17\n\
    \ */\n\n#include <utility>\n\nnamespace libmcr {\n/**\n * @brief \u62E1\u5F35\u30E6\
    \u30FC\u30AF\u30EA\u30C3\u30C9\u306E\u4E92\u9664\u6CD5\u3067ax+by=GCD(a,b)\u3068\
    \u306A\u308Bx,y\u3092\u6C42\u3081\u308B\n *\n * @param a\n * @param b\n * @return\
    \ std::pair<long long, long long>\n */\nstd::pair<long long, long long> extgcd(long\
    \ long a, long long b) {\n    long long x = 1, y = 1, u = 1, v = 1;\n    while\
    \ (b) {\n        long long k = a / b;\n        x -= k * u;\n        y -= k * v;\n\
    \        std::swap(x, u);\n        std::swap(y, v);\n        k = a % b;\n    \
    \    a = b;\n        b = k;\n    }\n    return std::make_pair(x, y);\n}\n/**\n\
    \ * @brief \u62E1\u5F35\u30E6\u30FC\u30AF\u30EA\u30C3\u30C9\u306E\u4E92\u9664\u6CD5\
    \u3067ax+by=GCD(a,b)\u3068\u306A\u308Bx,y\u3092\u6C42\u3081\u308B\n *\n * @param\
    \ a\n * @param b\n * @return std::pair<__int128_t, __int128_t>\n */\nstd::pair<__int128_t,\
    \ __int128_t> extgcd(__int128_t a, __int128_t b) {\n    __int128_t x = 1, y =\
    \ 1, u = 1, v = 1;\n    while (b) {\n        __int128_t k = a / b;\n        x\
    \ -= k * u;\n        y -= k * v;\n        std::swap(x, u);\n        std::swap(y,\
    \ v);\n        k = a % b;\n        a = b;\n        b = k;\n    }\n    return std::make_pair(x,\
    \ y);\n}\n} // namespace libmcr"
  dependsOn: []
  isVerificationFile: false
  path: math/extgcd.hpp
  requiredBy: []
  timestamp: '2024-05-17 10:24:58-07:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: math/extgcd.hpp
layout: document
redirect_from:
- /library/math/extgcd.hpp
- /library/math/extgcd.hpp.html
title: "\u62E1\u5F35\u30E6\u30FC\u30AF\u30EA\u30C3\u30C9\u306E\u4E92\u9664\u6CD5"
---
