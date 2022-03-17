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

		class _throw_out_of_range : public std::exception
		{
		public:
			virtual const char* what() const throw() {
				return "vector index out of bounds";
			}
		};

		class _throw_length_error : public std::exception
		{
		public:
			virtual const char* what() const throw() {
				return "vector length out of max size";
			}
		};


	public:
		/* **************** */
		/*   Constructors   */
		/* **************** */

		explicit vector(const allocator_type& alloc = allocator_type())
			: _begin(nullptr), _end(nullptr), _end_cap(nullptr), _alloc(alloc) {}

		explicit vector(size_type n, const value_type& val = value_type(),
						const allocator_type& alloc = allocator_type())
			: _begin(nullptr), _end(nullptr), _end_cap(nullptr), _alloc(alloc) {
			if (n > 0) {
				if (n > this->max_size())
					throw vector::_throw_length_error();
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
				if (n > this->max_size())
					throw vector::_throw_length_error();
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
				if (n > this->max_size())
					throw vector::_throw_length_error();
				this->_begin = this->_end = _alloc.allocate(n);
				this->_end_cap = this->_begin + n;
				for (const_iterator it = x.begin(); it != x.end(); it++, _end++) {
					_alloc.construct(this->_end, *it);
				}
			}
		}


		/* *************** */
		/*   Destructors   */
		/* *************** */

		~vector() {
			this->clear();
			_alloc.deallocate(this->_begin, this->capacity());
		}


		/* ************** */
		/*   Assignment   */
		/* ************** */

		vector& operator=(const vector& x) {
			if (this != &x){

				size_type copy_size = x.size();
				size_type origin_size = this->size();
				size_type origin_cap = this->capacity();

				if (copy_size <= origin_cap) {
					for (size_type i = 0; i < copy_size; i++) { (*this)[i] = x[i]; }
					for (size_type i = 0; i < origin_size - copy_size; i++) {
						this->_end--;
						_alloc.destroy(this->_end);
					}
				} else {
					this->clear();
					_alloc.deallocate(this->_begin, origin_cap);
					this->_begin = this->_end = _alloc.allocate(copy_size);
					this->_end_cap = this->_begin + copy_size;
					for (const_iterator it = x.begin(); it != x.end(); it++, _end++) {
						_alloc.construct(this->_end, *it);
					}
				}
			}
			return *this;
		}


		/* ************* */
		/*   Iterators   */
		/* ************* */

		iterator begin() { return iterator(this->_begin); }
		const_iterator begin() const { return const_iterator(this->_begin); }
		iterator end() { return iterator(this->_end); }
		const_iterator end() const { return const_iterator(this->_end); }
		reverse_iterator rbegin() { return reverse_iterator(this->end()); }
		const_reverse_iterator rbegin() const { return const_reverse_iterator(this->end()); }
		reverse_iterator rend() { return reverse_iterator(this->begin()); }
		const_reverse_iterator rend() const { return const_reverse_iterator(this->begin()); }


		/* ************ */
		/*   Capacity   */
		/* ************ */

		size_type size() const { return static_cast<size_type>(this->_end - this->_begin); }
		size_type capacity() const { return static_cast<size_type>(this->_end_cap - this->_begin); }
		bool empty() const { return this->_begin == this->_end; }
		size_type max_size() const { return std::numeric_limits<size_type>::max() / sizeof(value_type); }
		
		void resize (size_type n, value_type val = value_type()) {
			if (n > this->max_size())
				throw vector::_throw_length_error();

			size_type s = this->size();
			if (s < n) {
				size_type diff = n - s;
				if (static_cast<size_type>(this->_end_cap - this->_end) >= diff) {
					for (size_type i = 0; i < diff; i++, _end++) {
						_alloc.construct(this->_end, val);
					}
				} else {
					size_type diff = n - this->size();
					size_type temp_cap = max_size() < capacity() * 2 ? max_size() : capacity() * 2;
					size_type new_cap = n > temp_cap ? n : temp_cap;
					this->reserve(new_cap);
					for (size_type i = 0; i < diff; i++, _end++) {
						_alloc.construct(this->_end, val);
					}
				}
			} else if (s > n) {
				size_type diff = s - n;
				for (size_type i = 0; i < diff ; i++) {
					this->_end--;
					_alloc.destroy(this->_end);
				}
			}
		}

		void reserve (size_type n) {
			if (n > this->capacity()) {

				if (n > this->max_size())
					throw vector::_throw_length_error();

				pointer new_begin, new_end;
				new_begin = new_end = _alloc.allocate(n);
				for (iterator it = this->begin(); it != this->end(); it++, new_end++) {
					_alloc.construct(new_end, *it);
				}

				this->clear();
				_alloc.deallocate(this->_begin, this->capacity());
				
				this->_begin = new_begin;
				this->_end = new_end;
				this->_end_cap = new_begin + n;
			}
		}


		/* ****************** */
		/*   Element access   */
		/* ****************** */

		reference operator[] (size_type n) {
			if (n >= size())
				throw vector::_throw_out_of_range();
			return *(this->_begin + n);
		}

		const_reference operator[] (size_type n) const {
			if (n >= size())
				throw vector::_throw_out_of_range();
			return *(this->_begin + n);
		}

		reference at (size_type n) {
			if (n >= size())
				throw vector::_throw_out_of_range();
			return *(this->_begin + n);
		}

		const_reference at (size_type n) const {
			if (n >= size())
				throw vector::_throw_out_of_range();
			return *(this->_begin + n);
		}

		reference front() { return *(this->_begin); }
		const_reference front() const { return *(this->_begin); }
		reference back() { return *(this->_end - 1); }
		const_reference back() const { return *(this->_end - 1); }


		/* ************* */
		/*   Modifiers   */
		/* ************* */

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
		
		void clear() {
			size_type n = this->size();
			for (size_type st = 0; st < n; st++) {
				this->_end--;
				_alloc.destroy(this->_end);
			}
		}

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