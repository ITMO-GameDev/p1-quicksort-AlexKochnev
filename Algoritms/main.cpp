#include <iostream>
#include "sort.h"


template <typename T>
void printarray(const T* first, const T* last)
{
	for (int i = 0; first + i <= last; i++)
		std::cout << *(first + i) << " ";
	std::cout << "\n";
	std::cout << "-------------------------\n";
}


void sortTmp(int* arr, int size)
{
	bool (*comparatorptr)(int, int) = ForwardComparator;
	sort(arr, arr + size - 1, comparatorptr);
	printarray(arr, arr + size - 1);
	return;
}

int main(int argc, char** argv)
{
	int array[] = {7, 2, 2, 2, 1, 5, 5, 5, 0};
	sortTmp(array, sizeof (array)/ sizeof (int));
	return 0;
}
