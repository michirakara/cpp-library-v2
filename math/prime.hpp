/**
 * @file prime.hpp
 * @author michirakara
 * @brief 素数
 * @date 2024-05-17
 */

#include "../math/montgomery-reduction.hpp"
#include "../random/xorshift.hpp"
#include <algorithm>
#include <concepts>
#include <numeric>
#include <vector>

namespace libmcr {
namespace internal {

bool fermat_test(unsigned long long n, const size_t REP_NUM) {
    montgomery_reduction MR(n);
    for (size_t rep = 0; rep < REP_NUM; rep++) {
        unsigned long long a = xorshift128_64() % (n - 1) + 1;
        if (MR.pow(a, n - 1) != 1)
            return false;
    }
    return true;
}

bool miller_rabin(unsigned long long n) {
    if (n <= 1) {
        return false;
    }
    unsigned long long k = 0;
    unsigned long long m = n - 1;
    while (!(m & 1)) {
        k += 1;
        m >>= 1;
    }
    montgomery_reduction MR(n);
    for (unsigned long long a :
         {2, 325, 9375, 28178, 450775, 9780504, 1795265022}) {
        if (a % n == 0)
            continue;
        unsigned long long b = MR.pow(a, m);

        if (b == 1)
            continue;

        bool flag = false;
        for (size_t rep2 = 0; rep2 < k; rep2++) {
            if (b == n - 1) {
                flag = true;
                break;
            }
            b = MR.mult(b, b);
        }
        if (!flag)
            return false;
    }
    return true;
}

} // namespace internal
/**
 * @brief numが素数であるか判定する 確率的アルゴリズム**ではない**
 *
 * @param num
 * @return true 素数の場合
 * @return false 素数でない場合
 */
bool is_prime(unsigned long long num) {
    if (num <= 1) {
        return false;
    } else if (num <= 3) {
        return true;
    }
    if (!(num & 1))
        return false;
    if (internal::miller_rabin(num)) {
        return true;
    }
    return false;
}
/**
 * @brief n**以下**の素数のvectorを返す
 *
 * @param n
 * @return std::vector<unsigned long long>
 */
std::vector<unsigned long long> enumerate_primes(unsigned long long n) {
    if (n <= 1)
        return {};
    if (n == 2)
        return {2};
    std::vector<unsigned long long> to_ret{2, 3};
    for (int i = 6; i - 1 <= n; i += 6) {
        if (is_prime(i - 1))
            to_ret.push_back(i - 1);
        if (i + 1 <= n && is_prime(i + 1))
            to_ret.push_back(i + 1);
    }
    return to_ret;
}
} // namespace libmcr