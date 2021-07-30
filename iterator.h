#ifndef __LMSTL_ITERATOR_H__
#define __LMSTL_ITERATOR_H__

#include "type_traits.h"
#include <type_traits>
#include <stddef.h>

namespace lmstl {

struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

template <typename T, typename = void>
struct iterator_traits_base {};

template <typename T>
struct iterator_traits_base <T, void_t<
	typename T::iterator_category,
	typename T::value_type,
	typename T::difference_type,
	typename T::pointer,
	typename T::reference>> {
	typedef typename T::iterator_category	iterator_category;
	typedef typename T::value_type			value_type;
	typedef typename T::difference_type		difference_type;
	typedef typename T::pointer				pointer;
	typedef typename T::reference			reference;
};

template <typename T, bool = std::is_object_v<T>>
struct iterator_pointer_traits_base {
	typedef random_access_iterator_tag	iterator_category;
	typedef T							value_type;
	typedef ptrdiff_t					difference_type;
	typedef T*							pointer;
	typedef T&							reference;
};

template <typename T>
struct iterator_pointer_traits_base<T, false> {};

template <typename T>
struct iterator_traits : public iterator_traits_base<T> {};

template <typename T>
struct iterator_traits<T*> : public iterator_pointer_traits_base<T> {};

template <typename T>
struct iterator_traits<const T*> : public iterator_pointer_traits_base<T> {};

template <typename Iter>
using iter_cat = typename iterator_traits<Iter>::iterator_category;

template <typename Iter, class = void>
constexpr bool is_iterator_v = false;

template <typename Iter>
constexpr bool is_iterator_v<Iter, void_t<iter_cat<Iter>>> = true;

template <typename Iter, typename = void>
constexpr bool is_input_iterator_v = false;

template <typename Iter>
constexpr bool is_input_iterator_v<Iter, void_t<iter_cat<Iter>>> = std::is_convertible_v<iter_cat<Iter>, input_iterator_tag>;

template <typename Iter, typename = void>
constexpr bool is_output_iterator_v = false;

template <typename Iter>
constexpr bool is_output_iterator_v<Iter, void_t<iter_cat<Iter>>> = std::is_convertible_v<iter_cat<Iter>, output_iterator_tag>;

template <typename Iter, typename = void>
constexpr bool is_forward_iterator_v = false;

template <typename Iter>
constexpr bool is_forward_iterator_v<Iter, void_t<iter_cat<Iter>>> = std::is_convertible_v<iter_cat<Iter>, forward_iterator_tag>;

template <typename Iter, typename = void>
constexpr bool is_bidirectional_iterator_v = false;

template <typename Iter>
constexpr bool is_bidirectional_iterator_v<Iter, void_t<iter_cat<Iter>>> = std::is_convertible_v<iter_cat<Iter>, bidirectional_iterator_tag>;

template <typename Iter, typename = void>
constexpr bool is_random_access_iterator_v = false;

template <typename Iter>
constexpr bool is_random_access_iterator_v<Iter, void_t<iter_cat<Iter>>> = std::is_convertible_v<iter_cat<Iter>, random_access_iterator_tag>;

template <typename InputIterator, typename Distance>
inline void __advance(InputIterator& i, Distance d, input_iterator_tag) {
	while (d--)
		++i;
}

template <typename InputIterator, typename Distance>
inline void __advance(InputIterator& i, Distance d, bidirectional_iterator_tag) {
	if (d > 0) {
		while (d--)	++i;
	}
	else {
		while (d++) --i;
	}
}

template <typename InputIterator, typename Distance>
inline void __advance(InputIterator& i, Distance d, random_access_iterator_tag) {
	i += d;
}

template <typename InputIterator, typename Distance>
inline void advance(InputIterator& i, Distance d) {
	__advance(i, d, iterator_traits<InputIterator>::iterator_category());
}

template <typename InputIterator>
inline typename iterator_traits<InputIterator>::difference_type __distance(InputIterator beg, InputIterator end, input_iterator_tag) {
	typename iterator_traits<InputIterator>::difference_type cnt = 0;
	while (beg != end) {
		cnt++;
		beg++;
	}
	return cnt;
}

template <typename InputIterator>
inline typename iterator_traits<InputIterator>::difference_type __distance(InputIterator beg, InputIterator end, random_access_iterator_tag) {
	return (end - beg);
}

template <typename InputIterator>
inline typename iterator_traits<InputIterator>::difference_type distance(InputIterator beg, InputIterator end) {
	return __distance(beg, end, iterator_traits<InputIterator>::iterator_category());
}

template <typename Category, typename T, typename Distance = ptrdiff_t, typename Pointer = T*, typename Reference = T&>
struct iterator {
	typedef Category	iterator_category;
	typedef T			value_type;
	typedef Distance	difference_type;
	typedef Pointer		pointer;
	typedef Reference	reference;
};

template <typename Container>
class back_insert_iterator {
protected:
	Container* container;
public:
	typedef output_iterator_tag iterator_category;
	typedef void value_type;
	typedef void difference_type;
	typedef void pointer;
	typedef void reference;

	explicit back_insert_iterator(Container& x):container(&x){}
	back_insert_iterator<Container>& operator=(const typename Container::value_type& value) {
		container->push_back(value);
		return *this;
	}

	back_insert_iterator<Container>& operator*() { return *this; }
	back_insert_iterator<Container>& operator++() { return *this; }
	back_insert_iterator<Container>& operator++(int) { return *this; }
	
};

template <typename Container>
inline back_insert_iterator<Container> back_inserter(Container& x) {
	return back_insert_iterator<Container>(x);
}

template <typename Container>
class front_insert_iterator {
protected:
	Container* container;
public:
	typedef output_iterator_tag iterator_category;
	typedef void value_type;
	typedef void difference_type;
	typedef void pointer;
	typedef void reference;

	explicit front_insert_iterator(Container& x):container(&x){}
	front_insert_iterator<Container>& operator=(const typename Container::value_type& value) {
		container->push_front(value);
		return *this;
	}

	front_insert_iterator<Container>& operator*() { return *this; }
	front_insert_iterator<Container>& operator++() { return *this; }
	front_insert_iterator<Container>& operator++(int) { return *this; }
	
};

template <typename Container>
inline front_insert_iterator<Container> front_inserter(Container& x) {
	return front_insert_iterator<Container>(x);
}

template <typename Container>
class insert_iterator {
protected:
	Container* container;
	typename Container::iterator iter;
public:
	typedef output_iterator_tag iterator_category;
	typedef void value_type;
	typedef void difference_type;
	typedef void pointer;
	typedef void reference;

	explicit insert_iterator(Container& x, typename Container::iterator i):
		container(&x), iter(i) {}
	insert_iterator<Container>& operator=(const typename Container::value_type& value) {
		iter = container->insert(iter, value);
		++iter;
		return *this;
	}

	insert_iterator<Container>& operator*() { return *this; }
	insert_iterator<Container>& operator++() { return *this; }
	insert_iterator<Container>& operator++(int) { return *this; }
	
};

template <typename Container, typename Iterator>
inline insert_iterator<Container> inserter(Container& x, Iterator) {
	return insert_iterator<Container>(x, Iterator);
}

template <typename Iterator>
class reverse_iterator {
protected:
	Iterator current;
public:
	typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
	typedef typename iterator_traits<Iterator>::value_type value_type;
	typedef typename iterator_traits<Iterator>::difference_type difference_type;
	typedef typename iterator_traits<Iterator>::pointer pointer;
	typedef typename iterator_traits<Iterator>::reference reference;

	typedef Iterator iterator_type;
	typedef reverse_iterator<Iterator> self;

	template <typename Iterator>
	friend ptrdiff_t operator-(const reverse_iterator<Iterator>& l, const reverse_iterator<Iterator>& r);
public:
	reverse_iterator() {}
	explicit reverse_iterator(iterator_type x):
		current(x) {}
	reverse_iterator(const self& x):
		current(x.current) {}

	iterator_type base() const { return current; }
	reference operator*() const {
		Iterator tmp = current;
		return *--tmp;
	}
	pointer operator->() const { return &(operator*()); }

	self& operator++() {
		--current;
		return *this;
	}

	self operator++(int) {
		self tmp = *this;
		--current;
		return tmp;
	}

	self& operator--() {
		++current;
		return *this;
	}
	
	self operator--(int) {
		self tmp = *this;
		++current;
		return tmp;
	}

	self operator+(difference_type n) const {
		return self(current - n);
	}

	self& operator+=(difference_type n) {
		current -= n;
		return *this;
	}

	self operator-(difference_type n) const {
		return self(current + n);
	}

	self& operator-=(difference_type n) {
		current += n;
		return *this;
	}

	reference operator[](difference_type n) const { return *(*this + n); }

	bool operator==(const self& x) const {
		return current == x.current;
	}

	bool operator!=(const self& x) const {
		return current != x.current;
	}

	bool operator<(const self& x) const {
		return current < x.current;
	}
	
	bool operator<=(const self& x) const {
		return current <= x.current;
	}
	
	bool operator>(const self& x) const {
		return current > x.current;
	}
	
	bool operator>=(const self& x) const {
		return current >= x.current;
	}
};

template <typename Iter>
ptrdiff_t operator-(const reverse_iterator<Iter>& l, const reverse_iterator<Iter>& r){
	return r.current - l.current;
}

}

#endif // !__LMSTL_ITERATOR_H__
