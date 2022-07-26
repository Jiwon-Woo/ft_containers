#ifndef OBSERVERS_STACK_HPP
# define OBSERVERS_STACK_HPP

# include "print.stack.hpp"

template<class T, class C>
void	ft_observers(ft::stack<T, C>& stack)
{
				/* EMPTY */
	heading("empty");
	std::cout << "0#  " << stack.empty() << std::endl; // 0#
	stack.push(1);
	std::cout << "1#  " << stack.empty() << std::endl; // 1#
	stack.pop();
	std::cout << "2#  " << stack.empty() << std::endl; // 2#
    
				/* SIZE */
	heading("size");
	std::cout << "0#  " << stack.size() << std::endl; // 0#
	std::cout << "1#  " << stack.size() << std::endl; // 1#
	stack.push(1);
	std::cout << "2#  " << stack.size() << std::endl; // 2#
    
				/* TOP */
	heading("top");
	std::cout << "1#  " << stack.top() << std::endl; // 1#
	stack.push(2);
	std::cout << "2#  " << stack.top() << std::endl; // 2#
}

#endif
