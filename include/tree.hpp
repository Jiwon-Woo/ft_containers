#ifndef TREE_HPP
# define TREE_HPP

#include <functional>
#include <memory.h>
#include "utils.hpp"

namespace ft
{

template <typename T>
struct tree_node
{
public:
	typedef T        	node_value_type;
	typedef tree_node	node;
	typedef node*		node_pointer;

public:
	node_value_type	value;
	node_pointer   	parent;
	node_pointer   	right;
	node_pointer   	left;
};

template <typename T, typename Compare,
		typename Node = ft::tree_node<T>,
		typename Alloc = std::allocator<Node> >
class tree
{

public:
	typedef T                                                	value_type;
	typedef Compare                                          	value_compare;
	typedef ft::tree_node<T>                                 	node_type;
	typedef typename Alloc::template rebind<node_type>::other	allocator_type;
	typedef typename allocator_type::pointer                 	pointer;
    typedef typename allocator_type::const_pointer           	const_pointer;
    typedef std::size_t                                      	size_type;
	typedef std::ptrdiff_t                                   	difference_type;
	typedef typename node_type::node_pointer                 	node_pointer;

public:
    typedef	typename ft::tree_iterator<value_type, node_type>      	iterator;
    typedef typename ft::tree_iterator<const value_type, node_type>	const_iterator;

private:
	node_pointer	root;
    // iter_pointer	begin_node;
    // __compressed_pair<__end_node_t, __node_allocator>  __pair1_;
    // __compressed_pair<size_type, value_compare>        __pair3_;

};

}


#endif