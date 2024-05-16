namespace libmcr {
template <typename T> T modpow(T x, T n, T mod) {
    __uint128_t ans = 1;
    __uint128_t xx = x;
    while (n) {
        if (n & 1) {
            ans = ans * xx % mod;
        }
        xx = xx * xx % mod;
        n >>= 1;
    }
    return ans;
}
} // namespace libmcr