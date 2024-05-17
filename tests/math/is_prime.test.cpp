#define PROBLEM "https://judge.yosupo.jp/problem/primality_test"

#include "../../math/prime.hpp"

#include <bits/stdc++.h>
using namespace std;
int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        unsigned long long x;
        cin >> x;
        cout << (libmcr::is_prime(x) ? "Yes" : "No") << endl;
    }
}