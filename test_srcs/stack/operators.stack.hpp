#ifndef OPERATORS_STACK_HPP
# define OPERATORS_STACK_HPP

# include "print.stack.hpp"

template<class T, class C>
void	ft_operators(const ft::stack<T, C>& stack)
{
	heading("operators");
	
	ft::stack<T, C> other;
	std::cout << "0#  == " << (stack == other) << std::endl;
	std::cout << "1#  != " << (stack != other) << std::endl;
	std::cout << "2#  <  " << (stack < other) << std::endl;
	std::cout << "3#  <= " << (stack <= other) << std::endl;
	std::cout << "4#  >  " << (stack > other) << std::endl;
	std::cout << "5#  >= " << (stack >= other) << std::endl;
}

#endif
