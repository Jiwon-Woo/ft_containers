#include <iostream>
#include <algorithm>
#include <map>

int main()
{
	std::map<int, int> m;
	std::map<int, int>::iterator mi;

	m[1] = 3;
	m[2] = 6;
	m[0] = 0;

	// std::cout << (m.begin() == m.end()) << std::endl;

	for (mi = m.begin(); mi != m.end(); mi++) {
		std::cout << mi->first << std::endl;
		std::cout << mi->second << std::endl;
	}
	std::cout << mi->first << std::endl;
	std::cout << mi->second << std::endl;
	++mi;
	std::cout << mi->first << std::endl;
	std::cout << mi->second << std::endl;
	return 0;
}