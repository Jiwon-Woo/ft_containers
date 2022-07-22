#ifndef TREE_HPP
# define TREE_HPP

#include <functional>
#include <memory.h>
#include "utils.hpp"

#define LEFT 0
#define RIGHT 1

namespace ft
{

	/* ******** */
	/*   Node   */
	/* ******** */

	template <typename T>
	struct tree_node
	{
		typedef T        	node_value_type;
		typedef T*       	node_value_type_pointer;
		typedef tree_node	node;
		typedef node*    	node_pointer;

		node_value_type	value;
		node_pointer   	parent;
		node_pointer   	right;
		node_pointer   	left;

		tree_node(const node_value_type& v) : value(v), parent(nullptr), right(nullptr), left(nullptr) {}
		tree_node(const tree_node& tn) : value(tn.value), parent(tn.parent), right(tn.right), left(tn.left) {}
		~tree_node() {}

		tree_node& operator=(const tree_node& tn) {
			if (this != &tn){
				this->value = tn.value;
				this->parent = tn.parent;
				this->right = tn.right;
				this->left = tn.left;
			}
			return *this;
		}

		void set_parent(node_pointer p) { parent = p; }
		void set_left(node_pointer p) { left = p; }
		void set_right(node_pointer p) { right = p; }
		void set_value(const node_value_type& v) { value = v; }
		void set_node(node_pointer parent, node_pointer left, node_pointer right)
		{
			this->set_parent(parent);
			this->set_left(left);
			this->set_right(right);
		}
	};



	/* ******** */
	/*   Tree   */
	/* ******** */

	template <typename T, typename Compare,
			typename Node = ft::tree_node<T>,
			typename Alloc = std::allocator<Node> >
	class tree
	{

	public:
		typedef T                                                      	value_type;
		typedef Compare                                                	value_compare;
		typedef Node                                                   	node_type;
		typedef typename Alloc::template rebind<node_type>::other      	allocator_type;
		typedef typename allocator_type::pointer                       	pointer;
		typedef typename allocator_type::const_pointer                 	const_pointer;
		typedef std::size_t                                            	size_type;
		typedef std::ptrdiff_t                                         	difference_type;

		typedef typename node_type::node_pointer                       	node_pointer;
		typedef	typename ft::tree_iterator<value_type, node_type>      	iterator;
		typedef typename ft::tree_iterator<const value_type, node_type>	const_iterator;

	private:
		node_pointer  	_root;
		node_pointer  	_begin_node;
		node_pointer  	_end_node;
		node_pointer  	_virtual_root;
		allocator_type	_alloc;
		size_type     	_size;
		value_compare 	_value_comp;

	public:

		tree(const value_compare& comp = value_compare(), const allocator_type& alloc = allocator_type())
			: _root(NULL), _alloc(alloc), _size(0), _value_comp(comp)
		{
			_end_node = alloc.allocate(1);
			alloc.construct(_end_node, value_type());
			_begin_node = _end_node;
			_end_node->parent = _root;
			_end_node->left = _root;
			_end_node->right = NULL;
		}

		iterator begin()  {return iterator(_begin_node);}
		const_iterator begin() const {return const_iterator(_begin_node);}
		iterator end() {return iterator(_end_node);}
		const_iterator end() const {return const_iterator(_end_node);}

		size_type& size() {return _size;}
		const size_type& size() const {return _size;}
		value_compare& value_comp() {return _value_comp;}
		const value_compare& value_comp() const {return _value_comp;}
		void clear();

		node_pointer allocate_node(const value_type& val)
		{
			node_pointer ptr = _alloc.allocate(1);
			_alloc.construct(ptr, node_type(val));
			return ptr;
		}

		node_pointer allocate_node(const node_type& node)
		{
			node_pointer ptr = _alloc.allocate(1);
			_alloc.construct(ptr, node_type(node));
			return ptr;
		}

		void set_node(node_pointer node, node_pointer parent, node_pointer left, node_pointer right)
		{
			node->set_parent(parent);
			node->set_left(left);
			node->set_right(right);
		}

		// tree 삽입 삭제 함수
		ft::pair<iterator,bool> insert(const value_type& val)
		{
			node_pointer parent = NULL;
			node_pointer current = _root;
			bool child_flag;

			while (current)
			{
				if (val.first == (current->value).first) {
					return ft::pair<iterator,bool>(iterator(current), false);
				}
				parent = current;
				if (_value_comp(val, current->value)) {
					current = current->left;
					child_flag = LEFT;
				} else {
					current = current->right;
					child_flag = RIGHT;
				}
			}

			node_pointer new_node = allocate_node(val);
			new_node->set_node(parent, NULL, NULL);
			if (parent) {
				if (child_flag == LEFT) {
					parent->set_left(new_node);
				} else {
					parent->set_right(new_node);
				}
			}
			current = new_node;
			_size++;
			return ft::pair<iterator,bool>(iterator(current), true);
		}

		iterator insert(iterator position, const value_type& val)
		{
			node_pointer parent = NULL;
			node_pointer current = _root;
			bool child_flag;

			(void)position;
			while (current && val.first != (current->value).first)
			{
				parent = current;
				if (_value_comp(val, current->value)) {
					current = current->left;
					child_flag = LEFT;
				} else {
					current = current->right;
					child_flag = RIGHT;
				}
			}

			if (current) {
				return iterator(current);
			} else {
				node_pointer new_node = allocate_node(val);
				new_node->set_node(parent, NULL, NULL);
				if (parent) {
					if (child_flag == LEFT) {
						parent->set_left(new_node);
					} else {
						parent->set_right(new_node);
					}
				}
				current = new_node;
				_size++;
				return iterator(current);
			}
		}

		iterator erase(const_iterator p);

		template <class Key>
		iterator erase (const Key& k)
		{
			iterator it = find(k);

			if (*it)

		}

		template <class Key>
		iterator find(const Key& k)
		{
			node_pointer current = _root;

			while (current && k != (current->value).first)
			{
				if (k < (current->value).first) {
					current = current->left;
				} else {
					current = current->right;
				}
			}

			if (!current || current->left == _root) {
				return iterator(_end_node);
			} else {
				return iterator(current);
			}
		}

		template <class Key>
		const_iterator find(const Key& k) const
		{
			node_pointer current = _root;

			while (current && k != (current->value).first)
			{
				if (k < (current->value).first) {
					current = current->left;
				} else {
					current = current->right;
				}
			}

			if (!current || current->left == _root) {
				return const_iterator(_end_node);
			} else {
				return const_iterator(current);
			}
		}

	};

}


#endif