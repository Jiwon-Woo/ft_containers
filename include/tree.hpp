#ifndef TREE_HPP
# define TREE_HPP

#include <functional>
#include <memory.h>
#include "iterator.hpp"

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

		tree_node() : parent(nullptr), right(nullptr), left(nullptr) {}
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
		// node_pointer  	_begin_node;
		// node_pointer  	_end_node;
		node_pointer  	_super_root;	// 가상 루트
		allocator_type	_alloc;
		size_type     	_size;
		value_compare 	_value_comp;


	public:
	
		/* ************* */
		/*   Construct   */
		/* ************* */
		
		tree(const value_compare& comp, const allocator_type& alloc = allocator_type())
			: _root(NULL), _alloc(alloc), _size(0), _value_comp(comp)
		{
			_super_root = _alloc.allocate(1);
			_alloc.construct(_super_root, node_type());
			_super_root->parent = NULL;
			_super_root->left = NULL;
			_super_root->right = NULL;
		}

		tree(const tree& t, const allocator_type& alloc = allocator_type())
			: _alloc(alloc), _size(t.size()), _value_comp(t.value_comp())
		{
			_super_root = _alloc.allocate(1);
			_alloc.construct(_super_root, node_type());
			_root = copy_tree(t._root, _super_root);
			_super_root->left = _root;
			_super_root->right = _root;
			if (_root) {
				_root->parent = _super_root;
			}
		}



		/* ************** */
		/*   Destructor   */
		/* ************** */

		~tree() {
			clear();
			_alloc.destroy(_super_root);
			_alloc.deallocate(_super_root, 1);
			_super_root = NULL;
		}



		/* ************** */
		/*   Assignment   */
		/* ************** */

		tree& operator=(const tree& t) {
			if (this != &t){
				clear();
				_root = copy_tree(t.get_root(), _super_root);
				_super_root->left = _root;
				_super_root->right = _root;
				if (_root) {
					_root->parent = _super_root;
				}
				_size = t.size();
			}
			return *this;
		}


		node_pointer get_min_node() const
		{
			node_pointer current = _root;

			while (current->left) {
				current = current->left;
			}
			return current;
		}

		/* ************* */
		/*   Iterators   */
		/* ************* */

		iterator begin() {
			if(_size == 0)
				return iterator(_super_root);
			return iterator(get_min_node());
		}

		const_iterator begin() const {
			if(_size == 0)
				return const_iterator(_super_root);
			return const_iterator(get_min_node());
		}
		
		iterator end() {return iterator(_super_root);}
		const_iterator end() const {return const_iterator(_super_root);}



		/* ************ */
		/*   Capacity   */
		/* ************ */

		bool empty() const { return _size == 0; }

		size_type size() const {return _size;}

		size_type max_size() const {
			return std::min<size_type>(
				std::numeric_limits<size_type>::max() / sizeof(value_type),
				static_cast<size_type>(std::numeric_limits<difference_type>::max())
			);
		}



		/* ************* */
		/*   Modifiers   */
		/* ************* */

		ft::pair<iterator, bool> insert(const value_type& val)
		{
			if (_size == 0) {
				set_root(val);
				return ft::pair<iterator,bool>(iterator(_root), true);
			}

			ft::pair<node_pointer, int> pos = find_insert_position(_root, val);
			if (pos.second == NONE)
				return ft::pair<iterator,bool>(iterator(pos.first), false);

			node_pointer new_node = _alloc.allocate(1);
			_alloc.construct(new_node, node_type(val));
			new_node->set_parent(pos.first);
			new_node->set_left(NULL);
			new_node->set_right(NULL);
			if (pos.second == LEFT) {
				(pos.first)->set_left(new_node);
			} else {
				(pos.first)->set_right(new_node);
			}
			_size++;
			return ft::pair<iterator,bool>(iterator(new_node), true);
		}

		ft::pair<iterator, bool> insert(iterator position, const value_type& val)
		{
			if (_size == 0) {
				set_root(val);
				return ft::pair<iterator,bool>(iterator(_root), true);
			}
			if (!_value_comp(*position, val) && !_value_comp(val, *position))
				return ft::pair<iterator,bool>(position, false);
			return insert(val);
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

		bool erase (const value_type& k) { return erase(find(k)); }

		void clear() {
			if (_root)
				destroy(_root);
			_root = NULL;
			_size = 0;
		}



		/* ************* */
		/*   Observers   */
		/* ************* */

		value_compare& value_comp() { return _value_comp; }
		const value_compare& value_comp() const { return _value_comp; }



		/* ************** */
		/*   Operations   */
		/* ************** */

		iterator find(const value_type& v)
		{
			if (_size == 0) {
				return end();
			}
			node_pointer current = _root;
			while (current)
			{
				if (_value_comp(v, current->value)) {
					current = current->left;
				} else if (!_value_comp(current->value, v)) {
					return iterator(current);
				} else {
					current = current->right;
				}
			}
			return end();
		}

		const_iterator find(const value_type& v) const
		{
			if (_size == 0) {
				return end();
			}
			node_pointer current = _root;
			while (current)
			{
				if (_value_comp(v, current->value)) {
					current = current->left;
				} else if (!_value_comp(current->value, v)) {
					return iterator(current);
				} else {
					current = current->right;
				}
			}
			return end();
		}

		size_type count (const value_type& v) const { return !(find(v) == end()); }

		iterator lower_bound(const value_type& v)
		{
			node_pointer current = _root;
			node_pointer result = _super_root;

			while (current != nullptr)
			{
				if (!_value_comp(current->value, v))
				{
					result = current;
					current = current->left;
				}
				else
					current = current->right;
			}
			return iterator(result);
		}

		const_iterator lower_bound(const value_type& v) const
		{
			node_pointer current = _root;
			node_pointer result = _super_root;

			while (current != nullptr)
			{
				if (!_value_comp(current->value, v))
				{
					result = current;
					current = current->left;
				}
				else
					current = current->right;
			}
			return const_iterator(result);
		}

		iterator upper_bound(const value_type& v)
		{
			node_pointer current = _root;
			node_pointer result = _super_root;

			while (current != nullptr)
			{
				if (_value_comp(v, current->value))
				{
					result = current;
					current = current->left;
				}
				else
					current = current->right;
			}
			return iterator(result);
		}

		const_iterator upper_bound(const value_type& v) const
		{
			node_pointer current = _root;
			node_pointer result = _super_root;

			while (current != nullptr)
			{
				if (_value_comp(v, current->value))
				{
					result = current;
					current = current->left;
				}
				else
					current = current->right;
			}
			return const_iterator(result);
		}

		ft::pair<iterator, iterator> equal_range (const value_type& v) {
			return ft::pair<iterator, iterator>(lower_bound(v), upper_bound(v));
		}

		ft::pair<const_iterator, const_iterator> equal_range (const value_type& v) const {
			return ft::pair<const_iterator, const_iterator>(lower_bound(v), upper_bound(v));
		}



		/* *********** */
		/*   Getters   */
		/* *********** */

		node_pointer get_root() const { return _root; }


	private:

		void set_root(const value_type& val)
		{
			_root = _alloc.allocate(1);
			_alloc.construct(_root, node_type(val));
			_super_root->left = _root;
			_super_root->right = _root;
			_root->parent = _super_root;
			_size++;
		}

		node_pointer copy_node(const node_type& src)
		{
			node_pointer ptr = _alloc.allocate(1);

			_alloc.construct(ptr, node_type(src.value));
			return ptr;
		}

		node_pointer copy_tree(node_pointer src, node_pointer parent)
		{
			node_pointer ptr = NULL;
			if (src)
			{
				ptr = copy_node(*(src));
				ptr->parent = parent;
				ptr->left = copy_tree(src->left, ptr);
				ptr->right = copy_tree(src->right, ptr);
			}
			return ptr;
		}

		ft::pair<node_pointer, int> find_insert_position(node_pointer start, const value_type& val)
		{
			node_pointer current = start;
			node_pointer parent = start->parent;
			int child_flag;

			while (current)
			{
				parent = current;
				if (_value_comp(val, current->value)) {
					current = current->left;
					child_flag = LEFT;
				} else if (!_value_comp(current->value, val)) {
					return ft::pair<node_pointer,int>(current, NONE);
				} else {
					current = current->right;
					child_flag = RIGHT;
				}
			}

			if (child_flag == LEFT)
				return ft::pair<node_pointer,int>(parent, LEFT);
			return ft::pair<node_pointer,int>(parent, RIGHT);
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

			if (direction == LEFT) {
				parent->left = NULL;
			}
			if (direction == RIGHT) {
				parent->right = NULL;
			}
			_alloc.destroy(ptr);
			_alloc.deallocate(ptr, 1);
		}

		void delete_node_with_child(node_pointer ptr)
		{
			node_pointer parent = ptr->parent;
			size_type direction = get_node_direction(ptr);

			node_pointer child = ptr->left;
			if (!ptr->left)
				child = ptr->right;
			
			if (direction == LEFT) {
				parent->left = child;
			}
			if (direction == RIGHT) {
				parent->right = child;
			}
			_alloc.destroy(ptr);
			_alloc.deallocate(ptr, 1);
		}

		node_pointer prev_iter(node_pointer x)
		{
			node_pointer copy_x = x;
			if (copy_x->left != nullptr) {
				copy_x = copy_x->left;
				while (copy_x->right != nullptr)
					copy_x = copy_x->right;
				return copy_x;
			}
			while (copy_x != copy_x->parent->right)
				copy_x = copy_x->parent;
			return copy_x->parent;
		}

		void delete_node_with_children(node_pointer ptr)
		{
			node_pointer prev_ptr = prev_iter(ptr);

			ptr->set_value(prev_ptr->value);
			delete_leaf_node(prev_ptr);
		}

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

	};

}


#endif