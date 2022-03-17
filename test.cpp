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

	ft::vector<int> copyVec = copyIterVec;
	for (ft::vector<int>::iterator it = copyVec.begin(); it != copyVec.end(); it++)
	{ std::cout << *it << " "; }
	std::cout << std::endl;

	ft::vector<int> copycopyVec = fiveVec;
	for (ft::vector<int>::iterator it = copycopyVec.begin(); it != copycopyVec.end(); it++)
	{ std::cout << *it << " "; }
	std::cout << std::endl;
	std::cout << std::endl;

	const ft::vector<int> constFiveVec(5);
	ft::vector<int> constCopyVec = zeroVec;
	constCopyVec.resize(4, 100);
	constCopyVec.resize(6);
	constCopyVec.resize(2);
	std::cout << constCopyVec.size() << " " << constCopyVec.capacity() << std::endl;
	constCopyVec.reserve(45);
	std::cout << constCopyVec.size() << " " << constCopyVec.capacity() << std::endl;
	for (ft::vector<int>::iterator it = constCopyVec.begin(); it != constCopyVec.end(); it++)
	{ std::cout << *it << " "; }
	std::cout << std::endl;
	for (ft::vector<int>::iterator it = zeroVec.begin(); it != zeroVec.end(); it++)
	{ std::cout << *it << " "; }
	std::cout << std::endl;

	std::cout << zeroVec.max_size() << std::endl;
	std::cout << fiveVec.max_size() << std::endl;
	std::cout << constCopyVec.max_size() << std::endl;
	std::cout << constFiveVec[3] << std::endl;
	std::cout << constFiveVec[4] << std::endl;

	try
	{
		std::cout << constFiveVec[6] << std::endl;
		/* code */
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
	ft::vector<int> noneVec;
	std::cout << noneVec.size() << " " << noneVec.capacity() << std::endl;
	noneVec.reserve(5);
	std::cout << noneVec.size() << " " << noneVec.capacity() << std::endl;
	// while (1);
	return (0);
}
