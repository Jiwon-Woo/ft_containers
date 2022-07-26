#ifndef ALOTOF_STACK_HPP
# define ALOTOF_STACK_HPP

# include "print.stack.hpp"

template<class T, class C>
void	ft_alotof(ft::stack<T,C>& stack)
{
	heading("a lot of stack!");
	for (int i=0; i<1000; i++)
		stack.push(i);
}

#endif
