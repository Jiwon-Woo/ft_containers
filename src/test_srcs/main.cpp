#include "containers.hpp"
#include "map/mapTests.hpp"
#include "vector/vectorTests.hpp"
#include "stack/stackTests.hpp"

#include <time.h>

void    title(std::string name)
{
    std::string str = "# ";
    int n;

    n = 54 - name.size();
    if (n % 2 == 0)
         str.insert(str.end(), n / 2 - 1, ' ');
    else
         str.insert(str.end(), n / 2 , ' ');
    str += name;
    str.insert(str.end(), n / 2, ' ');
    str += "# ";
	std::cout	<< "# **************************************************** #" << std::endl
				<< str << std::endl
				<< "# **************************************************** #" << std::endl
				<< std::endl;
}

void heading(std::string name)
{
    std::string str;
    int n;

    n = 28 - name.size();
    if (n % 2 == 0)
         str.insert(str.end(), n / 2 - 1, '#');
    else
         str.insert(str.end(), n / 2 , '#');
    str += " ";
    str += name;
    str += " ";
    str.insert(str.end(), n / 2, '#');
	std::cout	<< "#############################" << std::endl
				<< str << std::endl;
}

int main()
{
	ft::vector<int>			vect;
	ft::map<int, int>		map;
	ft::stack<int>			     stack;
	clock_t					start, end;
	
	/* to be sure of the namespace used, you can uncomment this : */
	// title(NAMESPACE);

	start = clock();
	vectorTests(vect);
	mapTests(map);
	stackTests(stack);
	end = clock();
	std::cout << "END." << std::endl;
	std::cout << "Time: " << (double)(end - start) / CLOCKS_PER_SEC << "s" << std::endl;
	return (0);
}


