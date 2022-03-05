#ifndef STACK_HPP
# define STACK_HPP

namespace ft
{
	class stack
	{
	private:
		/* data */
	public:
		stack();
		stack(stack const &s);
		stack& operator=(stack const &s);
		~stack();
	};
}

#endif