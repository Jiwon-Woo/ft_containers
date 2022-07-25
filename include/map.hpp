#ifndef MAP_HPP
# define MAP_HPP

#include <functional>
#include <memory.h>
#include "tree.hpp"

namespace ft
{
	template < typename Key, typename T,
		typename Compare = std::less<Key>,
		typename Alloc = std::allocator<ft::pair<const Key, T> > >
	class map
	{
	public:
		typedef Key                                                         	key_type;
		typedef T                                                           	mapped_type;
		typedef ft::pair<const key_type, mapped_type>                       	value_type;
		typedef Compare                                                     	key_compare;
		typedef Alloc                                                       	allocator_type;
		typedef std::ptrdiff_t                                              	difference_type;
		typedef std::size_t                                                 	size_type;
		typedef typename allocator_type::reference                          	reference;
		typedef typename allocator_type::const_reference                    	const_reference;
		typedef typename allocator_type::pointer                            	pointer;
		typedef typename allocator_type::const_pointer                      	const_pointer;

		class value_compare : public std::binary_function<value_type, value_type, bool>
		{
			friend class map; // map 클래스는 value_compare private 변수에 접근 가능
		
		protected:
			/* member variable */
			key_compare comp;
			
			/* Constructor */
			value_compare(key_compare c) : comp(c) {}
			
		public:
			bool operator()(const value_type& x, const value_type& y) const
			{ return comp(x.first, y.first); } // value_type 형태(pair)의 compare -> 마찬가지로 key로 비교함
		};
		
		typedef typename ft::tree<value_type, value_compare, allocator_type>	tree_type;
		typedef ft::map_iterator<typename tree_type::iterator>              	iterator;
		typedef ft::map_iterator<typename tree_type::const_iterator>        	const_iterator;
		typedef typename ft::reverse_iterator<iterator>                     	reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator>               	const_reverse_iterator;

	private:
		tree_type _tree;
	
	public:
		// Constructor:
		explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
			: _tree(tree_type()) {}
		
		template <class InputIterator>
		map (InputIterator first, InputIterator last,
			const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type()) : _tree(tree_type())
		{
			InputIterator it;

			for (it = first; it != last; it++) {
				_tree.insert(*it);
			}
		}
		
		map (const map& x) : _tree(x._tree) {}

		// Destructor:
		~map() {}

		// Assignment:
		map& operator=(const map& m) { _tree = m._tree; }

		// iterators:
		iterator begin() { return iterator(_tree.begin()); }
		const_iterator begin() const { return const_iterator(_tree.begin()); }
		iterator end() { return iterator(_tree.end()); }
		const_iterator end() const { return const_iterator(_tree.end()); }

		reverse_iterator rbegin() { return reverse_iterator(this->end()); }
		const_reverse_iterator rbegin() const { return const_reverse_iterator(this->end()); }
		reverse_iterator rend() { return reverse_iterator(this->begin()); }
		const_reverse_iterator rend() const { return const_reverse_iterator(this->begin()); }

		// capacity:
		bool empty() const { return _tree.empty(); }
		size_type size() const { return _tree.size(); }
		size_type max_size() const { return _tree.max_size(); }

		// element access:
		mapped_type& operator[](const key_type& k);

		// modifiers:
		pair<iterator,bool> insert (const value_type& val) { return _tree.insert(val); }
		iterator insert (iterator position, const value_type& val) { return _tree.insert(position.base(), val).first; }
		template <class InputIterator>
		void insert (InputIterator first, InputIterator last)
		{
			InputIterator it;

			for (it = first; it != last; it++) {
				_tree.insert(*it);
			}
		}

		void erase (iterator position) { _tree.erase(position.base()); }
		size_type erase (const key_type& k) { return _tree.erase(k); }
		void erase (iterator first, iterator last)
		{
			iterator it;

			for (it = first; it != last; it++) {
				_tree.erase(*it);
			}
		}

		void clear() { _tree.clear(); }

		// observers:
		// value_compare value_comp() const;
		// key_compare    key_comp()      const;

		// map operations:
		iterator find(const key_type& k) { return iterator(_tree.find(k)); }
		const_iterator find(const key_type& k) const { return const_iterator(_tree.find(k)); }

		size_type count (const key_type& k) const { return _tree.count(k); }

		iterator lower_bound (const key_type& k) { return iterator(_tree.lower_bound(k)); }
		const_iterator lower_bound (const key_type& k) const { return const_iterator(_tree.lower_bound(k)); }

		iterator upper_bound (const key_type& k) { return iterator(_tree.upper_bound(k)); }
		const_iterator upper_bound (const key_type& k) const { return const_iterator(_tree.upper_bound(k)); }

		ft::pair<iterator, iterator> equal_range (const key_type& k) {
			return ft::pair<iterator, iterator>(lower_bound(k), upper_bound(k));
		}

		ft::pair<const_iterator, const_iterator> equal_range (const key_type& k) const {
			return ft::pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k));
		}

	};
}

#endif