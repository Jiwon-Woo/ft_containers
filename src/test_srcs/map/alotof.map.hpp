#ifndef ALOTOF_MAP_HPP
# define ALOTOF_MAP_HPP

# include "print.map.hpp"

template<class Key, class Value>
void	ft_alotof(ft::map<Key, Value>& map)
{
	heading("a lot of stack!");
	for (int i=0; i<1000; i++)
		map.insert(ft::make_pair(i, i));
}

#endif
