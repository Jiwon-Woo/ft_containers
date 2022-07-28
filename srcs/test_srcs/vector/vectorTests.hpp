#ifndef VECTORTESTS_HPP
# define VECTORTESTS_HPP

# include "iterators.vector.hpp"
# include "modifiers.vector.hpp"
# include "operators.vector.hpp"
# include "observers.vector.hpp"
# include "elementAccess.vector.hpp"
# include "alotof.vector.hpp"

void    title(std::string name);

template <class T>
void    vectorTests(ft::vector<T>& vect)
{
	title("VECTOR");
	
	ft_observers(vect);
	ft_modifiers(vect);
	ft_iterators(vect);
	ft_elementAccess(vect);
	ft_operators(vect);
	
			/* COPY CONSTRUCTOR */
	heading("copy constructor");
	ft::vector<T> copy(vect);
	print(copy, 0); // 0#
	copy.clear();
	print(vect, 1); // 1#
	
	vect.insert(vect.end(), 42);
	
			/* OPERATOR = */
	heading("operator =");
	copy = vect;
	print(copy, 0); // 0#
	copy.clear();
	print(vect, 1); // 1#

	ft_alotof(vect);

	std::cout << std::endl;

}

#endif
