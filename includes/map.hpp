#ifndef MAP_HPP
# define MAP_HPP

#include "tree.hpp"

namespace ft
{
	template < typename Key, typename T,
		typename Compare = std::less<Key>,
		typename Alloc = std::allocator<ft::pair<const Key, T> > >
	class map
	{
	public:
		typedef Key                                     	key_type;
		typedef T                                       	mapped_type;
		typedef ft::pair<const key_type, mapped_type>   	value_type;
		typedef Compare                                 	key_compare;
		typedef Alloc                                   	allocator_type;
		typedef std::ptrdiff_t                          	difference_type;
		typedef std::size_t                             	size_type;
		typedef typename allocator_type::reference      	reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer        	pointer;
		typedef typename allocator_type::const_pointer  	const_pointer;

		class value_compare : public std::binary_function<value_type, value_type, bool>
		{
			friend class map;	// map 클래스는 value_compare private 변수에 접근 가능
		
		protected:
			/* member variable */
			key_compare comp;
			
			/* Constructor */
			value_compare(key_compare c) : comp(c) {}
			
		public:
			bool operator()(const value_type& x, const value_type& y) const
			{ return comp(x.first, y.first); }
		};
		
		typedef typename ft::tree<value_type, value_compare> 	tree_type;
		typedef typename tree_type::iterator                 	iterator;
		typedef typename tree_type::const_iterator           	const_iterator;
		typedef typename ft::reverse_iterator<iterator>      	reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator>	const_reverse_iterator;


	private:
		tree_type _tree;


	public:
		/* **************** */
		/*   Constructors   */
		/* **************** */

		explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
			: _tree(value_compare(comp), alloc) {}
		
		template <class InputIterator>
		map (InputIterator first, InputIterator last,
			const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type())
				: _tree(value_compare(comp), alloc)
		{
			InputIterator it;

			for (it = first; it != last; it++) {
				_tree.insert(*it);
			}
		}
		
		map (const map& x) : _tree(x._tree) {}


		/* *************** */
		/*   Destructors   */
		/* *************** */

		~map() {}


		/* ************** */
		/*   Assignment   */
		/* ************** */

		map& operator=(const map& m) {
			if (this != &m) {
				_tree = m._tree;
			}
			return *this;
		}
		
		
		/* ************* */
		/*   Iterators   */
		/* ************* */

		iterator begin() { return iterator(_tree.begin()); }
		const_iterator begin() const { return const_iterator(_tree.begin()); }
		iterator end() { return iterator(_tree.end()); }
		const_iterator end() const { return const_iterator(_tree.end()); }

		reverse_iterator rbegin() { return reverse_iterator(this->end()); }
		const_reverse_iterator rbegin() const { return const_reverse_iterator(this->end()); }
		reverse_iterator rend() { return reverse_iterator(this->begin()); }
		const_reverse_iterator rend() const { return const_reverse_iterator(this->begin()); }


		/* ************ */
		/*   Capacity   */
		/* ************ */

		bool empty() const { return _tree.empty(); }
		size_type size() const { return _tree.size(); }
		size_type max_size() const { return _tree.max_size(); }


		/* ****************** */
		/*   Element access   */
		/* ****************** */

		mapped_type& operator[](const key_type& k)
		{
			return (*((this->insert(ft::make_pair(k,mapped_type()))).first)).second;
		}


		/* ************* */
		/*   Modifiers   */
		/* ************* */

		pair<iterator,bool> insert (const value_type& val) { return _tree.insert(val); }
		iterator insert (iterator position, const value_type& val) { return _tree.insert(position, val).first; }
		template <class InputIterator>
		void insert (InputIterator first, InputIterator last)
		{
			for (InputIterator it = first; it != last; it++) {
				_tree.insert(*it);
			}
		}

		void erase (iterator position) { _tree.erase(position); }
		size_type erase (const key_type& k) { return _tree.erase(ft::make_pair(k, mapped_type())); }
		void erase (iterator first, iterator last) { _tree.erase(first, last); }

		void swap (map& x) { _tree.swap(x._tree); }

		void clear() { _tree.clear(); }


		/* ************* */
		/*   Observers   */
		/* ************* */

		key_compare key_comp() const { return key_compare(); }
		value_compare value_comp() const { return _tree.value_comp(); }


		/* ************** */
		/*   Operations   */
		/* ************** */

		iterator find(const key_type& k) { return _tree.find(ft::make_pair(k, mapped_type())); }
		const_iterator find(const key_type& k) const { return _tree.find(ft::make_pair(k, mapped_type())); }

		size_type count (const key_type& k) const { return _tree.count(ft::make_pair(k, mapped_type())); }

		iterator lower_bound (const key_type& k) { return _tree.lower_bound(ft::make_pair(k, mapped_type())); }
		const_iterator lower_bound (const key_type& k) const { return _tree.lower_bound(ft::make_pair(k, mapped_type())); }

		iterator upper_bound (const key_type& k) { return iterator(_tree.upper_bound(ft::make_pair(k, mapped_type()))); }
		const_iterator upper_bound (const key_type& k) const { return (_tree.upper_bound(ft::make_pair(k, mapped_type()))); }

		ft::pair<iterator, iterator> equal_range (const key_type& k) { return _tree.equal_range(ft::make_pair(k, mapped_type())); }
		ft::pair<const_iterator, const_iterator> equal_range (const key_type& k) const { return _tree.equal_range(ft::make_pair(k, mapped_type())); }
	

		/* ************* */
		/*   Allocator   */
		/* ************* */
		
		allocator_type get_allocator() const { return _tree.get_allocator(); }
	};


	/* ************************ */
	/*   Relational Operators   */
	/* ************************ */

	template <class _Key, class _Tp, class _Compare, class _Allocator>
	bool operator==(const map<_Key, _Tp, _Compare, _Allocator>& x,
			const map<_Key, _Tp, _Compare, _Allocator>& y)
	{ return x.size() == y.size() && ft::equal(x.begin(), x.end(), y.begin()); }

	template <class _Key, class _Tp, class _Compare, class _Allocator>
	bool operator!=(const map<_Key, _Tp, _Compare, _Allocator>& x,
			const map<_Key, _Tp, _Compare, _Allocator>& y)
	{ return !(x == y); }

	template <class _Key, class _Tp, class _Compare, class _Allocator>
	bool operator< (const map<_Key, _Tp, _Compare, _Allocator>& x,
			const map<_Key, _Tp, _Compare, _Allocator>& y)
	{ return ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end()); }

	template <class _Key, class _Tp, class _Compare, class _Allocator>
	bool operator> (const map<_Key, _Tp, _Compare, _Allocator>& x,
			const map<_Key, _Tp, _Compare, _Allocator>& y)
	{ return y < x; }

	template <class _Key, class _Tp, class _Compare, class _Allocator>
	bool operator>=(const map<_Key, _Tp, _Compare, _Allocator>& x,
			const map<_Key, _Tp, _Compare, _Allocator>& y)
	{ return !(x < y); }

	template <class _Key, class _Tp, class _Compare, class _Allocator>
	bool operator<=(const map<_Key, _Tp, _Compare, _Allocator>& x,
			const map<_Key, _Tp, _Compare, _Allocator>& y)
	{ return !(y < x); }


	/* ******** */
	/*   Swap   */
	/* ******** */

	template <class _Key, class _Tp, class _Compare, class _Allocator>
	void swap(map<_Key, _Tp, _Compare, _Allocator>& x,
			map<_Key, _Tp, _Compare, _Allocator>& y)
	{ x.swap(y); }

}

#endif