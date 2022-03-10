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
		template <class Up> reverse_iterator& operator=(const reverse_iterator<Up>& u) {
			if (this != &u) {
				this->current = u.base(); 
			}
			return *this;
		}

		/* Destrcutor */
		~reverse_iterator() {}

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
	template <class Iterator>
	bool operator==(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{ return lhs.base() == rhs.base(); }

	template <class Iterator>
	bool operator!=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{ return lhs.base() != rhs.base(); }

	template <class Iterator>
	bool operator<(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{ return lhs.base() < rhs.base(); }

	template <class Iterator>
	bool operator<=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{ return lhs.base() <= rhs.base(); }

	template <class Iterator>
	bool operator>(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{ return lhs.base() > rhs.base(); }

	template <class Iterator>
	bool operator>=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{ return lhs.base() >= rhs.base(); }

	template <class Iterator>
	reverse_iterator<Iterator> operator+(
			typename reverse_iterator<Iterator>::difference_type n,
			const reverse_iterator<Iterator>& rev_it)
	{ return reverse_iterator<Iterator>(rev_it.base() - n); }

	template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type operator- (
			const reverse_iterator<Iterator>& lhs,
			const reverse_iterator<Iterator>& rhs)
	{ return rhs.base() - lhs.base(); }



	/* ******************* */
	/*   Vector Iterator   */
	/* ******************* */

	template <typename Iterator>
	class vector_iterator
	{
	public:
		typedef Iterator                                                  	iterator_type;
		typedef typename iterator_traits<iterator_type>::iterator_category	iterator_category;
		typedef typename iterator_traits<iterator_type>::value_type       	value_type;
		typedef typename iterator_traits<iterator_type>::difference_type  	difference_type;
		typedef typename iterator_traits<iterator_type>::pointer          	pointer;
		typedef typename iterator_traits<iterator_type>::reference        	reference;
	
	private:
		iterator_type i;
	
	public:
		/* Constructors */
		vector_iterator() : i() {}
		vector_iterator(const vector_iterator& vi) : i(vi.base()) {}
		vector_iterator(iterator_type it) : i(it) {}
		template <class Up> vector_iterator(const vector_iterator<Up>& u, 
			typename enable_if<is_convertible<_Up, iterator_type>::value>::type* = 0)
			: i(u.base()) {}

		/* Assignment Operator */
		vector_iterator& operator=(const vector_iterator& vi) {
			if (this != &vi) {
				this->i = vi.base();
			}
			return *this;
		}

		/* Destrcutor */
		~vector_iterator() {}

		/* Member function */
		iterator_type base() const { return i; }

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
			typename __wrap_iter<Iter>::difference_type n, vector_iterator<Iter> vi)
	{ vi += n; return vi; }

	template <class Iter1, class Iter2>
	typename vector_iterator<Iter1>::difference_type operator- (
			const vector_iterator<Iter1>& lhs, const vector_iterator<Iter2>& rhs)
	{ return lhs.base() - rhs.base(); }

}

#endif