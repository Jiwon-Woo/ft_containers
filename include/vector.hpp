#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <memory>
#include "iterator.hpp"

namespace ft
{
	// Alloc의 default 값 = std::allocator<T>
	template<typename T, typename Alloc = std::allocator<T> >
	class vector
	{
	private:
		typedef T											value_type;
		typedef Alloc										allocator_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;

	public:
		vector();
		vector(vector<T> const &v);
		vector<T>& operator=(vector<T> const &v);
		~vector();
	};
}

#endif