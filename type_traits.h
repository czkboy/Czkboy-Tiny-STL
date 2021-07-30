#ifndef __LMSTL_TYPE_TRAITS_H__
#define __LMSTL_TYPE_TRAITS_H__

namespace lmstl {

template <class... _Types>
using void_t = void;

template <typename T, T v>
struct lm_integral_constant {
	static constexpr T value = v;
	using value_type = T;
	using type = lm_integral_constant;
	constexpr operator value_type() const noexcept { return value; }
	constexpr value_type operator()() const noexcept { return value; }
};

template <bool b>
using lm_bool_constant = lm_integral_constant<bool, b>;

typedef lm_bool_constant<true> true_type;
typedef lm_bool_constant<false> false_type;


template <bool b, typename T = void>
struct enable_if {};

template <typename T>
struct enable_if<true, T> {
	typedef T type;
};

}

#endif // !__LMSTL_TYPE_TRAITS_H__
