---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: binary-search-tree/rbst.hpp
    title: RBST ordered set
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: tests/binary-search-tree/rbst.test.cpp
    title: tests/binary-search-tree/rbst.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: concepts
    links: []
  bundledCode: "#line 1 \"algebra/concepts.hpp\"\n/**\n * @file concepts.hpp\n * @author\
    \ michirakara\n * @brief concepts\n * @date 2024-05-14\n */\n#include <concepts>\n\
    namespace libmcr {\n/**\n * @brief monoid\u304B\u3069\u3046\u304B\u3092\u5224\u5B9A\
    \u3059\u308Bconcept\n * `value_type`, `value_type op(value_type x,value_type x)`,\n\
    \ * `value_type e()`\u304C\u5B58\u5728\u3059\u308B\u304B\u5224\u5B9A\u3059\u308B\
    \n *\n * @tparam Monoid\n */\ntemplate <class Monoid>\nconcept monoid = requires(Monoid\
    \ a, Monoid::value_type x) {\n    { a.op(x, x) } -> std::same_as<typename Monoid::value_type>;\n\
    \    { a.e() } -> std::same_as<typename Monoid::value_type>;\n};\n} // namespace\
    \ libmcr\n"
  code: "/**\n * @file concepts.hpp\n * @author michirakara\n * @brief concepts\n\
    \ * @date 2024-05-14\n */\n#include <concepts>\nnamespace libmcr {\n/**\n * @brief\
    \ monoid\u304B\u3069\u3046\u304B\u3092\u5224\u5B9A\u3059\u308Bconcept\n * `value_type`,\
    \ `value_type op(value_type x,value_type x)`,\n * `value_type e()`\u304C\u5B58\
    \u5728\u3059\u308B\u304B\u5224\u5B9A\u3059\u308B\n *\n * @tparam Monoid\n */\n\
    template <class Monoid>\nconcept monoid = requires(Monoid a, Monoid::value_type\
    \ x) {\n    { a.op(x, x) } -> std::same_as<typename Monoid::value_type>;\n   \
    \ { a.e() } -> std::same_as<typename Monoid::value_type>;\n};\n} // namespace\
    \ libmcr"
  dependsOn: []
  isVerificationFile: false
  path: algebra/concepts.hpp
  requiredBy:
  - binary-search-tree/rbst.hpp
  timestamp: '2024-05-14 22:41:03-07:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - tests/binary-search-tree/rbst.test.cpp
documentation_of: algebra/concepts.hpp
layout: document
redirect_from:
- /library/algebra/concepts.hpp
- /library/algebra/concepts.hpp.html
title: concepts
---
