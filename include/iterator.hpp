#ifndef ITERATOR_HPP
# define ITERATOR_HPP

#include <cstddef>
#include <iterator>
#include "utils.hpp"

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
	public:
		typedef Iterator                                             	iterator_type;
		typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
		typedef typename iterator_traits<Iterator>::value_type       	value_type;
		typedef typename iterator_traits<Iterator>::difference_type  	difference_type;
		typedef typename iterator_traits<Iterator>::pointer          	pointer;
		typedef typename iterator_traits<Iterator>::reference        	reference;

	protected:
		iterator_type	current;
	
	public:
		/* Constructors */
		reverse_iterator() : current() {}
		explicit reverse_iterator(iterator_type it) : current(it) {}
		template <class Up> reverse_iterator(const reverse_iterator<Up>& u) : current(u.base()) {}

		/* Assignment Operator */
		// template <class Up> reverse_iterator& operator=(const reverse_iterator<Up>& u) {
		// 	if (this != &u) {
		// 		this->current = u.base(); 
		// 	}
		// 	return *this;
		// }

		/* Destrcutor */
		virtual ~reverse_iterator() {}

		/* Member function */
		iterator_type base() const { return current; }

		/* Member function Operators */
		reference operator*() const { Iterator tmp = current; return *--tmp; }
		pointer operator->() const { return &(operator*()); }
		reverse_iterator& operator++() { --current; return *this; }
		reverse_iterator operator++(int) { reverse_iterator tmp(*this); --current; return tmp; }
		reverse_iterator& operator--() { ++current; return *this; }
		reverse_iterator operator--(int) { reverse_iterator tmp(*this); ++current; return tmp; }
		reverse_iterator operator+(difference_type n) const { return reverse_iterator(current - n); }
		reverse_iterator& operator+=(difference_type n) { current -= n; return *this; }
		reverse_iterator operator-(difference_type n) const { return reverse_iterator(current + n); }
		reverse_iterator& operator-=(difference_type n) { current += n; return *this; }
		reference operator[](difference_type n) const { return *(*this + n); }
	};

	/* Non-member function Operators */
	template <typename Iter1, typename Iter2>
	bool operator==(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs)
	{ return lhs.base() == rhs.base(); }

	template <typename Iter1, typename Iter2>
	bool operator!=(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs)
	{ return lhs.base() != rhs.base(); }

	template <typename Iter1, typename Iter2>
	bool operator<(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs)
	{ return lhs.base() > rhs.base(); }

	template <typename Iter1, typename Iter2>
	bool operator<=(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs)
	{ return lhs.base() >= rhs.base(); }

	template <typename Iter1, typename Iter2>
	bool operator>(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs)
	{ return lhs.base() < rhs.base(); }

	template <typename Iter1, typename Iter2>
	bool operator>=(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs)
	{ return lhs.base() <= rhs.base(); }

	template <typename Iterator>
	reverse_iterator<Iterator> operator+ (
			typename reverse_iterator<Iterator>::difference_type n,
			const reverse_iterator<Iterator>& rev_it)
	{ return reverse_iterator<Iterator>(rev_it.base() - n); }

	template <typename Iter1, typename Iter2>
	typename reverse_iterator<Iter1>::difference_type operator- (
			const reverse_iterator<Iter1>& lhs,
			const reverse_iterator<Iter2>& rhs)
	{ return rhs.base() - lhs.base(); }



	/* ********************** */
	/*   is_vector_iterator   */
	/* ********************** */

	template<typename T>
	struct is_vector_iterator : public false_type {};

	template<>	struct is_vector_iterator<ft::random_access_iterator_tag> : public true_type {};
	template<>	struct is_vector_iterator<std::random_access_iterator_tag> : public true_type {};
	template<>	struct is_vector_iterator<ft::bidirectional_iterator_tag> : public true_type {};
	template<>	struct is_vector_iterator<std::bidirectional_iterator_tag> : public true_type {};



	/* ******************* */
	/*   Vector Iterator   */
	/* ******************* */

	template <typename T>
	class vector_iterator
	{
	public:
		typedef std::ptrdiff_t                	difference_type;
		typedef T                             	value_type;
		typedef T*                            	pointer;
		typedef T&                            	reference;
		typedef ft::random_access_iterator_tag	iterator_category;

	private:
		pointer i;
	
	public:
		/* Constructors */
		vector_iterator() : i(nullptr) {}
		vector_iterator(const vector_iterator& vi) : i(vi.base()) {}
		vector_iterator(pointer it) : i(it) {}
		template <class Up> vector_iterator(const vector_iterator<Up>& u,
				typename ft::enable_if<is_vector_iterator<typename Up::iterator_category>::value>::type* = nullptr)
			: i(u.base()) {}

		/* Assignment Operator */
		vector_iterator& operator=(const vector_iterator& vi) {
			if (this != &vi) {
				this->i = vi.base();
			}
			return *this;
		}

		/* Conversion operator */
		operator vector_iterator<const value_type> () const { 
			return (vector_iterator<const value_type>(this->i));
		}

		/* Destrcutor */
		virtual ~vector_iterator() {}

		/* Member function */
		pointer base() const { return i; }

		/* Member function Operators */
		reference operator*() const { return *i; }
		pointer operator->() const { return &(operator*()); }
		vector_iterator& operator++() { ++i; return *this; }
		vector_iterator operator++(int) { vector_iterator tmp(*this); ++(*this); return tmp; }
		vector_iterator& operator--() { --i; return *this; }
		vector_iterator operator--(int) { vector_iterator tmp(*this); --(*this); return tmp; }
		vector_iterator operator+(difference_type n) const { vector_iterator w(*this); w += n; return w; }
		vector_iterator& operator+=(difference_type n) { i += n; return *this; }
		vector_iterator operator-(difference_type n) const { return *this + (-n); }
		vector_iterator& operator-=(difference_type n) { *this += -n; return *this; }
		reference operator[](difference_type n) const { return i[n]; }
	};

	/* Non-member function Operators */
	template <class Iter1, class Iter2>
	bool operator==(const vector_iterator<Iter1>& lhs, const vector_iterator<Iter2>& rhs)
	{ return lhs.base() == rhs.base(); }

	template <class Iter1, class Iter2>
	bool operator<(const vector_iterator<Iter1>& lhs, const vector_iterator<Iter2>& rhs)
	{ return lhs.base() < rhs.base(); }

	template <class Iter1, class Iter2>
	bool operator!=(const vector_iterator<Iter1>& lhs, const vector_iterator<Iter2>& rhs)
	{ return !(lhs == rhs); }

	template <class Iter1, class Iter2>
	bool operator>(const vector_iterator<Iter1>& lhs, const vector_iterator<Iter2>& rhs)
	{ return (rhs < lhs); }

	template <class Iter1, class Iter2>
	bool operator>=(const vector_iterator<Iter1>& lhs, const vector_iterator<Iter2>& rhs)
	{ return !(lhs < rhs); }

	template <class Iter1, class Iter2>
	bool operator<=(const vector_iterator<Iter1>& lhs, const vector_iterator<Iter2>& rhs)
	{ return !(rhs < lhs); }

	template <class Iter>
	vector_iterator<Iter> operator+ (
			typename vector_iterator<Iter>::difference_type n, vector_iterator<Iter> vi)
	{ vi += n; return vi; }

	template <class Iter1, class Iter2>
	typename vector_iterator<Iter1>::difference_type operator- (
			const vector_iterator<Iter1>& lhs, const vector_iterator<Iter2>& rhs)
	{ return lhs.base() - rhs.base(); }



	/* ******************* */
	/*   is_map_iterator   */
	/* ******************* */

	template<typename T>
	struct is_map_iterator : public false_type {};

	template<>	struct is_map_iterator<ft::bidirectional_iterator_tag> : public true_type {};



	/* **************** */
	/*   Map Iterator   */
	/* **************** */

	template<typename TreeIterator>
	class map_iterator
	{
	public:
		typedef typename TreeIterator::NodeTypes                   NodeTypes;
		typedef typename TreeIterator::pointer_traits             pointer_traits;

	private:
		TreeIterator i;
	
	public:
		/* Constructors */
		map_iterator() : i(nullptr) {}
		map_iterator(TreeIterator ti) : i(ti) {}

		/* Conversion operator */
		operator map_iterator<const value_type> () const { 
			return (map_iterator<const value_type>(this->i));
		}

		// __map_const_iterator(__map_iterator<
        // typename _TreeIterator::__non_const_iterator> __i) _NOEXCEPT
        // : __i_(__i.__i_) {}

		/* Destrcutor */
		virtual ~map_iterator() {}

		/* Member function */
		pointer base() const { return i; }

		/* Member function Operators */
		reference operator*() const { return *i; }
		pointer operator->() const { return &(operator*()); }
		map_iterator& operator++() { ++i; return *this; }
		map_iterator operator++(int) { map_iterator tmp(*this); ++(*this); return tmp; }
		map_iterator& operator--() { --i; return *this; }
		map_iterator operator--(int) { map_iterator tmp(*this); --(*this); return tmp; }

		/* Non-member function Operators */
		friend template <class Iter1, class Iter2>
		bool operator==(const map_iterator<Iter1>& lhs, const map_iterator<Iter2>& rhs)
		{ return lhs.i == rhs.i; }

		friend template <class Iter1, class Iter2>
		bool operator!=(const map_iterator<Iter1>& lhs, const map_iterator<Iter2>& rhs)
		{ return !(lhs.i == rhs.i); }
	};



	/* ***************** */
	/*   Tree Iterator   */
	/* ***************** */

	template <class _Tp, class _NodePtr, class _DiffType>
	class _LIBCPP_TEMPLATE_VIS __tree_iterator
	{
		typedef __tree_node_types<_NodePtr>                     _NodeTypes;
		typedef _NodePtr                                        __node_pointer;
		typedef typename _NodeTypes::__node_base_pointer        __node_base_pointer;
		typedef typename _NodeTypes::__end_node_pointer         __end_node_pointer;
		typedef typename _NodeTypes::__iter_pointer             __iter_pointer;
		typedef pointer_traits<__node_pointer> __pointer_traits;

		__iter_pointer __ptr_;

	public:
		typedef bidirectional_iterator_tag                     iterator_category;
		typedef _Tp                                            value_type;
		typedef _DiffType                                      difference_type;
		typedef value_type&                                    reference;
		typedef typename _NodeTypes::__node_value_type_pointer pointer;

		_LIBCPP_INLINE_VISIBILITY __tree_iterator() _NOEXCEPT
	#if _LIBCPP_STD_VER > 11
		: __ptr_(nullptr)
	#endif
		{}

		_LIBCPP_INLINE_VISIBILITY reference operator*() const
			{return __get_np()->__value_;}
		_LIBCPP_INLINE_VISIBILITY pointer operator->() const
			{return pointer_traits<pointer>::pointer_to(__get_np()->__value_);}

		_LIBCPP_INLINE_VISIBILITY
		__tree_iterator& operator++() {
		__ptr_ = static_cast<__iter_pointer>(
			__tree_next_iter<__end_node_pointer>(static_cast<__node_base_pointer>(__ptr_)));
		return *this;
		}
		_LIBCPP_INLINE_VISIBILITY
		__tree_iterator operator++(int)
			{__tree_iterator __t(*this); ++(*this); return __t;}

		_LIBCPP_INLINE_VISIBILITY
		__tree_iterator& operator--() {
		__ptr_ = static_cast<__iter_pointer>(__tree_prev_iter<__node_base_pointer>(
			static_cast<__end_node_pointer>(__ptr_)));
		return *this;
		}
		_LIBCPP_INLINE_VISIBILITY
		__tree_iterator operator--(int)
			{__tree_iterator __t(*this); --(*this); return __t;}

		friend _LIBCPP_INLINE_VISIBILITY
			bool operator==(const __tree_iterator& __x, const __tree_iterator& __y)
			{return __x.__ptr_ == __y.__ptr_;}
		friend _LIBCPP_INLINE_VISIBILITY
			bool operator!=(const __tree_iterator& __x, const __tree_iterator& __y)
			{return !(__x == __y);}

	private:
		_LIBCPP_INLINE_VISIBILITY
		explicit __tree_iterator(__node_pointer __p) _NOEXCEPT : __ptr_(__p) {}
		_LIBCPP_INLINE_VISIBILITY
		explicit __tree_iterator(__end_node_pointer __p) _NOEXCEPT : __ptr_(__p) {}
		_LIBCPP_INLINE_VISIBILITY
		__node_pointer __get_np() const { return static_cast<__node_pointer>(__ptr_); }
		template <class, class, class> friend class __tree;
		template <class, class, class> friend class _LIBCPP_TEMPLATE_VIS __tree_const_iterator;
		template <class> friend class _LIBCPP_TEMPLATE_VIS __map_iterator;
		template <class, class, class, class> friend class _LIBCPP_TEMPLATE_VIS map;
		template <class, class, class, class> friend class _LIBCPP_TEMPLATE_VIS multimap;
		template <class, class, class> friend class _LIBCPP_TEMPLATE_VIS set;
		template <class, class, class> friend class _LIBCPP_TEMPLATE_VIS multiset;
	};

}

#endif