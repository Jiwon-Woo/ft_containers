#ifndef STACK_HPP
# define STACK_HPP

#include "vector.hpp"

namespace ft
{
	template <typename T, class Container = ft::vector<T> >
	class stack
	{
	public:
		typedef T          	value_type;
		typedef Container  	container_type;
		typedef std::size_t	size_type;
	
	protected:
		container_type c;
	
	public:
		/* Constructors */
		explicit stack (const container_type& ctnr = container_type()) : c(ctnr) {}
		stack(const stack& other) : c(other.c) {}

		/* Destructors */
		virtual ~stack() {}

		/* Assignment */
		stack& operator=(const stack& other) {
			if (this != &other) {
				c = other.c;
			}
			return *this;
		}

		/* Member functions */
		bool empty() const { return this->c.empty(); }
		size_type size() const { return this->c.size(); }
		value_type& top() { return this->c.back(); }
		const value_type& top() const { return this->c.back(); }
		void push (const value_type& val) { this->c.push_back(val); }
		void pop() { this->c.pop_back(); }

		/* Relational Operators */
		friend bool operator==(const stack& x, const stack& y)
		{ return x.c == y.c; }
		friend bool operator<(const stack& x, const stack& y)
		{ return x.c < y.c; }
		friend bool operator!=(const stack& x, const stack& y)
		{ return !(x == y); }
		friend bool operator>(const stack& x, const stack& y)
		{ return y < x; }
		friend bool operator>=(const stack& x, const stack& y)
		{ return !(x < y); }
		friend bool operator<=(const stack& x, const stack& y)
		{ return !(y < x); }
	};

}

#endif