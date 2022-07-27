#ifndef MAPTESTS_HPP
# define MAPTESTS_HPP

# include "iterators.map.hpp"
# include "modifiers.map.hpp"
# include "operators.map.hpp"
# include "observers.map.hpp"
# include "alotof.map.hpp"

void    title(std::string name);

template<class Key, class Value>
void    mapTests(ft::map<Key, Value>& map)
{
	title("MAP");

	for (int i = 0; i < 6; ++i) {
		typename ft::map<Key, Value>::value_type val(i, i);
		map.insert(val);
	}

	ft_iterators(map);
	ft_modifiers(map);
	ft_operators(map);
	ft_observers(map);

				/* COPY CONSTRUCTOR */
	heading("copy constructor");
	ft::map<Key, Value> copy(map);
	print(copy, 0); // 0#
	copy.clear();
	print(map, 1); // 1#
	
	typename ft::pair<Key, Value> val = ft::make_pair(1000, 10);
	map.insert(val);
	
				/* OPERATOR = */
	heading("operator =");
	copy = map;
	print(copy, 0); // 0#
	copy.clear();
	print(map, 1); // 1#

				/* ALOTOF */
	ft_alotof(map);
	std::cout << std::endl;
}

#endif
