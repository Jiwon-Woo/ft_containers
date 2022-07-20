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
	template<>	struct is_map_iterator<std::bidirectional_iterator_tag> : public true_type {};



	/* **************** */
	/*   Map Iterator   */
	/* **************** */

	template<typename TreeIterator>
	class map_iterator
	{
	public:
		typedef typename TreeIterator::node_type                   node_type;

	private:
		TreeIterator i;
	
	public:
	    typedef bidirectional_iterator_tag          	iterator_category;
		typedef typename node_type::node_value_type 	value_type;
		typedef typename std::ptrdiff_t             	difference_type;
		typedef value_type&                         	reference;
		typedef value_type*                         	pointer;

		/* Constructors */
		map_iterator() : i(nullptr) {}
		map_iterator(TreeIterator ti) : i(ti) {}
		map_iterator(const map_iterator& mi) : i(mi.i) {}

		// /* Conversion operator */
		// operator map_iterator<const value_type> () const { 
		// 	return (map_iterator<const value_type>(this->i));
		// }

		/* Destrcutor */
		virtual ~map_iterator() {}

		/* Member function */
		TreeIterator base() const { return i; }

		/* Member function Operators */
		reference operator*() const { return *i; }
		pointer operator->() const { return &(operator*()); }
		map_iterator& operator++() { ++i; return *this; }
		map_iterator operator++(int) { map_iterator tmp(*this); ++(*this); return tmp; }
		map_iterator& operator--() { --i; return *this; }
		map_iterator operator--(int) { map_iterator tmp(*this); --(*this); return tmp; }

		/* Non-member function Operators */
		friend bool operator==(const map_iterator& x, const map_iterator& y)
		{ return x.i == y.i; }

		friend bool operator!=(const map_iterator& x, const map_iterator& y)
		{ return !(x.i == y.i); }
	};



	/* ***************** */
	/*   Tree Iterator   */
	/* ***************** */

	template <class T, class NodeType, class DiffType = std::ptrdiff_t>
	class tree_iterator
	{
		typedef NodeType                        	node_type;
		typedef typename node_type::node_pointer	node_pointer;
		// typedef typename node_pointer           	iter_pointer;

		node_pointer ptr;

	private:
		tree_next_iter(node_pointer x)
		{
			if (x->right != nullptr) { // 큰 집합들 중 가장 작은 것
				while (x->left != nullptr)
					x = x->left;
				return x;
			}
			while (x != x->parent->left) // x가 왼쪽 자식이 될때까지 거슬러 올라가서
				x = x->parent;
			return x->parent; // 그 부모를 반환
		}

		tree_prev_iter(node_pointer x)
		{
			if (x->left != nullptr) {
				while (x->right != nullptr)
					x = x->right;
				return x;
			}
			while (x == x->parent->left)
				x = x->parent;
			return x->parent;
		}

	public:
		typedef bidirectional_iterator_tag	iterator_category;
		typedef T                         	value_type;
		typedef DiffType                  	difference_type;
		typedef value_type&               	reference;
		typedef value_type*               	pointer;

		tree_iterator() : ptr(nullptr) {}
		tree_iterator(const tree_iterator& ti) : ptr(ti.get_np()) {}
		explicit tree_iterator(node_pointer p) : ptr(p) {}

		/* Conversion operator */
		operator tree_iterator<const value_type, node_type> () const { 
			return (tree_iterator<const value_type, node_type>(this->i));
		}

		reference operator*() const {return ptr->value;}
		pointer operator->() const {return &(this->operator*());}
		tree_iterator& operator++() { ptr = tree_next_iter(ptr); return *this; }
		tree_iterator operator++(int) { tree_iterator tmp(*this); ++(*this); return tmp; }
		tree_iterator& operator--() { ptr = tree_prev_iter(ptr); return *this; }

		tree_iterator operator--(int) {
			tree_iterator tmp(*this);
			--(*this);
			return tmp;
		}

		friend bool operator==(const tree_iterator& x, const tree_iterator& y)
		{return x.ptr == y.ptr;}
		friend bool operator!=(const tree_iterator& x, const tree_iterator& y)
		{return !(x == y);}

		node_pointer get_np() const { return ptr; }
	};

}

#endif