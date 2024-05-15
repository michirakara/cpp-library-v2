#define PROBLEM "https://judge.yosupo.jp/problem/predecessor_problem"

#include "../../binary-search-tree/rbst-set.hpp"

#include <bits/stdc++.h>
using namespace std;
int main() {
    libmcr::rbst_set<long long> tree;

    int n, q;
    cin >> n >> q;

    string s;
    cin >> s;
    for (int i = 0; i < n; i++) {
        if (s[i] == '1')
            tree.insert(i);
    }
    while (q--) {
        int c, k;
        cin >> c >> k;
        if (c == 0) {
            if (!tree.includes(k))
                tree.insert(k);
        } else if (c == 1) {
            if (tree.includes(k))
                tree.erase_by_val(k);
        } else if (c == 2) {
            if (tree.includes(k)) {
                cout << 1 << endl;
            } else {
                cout << 0 << endl;
            }
        } else if (c == 3) {
            int idx = tree.lower_bound(k);
            if (idx < tree.size())
                cout << tree[idx] << endl;
            else
                cout << -1 << endl;
        } else {
            int idx = tree.upper_bound(k) - 1;
            if (0 <= idx)
                cout << tree[idx] << endl;
            else
                cout << -1 << endl;
        }
    }
}