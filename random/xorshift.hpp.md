---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: binary-search-tree/rbst-set.hpp
    title: RBST ordered set
  - icon: ':heavy_check_mark:'
    path: math/prime.hpp
    title: math/prime.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: tests/binary-search-tree/rbst.test.cpp
    title: tests/binary-search-tree/rbst.test.cpp
  - icon: ':heavy_check_mark:'
    path: tests/math/is_prime.test.cpp
    title: tests/math/is_prime.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"random/xorshift.hpp\"\n#include <ctime>\nnamespace libmcr\
    \ {\nunsigned int xorshift128_32() {\n    static unsigned int x = 123456789, y\
    \ = 362436069, z = 521288629,\n                        w = std::time(nullptr);\n\
    \    unsigned int t = x ^ (x << 11);\n    x = y;\n    y = z;\n    z = w;\n   \
    \ w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));\n    return w;\n}\n\nunsigned long long\
    \ xorshift128_64() {\n    static unsigned long long x = 123456789, y = 362436069,\
    \ z = 521288629,\n                              w = std::time(nullptr);\n    unsigned\
    \ long long t = x ^ (x << 11);\n    x = y;\n    y = z;\n    z = w;\n    w = (w\
    \ ^ (w >> 19)) ^ (t ^ (t >> 8));\n    return w;\n}\n} // namespace libmcr\n"
  code: "#include <ctime>\nnamespace libmcr {\nunsigned int xorshift128_32() {\n \
    \   static unsigned int x = 123456789, y = 362436069, z = 521288629,\n       \
    \                 w = std::time(nullptr);\n    unsigned int t = x ^ (x << 11);\n\
    \    x = y;\n    y = z;\n    z = w;\n    w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));\n\
    \    return w;\n}\n\nunsigned long long xorshift128_64() {\n    static unsigned\
    \ long long x = 123456789, y = 362436069, z = 521288629,\n                   \
    \           w = std::time(nullptr);\n    unsigned long long t = x ^ (x << 11);\n\
    \    x = y;\n    y = z;\n    z = w;\n    w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));\n\
    \    return w;\n}\n} // namespace libmcr"
  dependsOn: []
  isVerificationFile: false
  path: random/xorshift.hpp
  requiredBy:
  - binary-search-tree/rbst-set.hpp
  - math/prime.hpp
  timestamp: '2024-05-16 15:34:49-07:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - tests/binary-search-tree/rbst.test.cpp
  - tests/math/is_prime.test.cpp
documentation_of: random/xorshift.hpp
layout: document
redirect_from:
- /library/random/xorshift.hpp
- /library/random/xorshift.hpp.html
title: random/xorshift.hpp
---
