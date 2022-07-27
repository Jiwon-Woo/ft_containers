#ifndef PRINT_VECTOR_HPP
# define PRINT_VECTOR_HPP

# include "../containers.hpp"

template<class T>
void	print(const ft::vector<T>& vect, int n)
{
	std::cout << n << "#  size: " << vect.size() << std::endl << "    ";
	for (typename ft::vector<T>::const_iterator it = vect.begin() ; it != vect.end(); ++it)
		std::cout  << *it << " ";
	if (vect.empty() == 1)
		std::cout << "empty vector";
	std::cout << std::endl;	
}

#endif
