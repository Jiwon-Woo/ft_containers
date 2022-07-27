#ifndef PRINT_STACK_HPP
# define PRINT_STACK_HPP

# include "../containers.hpp"

template<class T, class Container>
void	print(const ft::stack<T,Container>& stack, int n)
{
	std::cout << n << "#  size: " << stack.size();
	if (stack.empty() == 1)
		std::cout << std::endl << "    empty stack";
	std::cout << std::endl;	
}

#endif
