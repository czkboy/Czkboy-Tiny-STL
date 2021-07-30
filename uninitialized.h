#ifndef __LMSTL_UNINITIALIZED_H__
#define __LMSTL_UNINITIALIZED_H__

#include "iterator.h"
#include "construct.h"
#include "algobase.h"
#include <type_traits>
#include <cstring>

namespace lmstl {

template <typename ForwardIterator, typename size, typename T>
inline ForwardIterator __uninitialized_fill_n(ForwardIterator beg, size n, const T& x, std::true_type) {
	return lmstl::fill_n(beg, n, x);
}

template <typename ForwardIterator, typename size, typename T>
inline ForwardIterator __uninitialized_fill_n(ForwardIterator beg, size n, const T& x, std::false_type) {
	ForwardIterator p = beg;
	for (; n > 0; n--, p++)
		construct(&*p, x);
	return p;
}

template <typename ForwardIterator, typename size, typename T>
inline ForwardIterator uninitialized_fill_n(ForwardIterator beg, size n, const T& x) {
	return __uninitialized_fill_n(beg, n, x, std::is_pod<T>());
}

template <typename InputIterator, typename ForwardIterator>
inline ForwardIterator __uninitialized_copy_n(InputIterator beg, InputIterator end, ForwardIterator dest, std::true_type) {
	return lmstl::copy(beg, end, dest);
}

template <typename InputIterator, typename ForwardIterator>
inline ForwardIterator __uninitialized_copy_n(InputIterator beg, InputIterator end, ForwardIterator dest, std::false_type) {
	ForwardIterator p = dest;
	for (; beg != end; beg++, p++) 
		construct(&*p, *beg);
	return p;
}

template <typename InputIterator, typename ForwardIterator>
inline ForwardIterator uninitialized_copy(InputIterator beg, InputIterator end, ForwardIterator dest) {
	typedef iterator_traits<InputIterator>::value_type value_type;
	return __uninitialized_copy_n(beg, end, dest, std::is_pod<value_type>());
}

template<>
inline char* uninitialized_copy(const char* beg, const char* end, char* dest) {
	std::memmove(dest, beg, end - beg);
	return dest + (end - beg);
}

template<>
inline wchar_t* uninitialized_copy(const wchar_t* beg, const wchar_t* end, wchar_t* dest) {
	std::memmove(dest, beg, sizeof(wchar_t) * (end - beg));
	return dest + (end - beg);
}

template <typename InputIter, typename ForwardIter>
inline ForwardIter uninitialized_move_aux(InputIter beg, InputIter end, ForwardIter result, std::true_type) {
	return lmstl::move(beg, end, result);
}

template <typename InputIter, typename ForwardIter>
inline ForwardIter uninitialized_move_aux(InputIter beg, InputIter end, ForwardIter result, std::false_type) {
	size_t n = static_cast<size_t>(lmstl::distance(beg, end));
	for (; n; --n, ++beg, ++result)
		construct(&*result, lmstl::move(*beg));
	return result;
}

template <typename InputIter, typename ForwardIter>
inline ForwardIter uninitialized_move(InputIter beg, InputIter end, ForwardIter dest) {
	typedef std::is_trivially_move_assignable<typename iterator_traits<InputIter>::value_type> mt;
	return uninitialized_move_aux(beg, end, dest, mt());
}

template <typename InputIter, typename ForwardIter>
inline ForwardIter uninitialized_move_n_aux(InputIter beg, size_t n, ForwardIter result, std::true_type) {
	return lmstl::move(beg, beg + n, result);
}

template <typename InputIter, typename ForwardIter>
inline ForwardIter uninitialized_move_n_aux(InputIter beg, size_t n, ForwardIter result, std::false_type) {
	for (; n; --n, ++beg, ++result)
		construct(&*result, lmstl::move(*beg));
	return result;
}

template <typename InputIter, typename ForwardIter>
inline ForwardIter uninitialized_move_n(InputIter beg, size_t n, ForwardIter dest) {
	typedef std::is_trivially_move_assignable<typename iterator_traits<InputIter>::value_type> mt;
	return uninitialized_move_n_aux(beg, n, dest, mt());
}

template<>
inline char* uninitialized_move(const char* beg, const char* end, char* dest) {
	std::memmove(dest, beg, end - beg);
	return dest + (end - beg);
}

template<>
inline wchar_t* uninitialized_move(const wchar_t* beg, const wchar_t* end, wchar_t* dest) {
	std::memmove(dest, beg, sizeof(wchar_t) * (end - beg));
	return dest + (end - beg);
}


template <typename ForwardIterator, typename T>
inline void __uninitialized_fill(ForwardIterator beg, ForwardIterator end, const T& val, std::false_type) {
	ForwardIterator p = beg;
	for (; p != end; p++)
		construct(&*p, val);
}

template <typename ForwardIterator, typename T>
inline void __uninitialized_fill(ForwardIterator beg, ForwardIterator end, const T& val, std::true_type) {
	lmstl::fill(beg, end, val);
}

template <typename ForwardIterator, typename T>
inline void uninitialized_fill(ForwardIterator beg, ForwardIterator end, const T& val) {
	typedef iterator_traits<ForwardIterator>::value_type value_type;
	__uninitialized_fill(beg, end, val, std::is_pod<value_type>());
}

}
#endif // !__LMSTL_UNINITIALIZED_H__
