#ifndef TREE_HPP
# define TREE_HPP

#include <functional>
#include <memory.h>
#include "utils.hpp"

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
		allocator_type	_alloc;
		size_type     	_size;
		value_compare 	_value_comp;
		// __compressed_pair<__end_node_t, __node_allocator>  __pair1_;
		// __compressed_pair<size_type, value_compare>        __pair3_;

	public:

		tree(const value_compare& comp = value_compare(), const allocator_type& alloc = allocator_type())
			: _begin_node(nullptr), _end_node(nullptr), _alloc(a), _size(0), _value_comp(comp)
		{
			_root = alloc.allocate(1);
			alloc.construct(_root, value_type());
			_end_node = alloc.allocate(1);

			_end_node->parent = _root;
			_end_node->left = _root;
			_root->parent = nullptr;
			_root->right = _end_node;
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


		// tree 삽입 삭제 함수
		ft::pair<iterator,bool> insert(const value_type& val)
		{
			node_pointer parent = NULL;
			node_pointer current = _root;
			while (current && val.first != (current->value).first)
			{
				if (_value_comp(val, current->value)) {
					parent = current;
					current = current->left;
				} else {
					parent = current;
					current = current->right;
				}
			}

			if (current) {
				_alloc.destroy(current);
			} else {
				current = _alloc.allocate(1);
				_size++;
			}
			_alloc.construct(current, node_type(val));
			current->set_parent(parent);
			current->set_right(nullptr);
			current->set_left(nullptr);
			return ft::pair(iterator(current), true);
		}

		iterator insert(iterator position, const value_type& val)
		{
			if (position->get_np()) {
				_alloc.destroy(position->get_np());
			} else {
				position->get_np() = _alloc.allocate(1);
				_size++;
			}
			_alloc.construct(position->get_np(), node_type(val));
			return position;
		}

		iterator erase(const_iterator p);
		iterator erase(const_iterator first, const_iterator last);
		template <class Key>
		iterator erase (const Key& k);

		template <class _Key>
		iterator find(const _Key& __v);
		template <class _Key>
		const_iterator find(const _Key& __v) const;

	};

}


#endif