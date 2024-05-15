#include <concepts>
namespace libmcr {
/**
 * @brief monoidかどうかを判定するconcept
 * `value_type`, `value_type op(value_type x,value_type x)`,
 * `value_type e()`が存在するか判定する
 *
 * @tparam Monoid
 */
template <class Monoid>
concept monoid = requires(Monoid a, Monoid::value_type x) {
    { a.op(x, x) } -> std::same_as<typename Monoid::value_type>;
    { a.e() } -> std::same_as<typename Monoid::value_type>;
};
} // namespace libmcr