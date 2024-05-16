#define PROBLEM "https://yukicoder.me/problems/no/3030"

#include "../../math/prime.hpp"

#include <bits/stdc++.h>
using namespace std;
int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        unsigned long long x;
        cin >> x;
        cout << x << ' ' << int(libmcr::is_prime(x)) << endl;
    }
}