#include <ctime>
namespace libmcr {
unsigned int xorshift128_32() {
    static unsigned int x = 123456789, y = 362436069, z = 521288629,
                        w = std::time(nullptr);
    unsigned int t = x ^ (x << 11);
    x = y;
    y = z;
    z = w;
    w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
    return w;
}

unsigned long long xorshift128_64() {
    static unsigned long long x = 123456789, y = 362436069, z = 521288629,
                              w = std::time(nullptr);
    unsigned long long t = x ^ (x << 11);
    x = y;
    y = z;
    z = w;
    w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
    return w;
}
} // namespace libmcr