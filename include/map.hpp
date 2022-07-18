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
		typedef Key                                          	key_type;
		typedef T                                            	mapped_type;
		typedef ft::pair<const key_type, mapped_type>        	value_type;
		typedef Compare                                      	key_compare;
		typedef Alloc                                        	allocator_type;
		typedef std::ptrdiff_t                               	difference_type;
		typedef std::size_t                                  	size_type;
		typedef typename allocator_type::reference           	reference;
		typedef typename allocator_type::const_reference     	const_reference;
		typedef typename allocator_type::pointer             	pointer;
		typedef typename allocator_type::const_pointer       	const_pointer;
		typedef ft::map_iterator<value_type>                 	iterator;
		typedef ft::map_iterator<const value_type>           	const_iterator;
		typedef typename ft::reverse_iterator<iterator>      	reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator>	const_reverse_iterator;

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

	private:
		ft::tree<value_type, value_compare, allocator_type> tree;
	
	public:
		// Constructor:
		explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());
		template <class InputIterator>
		map (InputIterator first, InputIterator last,
			const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type());
		map (const map& x);

		// Destructor:
		~map();

		// Assignment:
		map& operator=(map const &m);

		// iterators:
		iterator begin();
		const_iterator begin() const;
		iterator end();
		const_iterator end()   const;

		reverse_iterator rbegin();
		const_reverse_iterator rbegin() const;
		reverse_iterator rend();
		const_reverse_iterator rend()   const;

		// capacity:
		bool      empty()    const noexcept;
		size_type size()     const noexcept;
		size_type max_size() const noexcept;

		// element access:
		mapped_type& operator[](const key_type& k);

		// modifiers:
		pair<iterator,bool> insert (const value_type& val);
		iterator insert (iterator position, const value_type& val);
		template <class InputIterator>
		void insert (InputIterator first, InputIterator last);
		void erase (iterator position);
		size_type erase (const key_type& k);
		void erase (iterator first, iterator last);
		void clear();

		// observers:
		// value_compare value_comp() const;
		// key_compare    key_comp()      const;

		// map operations:
		iterator find(const key_type& k);
		const_iterator find(const key_type& k) const;
		size_type count (const key_type& k) const;
		iterator lower_bound (const key_type& k);
		const_iterator lower_bound (const key_type& k) const;
		iterator lower_bound (const key_type& k);
		const_iterator lower_bound (const key_type& k) const;
		iterator upper_bound (const key_type& k);
		const_iterator upper_bound (const key_type& k) const;
		pair<const_iterator,const_iterator> equal_range (const key_type& k) const;
		pair<iterator,iterator>             equal_range (const key_type& k);
	};
}

#endif