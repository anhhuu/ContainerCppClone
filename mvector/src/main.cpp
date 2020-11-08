#include <iostream>
#include "mvector.h"
#include "mmap.h"

int main()
{
	mvector<int> vectorTest;
	vectorTest.push_back(1);
	vectorTest.push_back(2);
	vectorTest.push_back(3);
	vectorTest.push_back(4);
	vectorTest.push_back(5);
	vectorTest.push_back(6);

	std::cout << "My vector: \t\t\t\t";

	for (mvector<int>::iterator i = vectorTest.begin(); i != vectorTest.end(); i++)
	{
		std::cout << *(i) << "\t";
	}

	std::cout << std::endl << "My vector after delete 3: \t\t";
	vectorTest.erase(vectorTest.begin() + 2);
	for (mvector<int>::iterator i = vectorTest.begin(); i != vectorTest.end(); i++)
	{
		std::cout << *(i) << "\t";
	}

	std::cout << std::endl << "My vector after delete 4, 5: \t\t";
	vectorTest.erase(vectorTest.begin() + 2, vectorTest.begin() + 4);
	for (mvector<int>::iterator i = vectorTest.begin(); i != vectorTest.end(); i++)
	{
		std::cout << *(i) << "\t";
	}

	std::cout << std::endl << "My vector after add 3 on pos = 2: \t";
	vectorTest.insert(vectorTest.begin() + 2, 3);
	for (mvector<int>::iterator i = vectorTest.begin(); i != vectorTest.end(); i++)
	{
		std::cout << *(i) << "\t";
	}

	mvector<int> addVector;
	addVector.push_back(4);
	addVector.push_back(5);
	std::cout << std::endl << "My vector after add 4, 5 on pos = 3: \t";
	vectorTest.insert(vectorTest.begin() + 3, addVector.begin(), addVector.end());
	for (mvector<int>::iterator i = vectorTest.begin(); i != vectorTest.end(); i++)
	{
		std::cout << *(i) << "\t";
	}

	std::cout << std::endl;

	mmap<int, int> mapTest;
	mapTest.insert(pair<int, int>(3, 1));
	mapTest.insert(pair<int, int>(1, 1));
	mapTest.insert(pair<int, int>(1, 1));
	mapTest.insert(pair<int, int>(2, 5));

	std::cout << "map iterator: " << std::endl;
	for (mmap<int, int>::iterator i = mapTest.begin(); i != mapTest.end(); i++)
	{
		std::cout << "Key: " << i->first << "\tValue: " << i->second << std::endl;
	}
	std::cout << std::endl << "map operator[], at() method: " << std::endl; 
	std::cout << "Key: " << 1 << "\tValue: " << mapTest[1] << std::endl;
	std::cout << "Key: " << 3 << "\tValue: " << mapTest.at(3) << std::endl;

	auto finder = mapTest.find(2);

	if (finder != mapTest.end())
	{
		std::cout << "Finder: key = 2" << std::endl;
		std::cout << "Key: " << finder->first << "\tValue: " << finder->second << std::endl;
	}

	system("pause");
	return 0;
}

