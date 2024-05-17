#include <utility>

namespace libmcr {
/**
 * @brief 拡張ユークリッドの互除法でax+by=GCD(a,b)となるx,yを求める
 *
 * @param a
 * @param b
 * @return std::pair<long long, long long>
 */
std::pair<long long, long long> extgcd(long long a, long long b) {
    long long x = 1, y = 1, u = 1, v = 1;
    while (b) {
        long long k = a / b;
        x -= k * u;
        y -= k * v;
        std::swap(x, u);
        std::swap(y, v);
        k = a % b;
        a = b;
        b = k;
    }
    return std::make_pair(x, y);
}
/**
 * @brief 拡張ユークリッドの互除法でax+by=GCD(a,b)となるx,yを求める
 *
 * @param a
 * @param b
 * @return std::pair<__int128_t, __int128_t>
 */
std::pair<__int128_t, __int128_t> extgcd(__int128_t a, __int128_t b) {
    __int128_t x = 1, y = 1, u = 1, v = 1;
    while (b) {
        __int128_t k = a / b;
        x -= k * u;
        y -= k * v;
        std::swap(x, u);
        std::swap(y, v);
        k = a % b;
        a = b;
        b = k;
    }
    return std::make_pair(x, y);
}
} // namespace libmcr