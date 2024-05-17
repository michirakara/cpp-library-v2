#define PROBLEM "https://judge.yosupo.jp/problem/enumerate_primes"

#include "../../math/prime.hpp"

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, a, b;
    cin >> n >> a >> b;
    vector<unsigned long long> l = libmcr::enumerate_primes(n);

    vector<unsigned long long> to_out;
    for (int i = b; i < l.size(); i += a) {
        to_out.push_back(l[i]);
    }

    cout << l.size() << ' ' << to_out.size() << '\n';
    for (int i = 0; i < to_out.size(); i++) {
        cout << to_out[i] << " \n"[to_out.size() - 1 == i];
    }
}