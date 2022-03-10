#ifndef ITERATOR_HPP
# define ITERATOR_HPP

#include <cstddef>

namespace ft
{

	/* ***************** */
	/*   Category tags   */
	/* ***************** */

	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag : public input_iterator_tag {};
	struct bidirectional_iterator_tag : public forward_iterator_tag {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};



	/* ************ */
	/*   Iterator   */
	/* ************ */

	template <typename Category,
				typename T,
				typename Distance = std::ptrdiff_t,
				typename Pointer = T*,
				typename Reference = T&>
	struct iterator
	{
		typedef T        	value_type;
		typedef Distance 	difference_type;
		typedef Pointer  	pointer;
		typedef Reference	reference;
		typedef Category 	iterator_category;
	};



	/* ******************* */
	/*   Iterator traits   */
	/* ******************* */

	template <typename Iterator>
	struct iterator_traits
	{
		typedef typename Iterator::difference_type  	difference_type;
		typedef typename Iterator::value_type       	value_type;
		typedef typename Iterator::pointer          	pointer;
		typedef typename Iterator::reference        	reference;
		typedef typename Iterator::iterator_category	iterator_category;
	};

	template <typename T>
	struct iterator_traits<T*>
	{
		typedef std::ptrdiff_t            	difference_type;
		typedef T                         	value_type;
		typedef T*                        	pointer;
		typedef T&                        	reference;
		typedef random_access_iterator_tag	iterator_category;
	};

	template <typename T>
	struct iterator_traits<const T*>
	{
		typedef std::ptrdiff_t            	difference_type;
		typedef T                         	value_type;
		typedef const T*                  	pointer;
		typedef const T&                  	reference;
		typedef random_access_iterator_tag	iterator_category;
	};



	/* ******************** */
	/*   Reverse Iterator   */
	/* ******************** */

	template <typename Iterator>
	class reverse_iterator
		: public iterator<typename iterator_traits<Iterator>::iterator_category,
						typename iterator_traits<Iterator>::value_type,
						typename iterator_traits<Iterator>::difference_type,
						typename iterator_traits<Iterator>::pointer,
						typename iterator_traits<Iterator>::reference>
	{
	protected:
		Iterator	current;
	
	public:
		/* Member types */
		typedef Iterator                                             	iterator_type;
		typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
		typedef typename iterator_traits<Iterator>::value_type       	value_type;
		typedef typename iterator_traits<Iterator>::difference_type  	difference_type;
		typedef typename iterator_traits<Iterator>::pointer          	pointer;
		typedef typename iterator_traits<Iterator>::reference        	reference;

		/* Constructs */
		reverse_iterator() : current() {}
		explicit reverse_iterator (iterator_type it) : current(it) {}
		template <class Iter> reverse_iterator (const reverse_iterator<Iter>& rev_it) : current(rev_it.base()) {}
		~reverse_iterator() {}

		/* Member function */
		iterator_type base() const { return current; }

		/* Operators */
		reference operator*() const {
			Iterator tmp = current;
			return *--tmp;
		}
		
		pointer operator->() const {
			return &(operator*());
		}
		
		reverse_iterator& operator++() {
			--current;
			return *this;
		}
		
		reverse_iterator operator++(int) {
			reverse_iterator tmp(*this);
			--current;
			return tmp;
		}
		
		reverse_iterator& operator--() {
			++current;
			return *this;
		}
		
		reverse_iterator operator--(int) {
			reverse_iterator tmp(*this);
			++current;
			return tmp;
		}
		
		reverse_iterator operator+ (difference_type n) const {
			return reverse_iterator(current - n);
		}
		
		reverse_iterator& operator+=(difference_type n) {
			current -= n;
			return *this;
		}
		
		reverse_iterator operator- (difference_type n) const {
			return reverse_iterator(current + n);
		}
		
		reverse_iterator& operator-=(difference_type n) {
			current += n;
			return *this;
		}
		
		reference operator[](difference_type n) const {
			return *(*this + n);
		}
	};

	template <class _Iter1, class _Iter2>
	inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX14
	bool
	operator==(const reverse_iterator<_Iter1>& __x, const reverse_iterator<_Iter2>& __y)
	{
		return __x.base() == __y.base();
	}

	template <class _Iter1, class _Iter2>
	inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX14
	bool
	operator<(const reverse_iterator<_Iter1>& __x, const reverse_iterator<_Iter2>& __y)
	{
		return __x.base() > __y.base();
	}

	template <class _Iter1, class _Iter2>
	inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX14
	bool
	operator!=(const reverse_iterator<_Iter1>& __x, const reverse_iterator<_Iter2>& __y)
	{
		return __x.base() != __y.base();
	}

	template <class _Iter1, class _Iter2>
	inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX14
	bool
	operator>(const reverse_iterator<_Iter1>& __x, const reverse_iterator<_Iter2>& __y)
	{
		return __x.base() < __y.base();
	}

	template <class _Iter1, class _Iter2>
	inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX14
	bool
	operator>=(const reverse_iterator<_Iter1>& __x, const reverse_iterator<_Iter2>& __y)
	{
		return __x.base() <= __y.base();
	}

	template <class _Iter1, class _Iter2>
	inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX14
	bool
	operator<=(const reverse_iterator<_Iter1>& __x, const reverse_iterator<_Iter2>& __y)
	{
		return __x.base() >= __y.base();
	}

	#ifndef _LIBCPP_CXX03_LANG
	template <class _Iter1, class _Iter2>
	inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX14
	auto
	operator-(const reverse_iterator<_Iter1>& __x, const reverse_iterator<_Iter2>& __y)
	-> decltype(__y.base() - __x.base())
	{
		return __y.base() - __x.base();
	}
	#else
	template <class _Iter1, class _Iter2>
	inline _LIBCPP_INLINE_VISIBILITY
	typename reverse_iterator<_Iter1>::difference_type
	operator-(const reverse_iterator<_Iter1>& __x, const reverse_iterator<_Iter2>& __y)
	{
		return __y.base() - __x.base();
	}
	#endif

	template <class _Iter>
	inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_AFTER_CXX14
	reverse_iterator<_Iter>
	operator+(typename reverse_iterator<_Iter>::difference_type __n, const reverse_iterator<_Iter>& __x)
	{
		return reverse_iterator<_Iter>(__x.base() - __n);
	}

}

#endif