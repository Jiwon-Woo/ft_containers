#ifndef TREE_HPP
# define TREE_HPP

#include <functional>
#include <memory.h>
#include "utils.hpp"

#define NONE 0
#define LEFT 1
#define RIGHT 2

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
		node_pointer  	_super_root;	// 가상 루트
		allocator_type	_alloc;
		size_type     	_size;
		value_compare 	_value_comp;

	public:

		tree(const value_compare& comp = value_compare(), const allocator_type& alloc = allocator_type())
			: _root(NULL), _begin_node(NULL), _end_node(NULL), _alloc(alloc), _size(0), _value_comp(comp)
		{
			_super_root = alloc.allocate(1);
			alloc.construct(_super_root, value_type());
			_super_root->parent = NULL;
			_super_root->left = NULL;
			_super_root->right = NULL;
		}

		iterator begin() {
			if(_size == 0)
				return iterator(_super_root);
			return iterator(_begin_node);
		}

		const_iterator begin() const {
			if(_size == 0)
				return const_iterator(_super_root);
			return const_iterator(_begin_node);
		}
		
		iterator end() {return iterator(_super_root);}
		const_iterator end() const {return const_iterator(_super_root);}

		size_type& size() {return _size;}
		const size_type& size() const {return _size;}
		size_type max_size() const {
			return std::min<size_type>(
				std::numeric_limits<size_type>::max() / sizeof(value_type),
				static_cast<size_type>(numeric_limits<difference_type>::max())
			);
		}
		bool empty() const { return _size == 0; }
		value_compare& value_comp() {return _value_comp;}
		const value_compare& value_comp() const {return _value_comp;}
		

		void destroy(node_pointer ptr)
		{
			if (ptr)
			{
				destroy(ptr->left);
				destroy(ptr->right);
				_alloc.destroy(ptr);
				_alloc.deallocate(ptr, 1);
			}
		}

		void clear()
		{
			destroy(_root);
		}

		void set_root(const value_type& val)
		{
			_root = _alloc.allocate(1);
			_alloc.construct(_root, node_type(val));
			_super_root->left = _root;
			_super_root->right = _root;
			_root->parent = _super_root;
			_size++;
		}

		ft::pair<node_pointer, int> find_insert_position(node_pointer start, const value_type& val)
		{
			node_pointer current = start;
			node_pointer parent = start->parent;
			int child_flag;

			while (current)
			{
				if (val.first == (current->value).first) {
					return ft::pair<node_pointer,int>(current, NONE);
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

			if (child_flag == LEFT)
				return ft::pair<node_pointer,int>(parent, LEFT);
			return ft::pair<node_pointer,int>(parent, RIGHT);
		}

		// tree 삽입 삭제 함수
		ft::pair<iterator, bool> insert(const value_type& val)
		{
			if (_size == 0) {
				set_root(val);
				_begin_node = _end_node = _root;
				return ft::pair<iterator,bool>(iterator(_root), true);
			}

			ft::pair<node_pointer, int> pos = find_insert_position(_root, val);
			if (pos.second == NONE)
				return ft::pair<iterator,bool>(iterator(pos.first), false);

			node_pointer new_node = allocate_node(val);
			new_node->set_node(pos.second, NULL, NULL);
			if (pos.first == LEFT) {
				(pos.second)->set_left(new_node);
			} else {
				(pos.second)->set_right(new_node);
			}
			_size++;
			return ft::pair<iterator,bool>(iterator(new_node), true);
		}

		ft::pair<iterator, bool> insert(iterator position, const value_type& val)
		{
			if (_size == 0) {
				set_root(val);
				_begin_node = _end_node = _root;
				return ft::pair<iterator,bool>(iterator(_root), true);
			}
			if ((*position).first == val.fisrt)
				return ft::pair<iterator,bool>(position, false);
			return insert(val);
		}

		size_type get_child_number(node_pointer ptr)
		{
			size_type child = 0;

			if (ptr->left)
				child++;
			if (ptr->right)
				child++;
			return child;
		}

		size_type get_node_direction(node_pointer ptr)
		{
			if (!ptr)
				return NONE;
			if (ptr == ptr->parent->left)
				return LEFT;
			if (ptr == ptr->parent->right)
				return RIGHT;
			return NONE;
		}

		void delete_leaf_node(node_pointer ptr)
		{
			node_pointer parent = ptr->parent;
			size_type direction = get_node_direction(ptr);

			_alloc.destroy(ptr);
			_alloc.deallocate(ptr, 1);
			if (direction == LEFT)
				parent->left = NULL;
			if (direction == RIGHT)
				parent->right = NULL;
		}

		void delete_node_with_child(node_pointer ptr)
		{
			node_pointer parent = ptr->parent;
			size_type direction = get_node_direction(ptr);
			node_pointer child = current->left;
			
			if (!current->left)
				child = current->right;
			
			_alloc.destroy(ptr);
			_alloc.deallocate(ptr, 1);
			if (direction == LEFT)
				parent->left = child;
			if (direction == RIGHT)
				parent->right = child;
		}

		void delete_node_with_children(node_pointer ptr)
		{
			node_pointer prev_ptr = tree_prev_iter(ptr);

			ptr->set_value(prev_ptr->value);
			delete_leaf_node(prev_ptr);
		}

		bool erase(iterator p)
		{
			if (p == end())
				return false;
			
			node_pointer current = p.get_np();
			size_type child_num = get_child_number(current);

			if (child_num == 0) {
				delete_leaf_node(current);
			} else if (child_num == 1) {
				delete_node_with_child(current);
			} else {
				delete_node_with_children(current);
			}
			--_size;
			return true;
		}

		template <class Key>
		bool erase (const Key& k)
		{
			return erase(find(k));
		}


		template <class Key>
		iterator find(const Key& k)
		{
			if (_size == 0) {
				return end();
			}
			node_pointer current = _root;
			while (current)
			{
				if (k == (current->value).first)
					return iterator(current);
				if (k < (current->value).first) {
					current = current->left;
				} else {
					current = current->right;
				}
			}
			return end();
		}

		template <class Key>
		const_iterator find(const Key& k) const
		{
			if (_size == 0) {
				return end();
			}
			node_pointer current = _root;
			while (current)
			{
				if (k == (current->value).first)
					return const_iterator(current);
				if (k < (current->value).first) {
					current = current->left;
				} else {
					current = current->right;
				}
			}
			return end();
		}

		template <class Key>
		size_type count (const Key& k) const
		{
			return !(find(k) == end());
		}

	};

}


#endif