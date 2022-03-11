#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <memory>
#include "iterator.hpp"
#include "utils.hpp"

namespace ft
{
	template<typename T, typename Alloc = std::allocator<T> >
	class vector
	{
	public:
		typedef T                                            	value_type;
		typedef Alloc                                        	allocator_type;
		typedef std::ptrdiff_t                               	difference_type;
		typedef std::size_t                                  	size_type;
		typedef typename allocator_type::reference           	reference;
		typedef typename allocator_type::const_pointer       	const_reference;
		typedef typename allocator_type::pointer             	pointer;
		typedef typename allocator_type::const_pointer       	const_pointer;
		typedef ft::vector_iterator<pointer>                 	iterator;
		typedef ft::vector_iterator<const_pointer>           	const_iterator;
		typedef typename ft::reverse_iterator<iterator>      	reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator>	const_reverse_iterator;
	
	protected:
		pointer       	_begin;
		pointer       	_end;
		pointer       	_end_cap;
		size_type     	_size;
		allocator_type	alloc;
	
	public:
		/* Constructors */
		vector()
			: _begin(nullptr), _end(nullptr), _end_cap(nullptr), _size(0), alloc(allocator_type()) {}
		explicit vector (const allocator_type& alloc)
			: _begin(nullptr), _end(nullptr), _end_cap(nullptr), _size(0), alloc(alloc) {}
		explicit vector (size_type n, const value_type& val = value_type(),
						const allocator_type& alloc = allocator_type())
			: _begin(nullptr), _end(nullptr), _end_cap(nullptr), alloc(alloc) {
			if (n > 0) {
				this->_size = n;
				this->_begin = this->_end = alloc.allocate(n);
				this->_end_cap = this->_begin + n;
				// this->__begin_ = this->__end_ = __alloc_traits::allocate(this->__alloc(), __n);
				// this->__end_cap() = this->__begin_ + __n;
				// __annotate_new(0);
			}
		}
		template <class InputIterator>
		vector (InputIterator first, InputIterator last,
				const allocator_type& alloc = allocator_type());
		vector (const vector& x);

		/* Destructors */
		~vector() {}

		/* Assignment */
		vector& operator= (const vector& x);

		/* Iterators */
		iterator begin() { return iterator(this->_begin); }
		const_iterator begin() const { return const_iterator(this->_begin); }
		iterator end() { return iterator(this->_end); }
		const_iterator end() const { return const_iterator(this->_end); }
		reverse_iterator rbegin() { return reverse_iterator(this->end()); }
		const_reverse_iterator rbegin() const { return const_reverse_iterator(this->end()); }
		reverse_iterator rend() { return reverse_iterator(this->begin()); }
		const_reverse_iterator rend() const { return const_reverse_iterator(this->begin()); }

		/* Capacity */
		size_type size() const { return static_cast<size_type>(this->_end - this->_begin); }
		size_type capacity() const { return static_cast<size_type>(this->_end_cap - this->_begin); }
		bool empty() const { return this->_begin == this->_end; }
		size_type max_size() const {
			// return _VSTD::min<size_type>(__alloc_traits::max_size(this->__alloc()),
			// 							numeric_limits<difference_type>::max());
		}
		void resize (size_type n, value_type val = value_type()) {
			// size_type s = size();
			// if (s < n)
			// 	this->__append(n - s, val);
			// else if (__cs > n)
			// 	this->__destruct_at_end(this->_begin + n);
		}
		void reserve (size_type n) {
			if (n > this->capacity()) {
				// allocator_type& __a = this->__alloc();
				// __split_buffer<value_type, allocator_type&> __v(__n, size(), __a);
				// __swap_out_circular_buffer(__v);
			}
		}

		/* Element access */
		reference operator[] (size_type n) {
			// _LIBCPP_ASSERT(__n < size(), "vector[] index out of bounds");
			return this->_begin[n];
		}
		const_reference operator[] (size_type n) const {
			// _LIBCPP_ASSERT(__n < size(), "vector[] index out of bounds");
			return this->_begin[n];
		}
		reference at (size_type n) {
			// if (n >= size())
			// 	this->__throw_out_of_range();
			return this->_begin[n];
		}
		const_reference at (size_type n) const {
			// if (n >= size())
			// 	this->__throw_out_of_range();
			return this->_begin[n];
		}
		reference front() {
			// _LIBCPP_ASSERT(!empty(), "front() called for empty vector");
			return *(this->_begin);
		}
		const_reference front() const {
			// _LIBCPP_ASSERT(!empty(), "front() called for empty vector");
			return *(this->_begin);
		}
		reference back() {
			// _LIBCPP_ASSERT(!empty(), "back() called for empty vector");
			return *(this->_end - 1);
		}
		const_reference back() const {
			// _LIBCPP_ASSERT(!empty(), "back() called for empty vector");
			return *(this->_end - 1);
		}
		
		/* Modifiers */
		template <class InputIterator>
		void assign (InputIterator first, InputIterator last);
		void assign (size_type n, const value_type& val);
		void push_back (const value_type& val);
		void pop_back();
		iterator insert (iterator position, const value_type& val);
		void insert (iterator position, size_type n, const value_type& val);
		template <class InputIterator>
		void insert (iterator position, InputIterator first, InputIterator last);
		iterator erase (iterator position);
		iterator erase (iterator first, iterator last);
		void swap (vector& x);
		void clear();

	};
}

#endif