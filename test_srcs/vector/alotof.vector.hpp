#ifndef ALOTOF_VECTOR_HPP
# define ALOTOF_VECTOR_HPP

# include "print.vector.hpp"

template<class T>
void	ft_alotof(ft::vector<T>& vect)
{
	heading("a lot of vector!");
	try {
		for (int i=0; i<1000; i++)
			vect.push_back(i);
		std::cout << " ** end **" << std::endl;
	} catch(const std::exception& e) {}
}

#endif
