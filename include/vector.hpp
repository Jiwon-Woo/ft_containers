#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <memory>
#include "iterator.hpp"

namespace ft
{
	template<typename T, typename Alloc = std::allocator<T> >
	class vector
	{
	protected:
		/* implement vector iterator */
		class vector_iterator
			: public ft::iterator<ft::random_access_iterator_tag, T>
		{
		protected:
			typedef typename vector_iterator::value_type       	value_type;
			typedef typename vector_iterator::difference_type  	difference_type;
			typedef typename vector_iterator::pointer          	pointer;
			typedef typename vector_iterator::reference        	reference;
			typedef typename vector_iterator::iterator_category	iterator_category;
			
			pointer	ptr;

		public:
			vector_iterator() : ptr(0) {}
			vector_iterator(vector_iterator const &rai) : ptr(rai.ptr) {}
			virtual ~vector_iterator() {}
			vector_iterator(pointer ptr) : ptr(ptr) {}
			
			vector_iterator& operator=(vector_iterator const &rai) {
				ptr = rai.ptr;
				return *this;
			};

			bool operator==(vector_iterator const &rai) const { return ptr == rai.ptr; }
			bool operator!=(vector_iterator const &rai) const { return ptr != rai.ptr; }
			
			reference operator*() const { return *ptr; }
			pointer operator->() const { return &(operator*()); }

			vector_iterator& operator++() { ++ptr; return *this; }
			vector_iterator  operator++(int) { vector_iterator tmp(*this); ++ptr; return tmp; }

			vector_iterator& operator--() {--ptr; return *this;}
			vector_iterator  operator--(int) { vector_iterator tmp(*this); --ptr; return tmp; }

			vector_iterator  operator+ (difference_type n) const { return vector_iterator(ptr + n); }
			vector_iterator  operator- (difference_type n) const { return vector_iterator(ptr - n); }

			bool operator<(vector_iterator const &rai) const { return ptr < rai.ptr; }
			bool operator>(vector_iterator const &rai) const { return ptr > rai.ptr; }
			bool operator<=(vector_iterator const &rai) const { return ptr <= rai.ptr; }
			bool operator>=(vector_iterator const &rai) const { return ptr >= rai.ptr; }

			vector_iterator& operator+=(difference_type n) { ptr += n; return *this; }
			vector_iterator& operator-=(difference_type n) { ptr -= n; return *this; }

			reference operator[](difference_type n) const { return *(*this + n); }

		};
	
	public:
		typedef T                                            	value_type;
		typedef Alloc                                        	allocator_type;
		typedef std::ptrdiff_t                               	difference_type;
		typedef std::size_t                                  	size_type;
		typedef value_type&                                  	reference;
		typedef const value_type&                            	const_reference;
		typedef typename allocator_type::pointer             	pointer;
		typedef typename allocator_type::const_pointer       	const_pointer;
		typedef vector_iterator                              	iterator;
		typedef vector_iterator                              	const_iterator;
		typedef typename ft::reverse_iterator<iterator>      	reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator>	const_reverse_iterator;
	};
}

#endif