#include <iostream>
#include <algorithm>
#include <map>

int main()
{
	std::map<int, int> m;
	std::map<int, int>::iterator mi;

	std::cout << "erase empty map: " << m.erase(0) << std::endl;

	m[1] = 3;
	m[2] = 6;
	m[0] = 0;

	std::cout << "erase invalid key: " << m.erase(-1) << std::endl;
	std::cout << "erase key: " << m.erase(0) << std::endl;


	// std::cout << (m.begin() == m.end()) << std::endl;

	for (mi = m.begin(); mi != m.end(); mi++) {
		std::cout << mi->first << ": " << mi->second << std::endl;
	}
	std::cout << "[end]" << std::endl;
	std::cout << mi->first << ": " << mi->second << std::endl;
	return 0;
}