#include "../../binary-search-tree/rbst.hpp"

#include <bits/stdc++.h>

using namespace std;

template <typename S> struct addMonoid {
    using value_type = S;
    S op(S a, S b) { return a + b; }
    S e() { return 0; }
};
int main() {
    libmcr::rbst<addMonoid<int>> tree;

    for (int i : {1, 3, 2, 5, 7, 3, 8}) {
        tree.insert(i);
        for (int j = 0; j < tree.size(); j++) {
            cout << tree[j] << ",\n"[j == tree.size() - 1];
        }
        cout << "sum = " << tree.prod(0, tree.size()) << endl;
    }
}