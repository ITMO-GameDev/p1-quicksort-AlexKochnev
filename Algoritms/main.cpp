#include <iostream>
#include "sort.h"
#include "containers.h"
#include "dictonary.h"
#include "memory_allocator.h"

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


void dictTmp()
{
	Dictonary<int, int> d;
	d.put(9, 4);
	d.put(8, 2);
	d.put(6, 3);
	d.put(7, 1);
	d.put(1, 3);
	d.put(3, 3);
	d.put(2, 3);
	d.put(5, 3);
	d.put(22, 3);
	d.put(-22, 3);
	d.put(-5, 3);
	std::cout << d.pformat();
	std::cout << "--------------------------------\n";
	std::cout << "size =" << d.size() << std::endl;
	std::cout << "--------------------------------\n";
	d.remove(22);
	d.remove(1);
	std::cout << d.pformat();
	std::cout << "--------------------------------\n";
	std::cout << d.contains(5) << std::endl;
	std::cout << d.contains(100) << std::endl;
	std::cout << "--------------------------------\n";
	std::cout << d[5] << std::endl;
	//    std::cout << d[0] << std::endl; // KeyError
	std::cout << "--------------------------------\n";
	std::cout << "size =" << d.size() << std::endl;
	std::cout << "--------------------------------\n";
	auto i = d.begin();
	i.next();
	std::cout << i.key() << '\n';
	i.next();
	std::cout << i.key() << '\n';
	i.next();
	std::cout << i.key() << '\n';
	i.next();
	std::cout << i.key() << '\n';

	std::cout << "get prev\n";
	i.prev();
	std::cout << i.key() << '\n';
	i.prev();
	std::cout << i.key() << '\n';
	i.prev();
	std::cout << i.key() << '\n';
	i.prev();
	std::cout << i.key() << '\n';
	i.prev();
	std::cout << i.key() << '\n';
	i.prev();
	std::cout << i.key() << '\n';
	i.prev();
	std::cout << i.key() << '\n';
	i.prev();
	std::cout << i.key() << '\n';
	i.prev();
	std::cout << i.key() << '\n';
}

void allocatorTmp()
{
	MemoryAllocator allocator;
	allocator.init();

	int* pi = (int*)allocator.alloc(sizeof(int));
	double* pd = (double*)allocator.alloc(sizeof(double));
	int* pa = (int*)allocator.alloc(10 * sizeof(int));
	int* pl[10];
	for (size_t i = 0; i < 10; ++i)
	{
		pl[i] = (int*)allocator.alloc(100 * sizeof(int));
	}

	int* bpi = (int*)allocator.alloc(1000 * sizeof(int));
	double* bpd = (double*)allocator.alloc(1000 * sizeof(double));
	double* bpl = (double*)allocator.alloc(1000 * sizeof(long));
	int* bpa = (int*)allocator.alloc(1000000 * sizeof(int));

#ifndef NDEBUG
	std::cout << "Before user freeing:\n";
	std::cout << "Overall memory statistics:\n";
	allocator.dumpStat();
	std::cout << "\nAllocated memory statistics:\n";
	allocator.dumpBlocks();
	std::cout << std::endl;
#endif

	allocator.free(pa);
	allocator.free(pd);
	allocator.free(pi);
	for (auto p : pl)
	{
		allocator.free(p);
	}

	allocator.free(bpa);
	allocator.free(bpl);
	allocator.free(bpi);
	allocator.free(bpd);

#ifndef NDEBUG
	std::cout << "After user freeing:\n";
	std::cout << "Overall memory statistics:\n";
	allocator.dumpStat();
	std::cout << "\nAllocated memory statistics:\n";
	allocator.dumpBlocks();
	std::cout << std::endl;
#endif

	std::cout << "Checking detecting leaks (should report 2 leaks):\n";
	allocator.alloc(128);
	allocator.alloc(1024);
}
int main(int argc, char** argv)
{
	    //int array[] = {7, 2, 2, 2, 1, 5, 5, 5, 0};
	    //sortTmp(array, sizeof (array)/ sizeof (int));
	    //arrayTmp();
	    //linkedListTmp();
		//dictTmp();
		//allocatorTmp();
	return 0;
}
