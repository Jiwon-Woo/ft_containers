#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <memory>
// #include <cstddef>
#include "iterator.hpp"

namespace ft
{
	template<typename T, typename Alloc = std::allocator<T> >
	class vector
	{
	private:
		class vector_iterator
		{
		public:
			typedef ft::random_access_iterator_tag	iterator_category;
		};

	public:
		typedef T                                     	value_type;
		typedef Alloc                                 	allocator_type;
		typedef std::ptrdiff_t                        	difference_type;
		typedef std::size_t                           	size_type;
		typedef value_type&                           	reference;
		typedef const value_type&                     	const_reference;
		typedef typename allocator_type::pointer      	pointer;
		typedef typename allocator_type::const_pointer	const_pointer;

		typedef vector_iterator                       	iterator;
		typedef vector_iterator                       	const_iterator;
		
		typedef typename ft::reverse_iterator<iterator>      	reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator>	reverse_iterator;
	};
}

#endif