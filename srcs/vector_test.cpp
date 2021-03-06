#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
	std::vector<int> emptyVec;
	std::vector<int> zeroVec;
	std::vector<int> fiveVec(5);
	std::vector<int> manyVec(4);

	std::cout << zeroVec.size() << std::endl;
	std::cout << zeroVec.capacity() << std::endl;
	zeroVec.push_back(1);
	std::cout << zeroVec.size() << std::endl;
	std::cout << zeroVec.capacity() << std::endl;
	zeroVec.push_back(2);
	std::cout << zeroVec.size() << std::endl;
	std::cout << zeroVec.capacity() << std::endl;
	zeroVec.push_back(3);
	std::cout << zeroVec.size() << std::endl;
	std::cout << zeroVec.capacity() << std::endl;
	std::cout << std::endl;

	std::cout << fiveVec.size() << std::endl;
	std::cout << fiveVec.capacity() << std::endl;
	fiveVec.push_back(5);
	std::cout << fiveVec.size() << std::endl;
	std::cout << fiveVec.capacity() << std::endl;
	std::cout << std::endl;

	for (std::vector<int>::iterator it = fiveVec.begin(); it != fiveVec.end(); it++)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;

	std::cout << manyVec.size() << std::endl;
	std::cout << manyVec.capacity() << std::endl;
	std::cout << std::endl;
	manyVec = fiveVec;
	std::cout << fiveVec.size() << std::endl;
	std::cout << fiveVec.capacity() << std::endl;
	std::cout << manyVec.size() << std::endl;
	std::cout << manyVec.capacity() << std::endl;
	manyVec.assign(7, 7);
	std::cout << manyVec.size() << std::endl;
	std::cout << manyVec.capacity() << std::endl;

	std::cout << std::endl;
	for (std::vector<int>::iterator it = fiveVec.begin(); it != fiveVec.end(); it++)
	{ std::cout << *it << " "; }
	std::cout << std::endl;
	for (std::vector<int>::iterator it = manyVec.begin(); it != manyVec.end(); it++)
	{ std::cout << *it << " "; }
	std::cout << std::endl;
	std::cout << std::endl;

	std::cout << fiveVec.size() << " " << fiveVec.capacity() << std::endl;
	std::cout << manyVec.size() << " " << manyVec.capacity() << std::endl;
	std::cout << std::endl;

	manyVec.swap(fiveVec);

	for (std::vector<int>::iterator it = fiveVec.begin(); it != fiveVec.end(); it++)
	{ std::cout << *it << " "; }
	std::cout << std::endl;
	for (std::vector<int>::iterator it = manyVec.begin(); it != manyVec.end(); it++)
	{ std::cout << *it << " "; }
	std::cout << std::endl;
	std::cout << std::endl;

	std::cout << &(*(manyVec.begin() + 2)) << std::endl;
	std::cout << &(*manyVec.erase(manyVec.begin() + 2)) << std::endl;

	std::cout << fiveVec.size() << " " << fiveVec.capacity() << std::endl;
	std::cout << manyVec.size() << " " << manyVec.capacity() << std::endl;

	emptyVec.reserve(2);
	std::cout << std::endl;

	std::cout << fiveVec.size() << std::endl;
	std::cout << fiveVec.capacity() << std::endl;
	fiveVec.insert(fiveVec.begin() + 3, 8, 17);
	std::cout << fiveVec.size() << std::endl;
	std::cout << fiveVec.capacity() << std::endl;
}