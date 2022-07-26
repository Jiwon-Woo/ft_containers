#ifndef CONTAINERS_HPP
# define CONTAINERS_HPP

# include <iostream>
# include <string.h>

#if 1
    # define NAMESPACE "STD"
    # include <stack>
    # include <vector>
    # include <map>
    namespace ft = std;
#else
    # define NAMESPACE "FT"
    # include "../include/iterator.hpp"
    # include "../include/map.hpp"
    # include "../include/stack.hpp"
    # include "../include/tree.hpp"
    # include "../include/utils.hpp"
    # include "../include/vector.hpp"
#endif

void heading(std::string name);

#endif
