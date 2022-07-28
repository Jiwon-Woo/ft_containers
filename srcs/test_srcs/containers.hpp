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
    # include "../../includes/iterator.hpp"
    # include "../../includes/map.hpp"
    # include "../../includes/stack.hpp"
    # include "../../includes/tree.hpp"
    # include "../../includes/utils.hpp"
    # include "../../includes/vector.hpp"
#endif

void heading(std::string name);

#endif
