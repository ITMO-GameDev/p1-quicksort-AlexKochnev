#include <iostream>
#include "sort.h"
#include "containers.h"

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

template <typename T>
void PrintArrayInfo(Array<T>& arr)
{
	std::cout << "Array capacity = " << arr.returnCapacity() << std::endl;
	std::cout << "Array size = " << arr.returnSize() << std::endl;

	auto it = arr.begin();
	while (it.hasNext()) {
		it.next();
		std::cout << it.get() << ' ';
	};
	std::cout << std::endl;
	std::cout << "-------------------------\n";
}


Array<int> generate()
{
	Array<int> a(3);
	a.insert(100);
	a.insert(200);
	a.insert(300);
	Array<int> b(std::move(a));
	//    Array<int> b = a;
	return b;
}


void arrayTmp()
{
	Array<int> a(0);
	for (int i = 0; i < 9; i++)
		a.insert(i, i);


	PrintArrayInfo(a);

	auto it1 = a.end();
	while (it1.hasPrev()) {
		it1.prev();
		std::cout << it1.get() << ' ';
	};
	std::cout << std::endl;

	a = generate();
	PrintArrayInfo(a);

	a.insert(400);
	a.insert(0, 50);
	a.insert(4, 350);
	a.insert(500);
	PrintArrayInfo(a);
}

void linkedListTmp()
{
	LinkedList<int> l;
	for (int i = 0; i < 10; i++)
		l.insertHead(i);

	std::cout << l.head() << '\n';
	std::cout << l.tail() << '\n';
	l.removeHead();
	std::cout << l.head() << '\n';
	std::cout << l.tail() << '\n';
	l.removeTail();
	std::cout << l.head() << '\n';
	std::cout << l.tail() << '\n';
	std::cout << l.head() << '\n';
}

int main(int argc, char** argv)
{
	//int array[] = {7, 2, 2, 2, 1, 5, 5, 5, 0};
	//sortTmp(array, sizeof (array)/ sizeof (int));
	arrayTmp();
	linkedListTmp();
	return 0;
}
