#include "../math/modpow.hpp"
#include "../random/xorshift.hpp"
#include <algorithm>
#include <concepts>
#include <numeric>

namespace libmcr {
namespace internal {

bool fermat_test(unsigned long long n, const size_t REP_NUM) {
    for (size_t rep = 0; rep < REP_NUM; rep++) {
        unsigned long long a = xorshift128_64() % (n - 1) + 1;
        if (modpow(a, n - 1, n) != 1)
            return false;
    }
    return true;
}

bool miller_rabin(unsigned long long n, const size_t REP_NUM) {
    if (n <= 1) {
        return false;
    }
    unsigned long long k = 0;
    unsigned long long m = n - 1;
    while (!(m & 1)) {
        k += 1;
        m >>= 1;
    }
    for (size_t rep = 0; rep < REP_NUM; rep++) {
        unsigned long long a = xorshift128_64() % (n - 2) + 2;
        unsigned long long b = modpow(a, m, n);

        bool flag = false;
        if (b == 1) {
            flag = true;
        } else {
            for (size_t rep2 = 0; rep2 < k; rep2++) {
                if (b == n - 1) {
                    flag = true;
                    break;
                }
                b = __uint128_t(b) * __uint128_t(b) % n;
            }
        }
        if (!flag)
            return false;
    }
    return true;
}

} // namespace internal
bool is_prime(unsigned long long num) {
    const unsigned long long SMALL_PRIMES[] = {2,  3,  5,  7,  11,
                                               13, 17, 19, 23, 29};
    if (num <= 29) {
        for (unsigned long long i : SMALL_PRIMES) {
            if (num == i)
                return true;
        }
        return false;
    }
    if (!(num & 1))
        return false;
    const unsigned long long PRIME_PRODUCT = 3234846615;
    if (std::gcd(PRIME_PRODUCT, num) != 1)
        return false;
    if (internal::fermat_test(num, 5) && internal::miller_rabin(num, 20)) {
        return true;
    }
    return false;
}
} // namespace libmcr