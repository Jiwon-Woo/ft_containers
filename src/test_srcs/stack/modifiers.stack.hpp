#ifndef MODIFIERS_STACK_HPP
# define MODIFIERS_STACK_HPP

# include "print.stack.hpp"

template<class T, class C>
void	ft_push(ft::stack<T,C>& stack)
{
	heading("push");
	print(stack, 0); // #0
	for (int i = 0; i < 5; i++)
	{
		stack.push(i);
		print(stack, i + 1); // i+1#
	}
}

template<class T, class C>
void	ft_pop(ft::stack<T,C>& stack)
{
	heading("pop");
	print(stack, 0); // #0
	for (int i = 0; i < 5; i++)
	{
		stack.pop();
		print(stack, i + 1); // i+1#
	}
}

#endif
