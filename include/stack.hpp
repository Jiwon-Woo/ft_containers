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
		/* **************** */
		/*   Constructors   */
		/* **************** */
		
		explicit stack (const container_type& ctnr = container_type()) : c(ctnr) {}


		/* *************** */
		/*   Destructors   */
		/* *************** */
		
		virtual ~stack() {}


		/* ******************** */
		/*   Member functions   */
		/* ******************** */

		bool empty() const { return this->c.empty(); }
		size_type size() const { return this->c.size(); }
		value_type& top() { return this->c.back(); }
		const value_type& top() const { return this->c.back(); }
		void push (const value_type& val) { this->c.push_back(val); }
		void pop() { this->c.pop_back(); }


		/* ************************ */
		/*   Relational Operators   */
		/* ************************ */

		template <class Tp, class C>
		friend bool operator==(const stack<Tp, C>& x, const stack<Tp, C>& y)
		{ return x.c == y.c; }

		template <class Tp, class C>
		friend bool operator<(const stack<Tp, C>& x, const stack<Tp, C>& y)
		{ return x.c < y.c; }

		template <class Tp, class C>
		friend bool operator!=(const stack<Tp, C>& x, const stack<Tp, C>& y)
		{ return !(x == y); }

		template <class Tp, class C>
		friend bool operator>(const stack<Tp, C>& x, const stack<Tp, C>& y)
		{ return y < x; }

		template <class Tp, class C>
		friend bool operator>=(const stack<Tp, C>& x, const stack<Tp, C>& y)
		{ return !(x < y); }

		template <class Tp, class C>
		friend bool operator<=(const stack<Tp, C>& x, const stack<Tp, C>& y)
		{ return !(y < x); }
	
	};

}

#endif