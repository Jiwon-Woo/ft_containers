#ifndef STACKTESTS_HPP
# define STACKTESTS_HPP

# include "modifiers.stack.hpp"
# include "observers.stack.hpp"
# include "operators.stack.hpp"
# include "alotof.stack.hpp"

void    title(std::string name);

template<class T, class C>
class	testAccess : public ft::stack<T, C>
{
	public:
		testAccess() {
			std::cout << "container size is " << this->c.size() << std::endl;
		}
};

template<class T, class C>
void    stackTests(ft::stack<T,C>& stack)
{
	title("Stack");

	testAccess<T,C> test;

	ft_observers(stack);
	
				/* MODIFIERS = */
	ft_push(stack);
	ft_pop(stack);
	for (int i = 0; i < 5; i++)
		stack.push(i);

	ft_operators(stack);
	ft_alotof(stack);
}

#endif
