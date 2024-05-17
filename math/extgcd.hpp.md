---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/extgcd.hpp\"\n#include <utility>\n\nnamespace libmcr\
    \ {\nstd::pair<long long, long long> extgcd(long long a, long long b) {\n    long\
    \ long x = 1, y = 1, u = 1, v = 1;\n    while (b) {\n        long long k = a /\
    \ b;\n        x -= k * u;\n        y -= k * v;\n        std::swap(x, u);\n   \
    \     std::swap(y, v);\n        k = a % b;\n        a = b;\n        b = k;\n \
    \   }\n    return std::make_pair(x, y);\n}\nstd::pair<__int128_t, __int128_t>\
    \ extgcd(__int128_t a, __int128_t b) {\n    __int128_t x = 1, y = 1, u = 1, v\
    \ = 1;\n    while (b) {\n        __int128_t k = a / b;\n        x -= k * u;\n\
    \        y -= k * v;\n        std::swap(x, u);\n        std::swap(y, v);\n   \
    \     k = a % b;\n        a = b;\n        b = k;\n    }\n    return std::make_pair(x,\
    \ y);\n}\n} // namespace libmcr\n"
  code: "#include <utility>\n\nnamespace libmcr {\nstd::pair<long long, long long>\
    \ extgcd(long long a, long long b) {\n    long long x = 1, y = 1, u = 1, v = 1;\n\
    \    while (b) {\n        long long k = a / b;\n        x -= k * u;\n        y\
    \ -= k * v;\n        std::swap(x, u);\n        std::swap(y, v);\n        k = a\
    \ % b;\n        a = b;\n        b = k;\n    }\n    return std::make_pair(x, y);\n\
    }\nstd::pair<__int128_t, __int128_t> extgcd(__int128_t a, __int128_t b) {\n  \
    \  __int128_t x = 1, y = 1, u = 1, v = 1;\n    while (b) {\n        __int128_t\
    \ k = a / b;\n        x -= k * u;\n        y -= k * v;\n        std::swap(x, u);\n\
    \        std::swap(y, v);\n        k = a % b;\n        a = b;\n        b = k;\n\
    \    }\n    return std::make_pair(x, y);\n}\n} // namespace libmcr"
  dependsOn: []
  isVerificationFile: false
  path: math/extgcd.hpp
  requiredBy: []
  timestamp: '2024-05-16 21:55:44-07:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: math/extgcd.hpp
layout: document
redirect_from:
- /library/math/extgcd.hpp
- /library/math/extgcd.hpp.html
title: math/extgcd.hpp
---
