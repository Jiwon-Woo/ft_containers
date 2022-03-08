#include <iostream>
#include <string>
#include <deque>

#include <vector>
#include <algorithm>    // std::lexicographical_compare
#include <cctype>       // std::tolower

#include "map.hpp"
#include "stack.hpp"
// #include "vector.hpp"
#include "iterator.hpp"
#include "utils.hpp"

#include <stdlib.h>

#define MAX_RAM 4294967296
#define BUFFER_SIZE 4096
struct Buffer
{
	int idx;
	char buff[BUFFER_SIZE];
};


#define COUNT (MAX_RAM / (int)sizeof(Buffer))

template <typename T>
typename ft::enable_if<ft::is_integral<T>::value, T>::type	isInt(T t)
{
	std::cout << t << " is Int!\n";
	return t;
}

bool mypredicate (int i, int j) {
	return (i == j);
}

// a case-insensitive comparison function:
bool mycomp (char c1, char c2) {
	return std::tolower(c1) < std::tolower(c2);
}

int main() {
	isInt(4);
	// isInt(4.0);

	int myints[] = {20,40,60,80,100};
	std::vector<int> myvector(myints,myints+5);

	// using default comparison:
	if ( std::equal (myvector.begin(), myvector.end(), myints) )
		std::cout << "The contents of both sequences are equal.\n";
	else
		std::cout << "The contents of both sequences differ.\n";

	// using predicate comparison:
	if ( std::equal (myvector.begin(), myvector.end(), myints, mypredicate) )
		std::cout << "The contents of both sequences are equal.\n";
	else
		std::cout << "The contents of both sequences differ.\n";

	myvector[3]=81;

	// using default comparison:
	if ( std::equal (myvector.begin(), myvector.end(), myints) )
		std::cout << "The contents of both sequences are equal.\n";
	else
		std::cout << "The contents of both sequences differ.\n";

	// using predicate comparison:
	if ( std::equal (myvector.begin(), myvector.end(), myints, mypredicate) )
		std::cout << "The contents of both sequences are equal.\n";
	else
		std::cout << "The contents of both sequences differ.\n";

	char foo[]="APPLE";
	char bar[]="apartment";

	std::cout << std::boolalpha;

	std::cout << "Comparing foo and bar lexicographically (foo<bar):\n";

	std::cout << "Using default comparison (operator<): ";
	std::cout << std::lexicographical_compare(foo,foo+5,bar,bar+9);
	std::cout << '\n';

	std::cout << "Using mycomp as comparison object: ";
	std::cout << std::lexicographical_compare(foo,foo+5,bar,bar+9,mycomp);
	std::cout << '\n';

	return (0);
}
