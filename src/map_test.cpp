#include <iostream>
#include <algorithm>
#include <string>
#include <deque>
#ifdef FT
	#include <map.hpp>
	#include <stack.hpp>
	#include <vector.hpp>
#else
	#include <map>
	#include <stack>
	#include <vector>
	namespace ft = std;
#endif


int main()
{
	ft::map<int, int> m;
	ft::map<int, int>::iterator mi;

	std::cout << "erase empty map: " << m.erase(0) << std::endl;

	m[1] = 3;
	m[2] = 6;
	m[0] = 0;

	std::cout << "erase invalid key: " << m.erase(-1) << std::endl;
	std::cout << "erase key: " << m.erase(0) << std::endl;

	for (mi = m.begin(); mi != m.end(); mi++) {
		std::cout << mi->first << ": " << mi->second << std::endl;
	}
	std::cout << "[end]" << std::endl;
	std::cout << mi->first << ": " << mi->second << std::endl;
	return 0;
}