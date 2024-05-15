#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1508"

#include "../../binary-search-tree/rbst-list.hpp"

#include <bits/stdc++.h>
using namespace std;

template <class S> struct minMonoid {
    using value_type = S;
    S op(S a, S b) { return min(a, b); }
    S e() { return 1e9; }
};

int main() {
    int n, q;
    cin >> n >> q;
    vector a(n, 0ll);
    for (long long &i : a)
        cin >> i;
    libmcr::rbst_list<minMonoid<long long>> tree(a);

    while (q--) {
        int qi;
        cin >> qi;
        if (qi == 0) {
            int l, r;
            cin >> l >> r;
            long long tmp = tree[r];
            tree.erase(r);
            tree.insert(l, tmp);
        } else if (qi == 1) {
            int l, r;
            cin >> l >> r;
            cout << tree.prod(l, r + 1) << endl;
        } else {
            int pos;
            long long val;
            cin >> pos >> val;
            tree.erase(pos);
            tree.insert(pos, val);
        }
    }
}