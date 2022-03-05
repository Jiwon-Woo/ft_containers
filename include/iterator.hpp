#ifndef ITERATOR_HPP
# define ITERATOR_HPP

#include <cstddef>

namespace ft
{

	/* ************* */
	/*   Functions   */
	/* ************* */

	/* Iterator operations */

	// template <class InputIterator, class Distance>
	// void advance (InputIterator& it, Distance n)
	// {

	// };

	// template<class InputIterator>
	// typename iterator_traits<InputIterator>::difference_type \
	// 	distance (InputIterator first, InputIterator last)
	// {

	// };


	/* Iterator generators */

	// template <class Container>
	// back_insert_iterator<Container> back_inserter (Container& x)
	// {
		
	// };

	// template <class Container>
	// front_insert_iterator<Container> front_inserter (Container& x)
	// {
		
	// };

	// template <class Container, class Iterator>
	// insert_iterator<Container> inserter (Container& x, Iterator it)
	// {
		
	// };



	/* *********** */
	/*   Classes   */
	/* *********** */

	/* Category tags */

	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag : public input_iterator_tag {};
	struct bidirectional_iterator_tag : public forward_iterator_tag {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};


	// Iterator base class
	template <typename Category,
				typename T,
				typename Distance = std::ptrdiff_t,
				typename Pointer = T*,
				typename Reference = T&>
	class iterator
	{
	public:
		typedef T        	value_type;
		typedef Distance 	difference_type;
		typedef Pointer  	pointer;
		typedef Reference	reference;
		typedef Category 	iterator_category;
	};

	// Iterator traits
	template <typename Iterator>
	class iterator_traits
	{
	public:
		typedef typename Iterator::difference_type  	difference_type;
		typedef typename Iterator::value_type       	value_type;
		typedef typename Iterator::pointer          	pointer;
		typedef typename Iterator::reference        	reference;
		typedef typename Iterator::iterator_category	iterator_category;
	};

	template <typename T>
	class iterator_traits<T*>
	{
	public:
		typedef ptrdiff_t                 	difference_type;
		typedef T                         	value_type;
		typedef T*                        	pointer;
		typedef T&                        	reference;
		typedef random_access_iterator_tag	iterator_category;
	};

	template <typename T>
	class iterator_traits<const T*>
	{
	public:
		typedef ptrdiff_t                 	difference_type;
		typedef T                         	value_type;
		typedef const T*                  	pointer;
		typedef const T&                  	reference;
		typedef random_access_iterator_tag	iterator_category;
	};


	/* Predefined iterators */

	template <typename Iterator>
	class reverse_iterator
		: public iterator<typename iterator_traits<Iterator>::iterator_category,
						typename iterator_traits<Iterator>::value_type,
						typename iterator_traits<Iterator>::difference_type,
						typename iterator_traits<Iterator>::pointer,
						typename iterator_traits<Iterator>::reference>
	{
	public:
		/* Member types */
		typedef Iterator                                             	iterator_type;
		typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
		typedef typename iterator_traits<Iterator>::value_type       	value_type;
		typedef typename iterator_traits<Iterator>::difference_type  	difference_type;
		typedef typename iterator_traits<Iterator>::pointer          	pointer;
		typedef typename iterator_traits<Iterator>::reference        	reference;

		/* Member functions */
		// Constructs
		reverse_iterator();
		explicit reverse_iterator (iterator_type it);
		template <class Iter>
		reverse_iterator (const reverse_iterator<Iter>& rev_it);
		
	};

	// template <class Container>
	// class back_insert_iterator : public iterator<>
	// {

	// };

	// template <class Container>
	// class front_insert_iterator : public iterator<>
	// {

	// };

	// template <class Container>
	// class insert_iterator : public iterator<>
	// {

	// };

	// template <class T, class charT=char, class traits=char_traits<charT>, 
	// 		class Distance = ptrdiff_t>
	// class istream_iterator : public iterator<>
	// {

	// };

	// template <class T, class charT=char, class traits=char_traits<charT> >
	// class ostream_iterator : public iterator<>
	// {

	// };

	// template <class charT, class traits=char_traits<charT> >
	// class istreambuf_iterator : public iterator<>
	// {

	// };

	// template <class charT, class traits=char_traits<charT> >
	// class ostreambuf_iterator : public iterator<>
	// {

	// };




}

#endif