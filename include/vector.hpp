#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <memory>
#include <limits>
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
		typedef typename allocator_type::const_reference     	const_reference;
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
		allocator_type	_alloc;
		// size_type     	_size;
	
	public:
		/* Constructors */
		explicit vector(const allocator_type& alloc = allocator_type())
			: _begin(nullptr), _end(nullptr), _end_cap(nullptr), _alloc(alloc) {}
		explicit vector(size_type n, const value_type& val = value_type(),
						const allocator_type& alloc = allocator_type())
			: _begin(nullptr), _end(nullptr), _end_cap(nullptr), _alloc(alloc) {
			if (n > 0) {
				this->_begin = this->_end = _alloc.allocate(n);
				this->_end_cap = this->_begin + n;
				for (; this->_end != this->_end_cap; _end++) {
					_alloc.construct(this->_end, val);
				}
			}
		}
		template <class InputIterator>
		vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type())
			: _begin(nullptr), _end(nullptr), _end_cap(nullptr), _alloc(alloc) {
			difference_type n = last - first;
			if (n > 0) {
				this->_begin = this->_end = _alloc.allocate(n);
				this->_end_cap = this->_begin + n;
				for (InputIterator it = first; it != last; it++, _end++) {
					_alloc.construct(this->_end, *it);
				}
			}
		}
		vector (const vector& x)
			: _begin(nullptr), _end(nullptr), _end_cap(nullptr), _alloc(x._alloc) {
			size_type n = x.size();
			if (n > 0) {
				this->_begin = this->_end = _alloc.allocate(n);
				this->_end_cap = this->_begin + n;
				for (const_iterator it = x.begin(); it != x.end(); it++, _end++) {
					_alloc.construct(this->_end, *it);
				}
			}
		}

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
		size_type max_size() const { return std::numeric_limits<size_type>::max() / sizeof(value_type); }
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

		/* Allocator */
		// allocator_type get_allocator() const { return allocator_type(); }

	};

	template <class T, class Alloc>
	bool operator==(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

	template <class T, class Alloc>
	bool operator!=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

	template <class T, class Alloc>
	bool operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

	template <class T, class Alloc>
	bool operator<=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

	template <class T, class Alloc>
	bool operator>(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

	template <class T, class Alloc>
	bool operator>=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

	template <class T, class Alloc>
	void swap(vector<T,Alloc>& x, vector<T,Alloc>& y);
}

#endif