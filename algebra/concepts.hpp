#include <concepts>
namespace libmcr {
template <class Monoid>
concept monoid = requires(Monoid a, Monoid::value_type x) {
    { a.op(x, x) } -> std::same_as<typename Monoid::value_type>;
    { a.e() } -> std::same_as<typename Monoid::value_type>;
};
} // namespace libmcr