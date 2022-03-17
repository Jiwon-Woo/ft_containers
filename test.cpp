#include <iostream>
#include <string>

#include <algorithm>    // std::lexicographical_compare
#include <cctype>       // std::tolower

#include "map.hpp"
#include "stack.hpp"
#include "vector.hpp"
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



int main()
{
	ft::vector<int> zeroVec;
	ft::vector<int> fiveVec(5);

	std::cout << zeroVec.size() << std::endl;
	std::cout << zeroVec.capacity() << std::endl;
	std::cout << std::endl;

	std::cout << fiveVec.size() << std::endl;
	std::cout << fiveVec.capacity() << std::endl;
	std::cout << std::endl;

	for (ft::vector<int>::iterator it = fiveVec.begin(); it != fiveVec.end(); it++)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;
	std::cout << std::endl;

	fiveVec[0] = 1;
	fiveVec[1] = 2;
	fiveVec[2] = 3;
	fiveVec[3] = 4;
	fiveVec[4] = 5;

	for (ft::vector<int>::iterator it = fiveVec.begin(); it != fiveVec.end(); it++)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;

	ft::vector<int>::iterator begin = fiveVec.begin();
	std::cout << begin[2] << std::endl;


	ft::vector<int> copyIterVec(fiveVec.begin(), fiveVec.end());
	for (ft::vector<int>::iterator it = copyIterVec.begin(); it != copyIterVec.end(); it++)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;
	std::cout << std::endl;

	copyIterVec[2] = 7;
	for (ft::vector<int>::iterator it = fiveVec.begin(); it != fiveVec.end(); it++)
	{ std::cout << *it << " "; }
	std::cout << std::endl;
	for (ft::vector<int>::iterator it = copyIterVec.begin(); it != copyIterVec.end(); it++)
	{ std::cout << *it << " "; }
	std::cout << std::endl;
	std::cout << std::endl;

	fiveVec[0] = -1;
	for (ft::vector<int>::iterator it = fiveVec.begin(); it != fiveVec.end(); it++)
	{ std::cout << *it << " "; }
	std::cout << std::endl;
	for (ft::vector<int>::iterator it = copyIterVec.begin(); it != copyIterVec.end(); it++)
	{ std::cout << *it << " "; }
	std::cout << std::endl;
	std::cout << std::endl;

	ft::vector<int> copyVec(fiveVec);
	for (ft::vector<int>::iterator it = copyVec.begin(); it != copyVec.end(); it++)
	{ std::cout << *it << " "; }
	std::cout << std::endl;

	ft::vector<int> copycopyVec(copyIterVec);
	for (ft::vector<int>::iterator it = copycopyVec.begin(); it != copycopyVec.end(); it++)
	{ std::cout << *it << " "; }
	std::cout << std::endl;

	const ft::vector<int> constFiveVec(5);
	ft::vector<int> constCopyVec(constFiveVec);
	for (ft::vector<int>::iterator it = constCopyVec.begin(); it != constCopyVec.end(); it++)
	{ std::cout << *it << " "; }
	std::cout << std::endl;
	std::cout << std::endl;

	std::cout << zeroVec.max_size() << std::endl;
	std::cout << fiveVec.max_size() << std::endl;
	std::cout << constCopyVec.max_size() << std::endl;
	return (0);
}
