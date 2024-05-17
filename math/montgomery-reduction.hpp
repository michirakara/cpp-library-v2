#include <iostream>

namespace libmcr {
class montgomery_reduction {
    __uint128_t N;
    __uint128_t N_dash;
    __uint128_t R2;

    unsigned long long redc(__uint128_t t) {
        unsigned long long m = N_dash * t;
        __uint128_t to_ret = (t + N * __uint128_t(m)) >> 64;
        return to_ret < N ? to_ret : to_ret - N;
    }

  public:
    montgomery_reduction(unsigned long long mod) : N(mod) {
        N_dash = 0;
        __uint128_t t = 0;
        __uint128_t vi = 1;
        for (int i = 0; i < 64; i++) {
            if ((t & 1) == 0) {
                t += N;
                N_dash += vi;
            }
            t >>= 1;
            vi <<= 1;
        }
        R2 = (__uint128_t)(0ull - mod) * (__uint128_t)(0ull - mod) % N;
    }

    unsigned long long mult(__uint128_t a, __uint128_t b) {
        return redc(redc(a * b) * R2);
    }

    unsigned long long pow(__uint128_t a, __uint128_t b) {
        __uint128_t p = redc(R2 * a);
        __uint128_t x = redc(R2);
        __uint128_t y = b;
        while (y) {
            if (y & 1) {
                x = redc(x * p);
            }
            p = redc(p * p);
            y >>= 1;
        }
        return redc(x);
    }
};
} // namespace libmcr