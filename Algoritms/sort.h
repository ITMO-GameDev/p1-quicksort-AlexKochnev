#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <iostream>
#include <memory>

using namespace std;

const int MAXTHRESH = 16; // taken from GNU's qsort


template<typename T>
T mediana(T* first, T* second, T* third)
{
	if (*first <= *second)
	{
		if (*third >= *second)
			return *second;
		else if (*third >= *first)
			return *third;
		else
			return *first;
	}
	else
	{
		if (*second >= *third)
			return *second;
		else if (*third <= *first)
			return *third;
		else
			return *first;
	}
}


template <typename T>
T GetPivot(T* first, T* last)
{
	T* MiddleElementIndex;
	MiddleElementIndex = first + ((last - first) / 2);
	return mediana(first, MiddleElementIndex, last);
}


template<typename T, typename ComparatorFunc>
int HoarePartition(T* first, T* last, ComparatorFunc comparator)
{
	int i = -1;
	int j = last - first + 1;
	T pivot = GetPivot(first, last);

	while (true) {
		do { i++; } while (comparator(first[i], pivot));

		do { j--; } while (comparator(pivot, first[j]));

		if (i >= j)
			return j;
		std::swap(first[i], first[j]);
	}
}


template<typename T, typename ComparatorFunc>
void sort(T* first, T* last, ComparatorFunc comparator);


template<typename T, typename ComparatorFunc>
void quicksort(T* first, T* last, ComparatorFunc comparator)
{
	while (last > first)
	{
		int pivot = HoarePartition(first, last, comparator);

		if (&first[pivot] - first < last - &first[pivot])
		{
			sort(first, &first[pivot], comparator);
			first = &first[pivot + 1];
		}
		else
		{
			sort(&first[pivot + 1], last, comparator);
			last = &first[pivot];
		}
	}
}


template<typename T, typename ComparatorFunc>
void insertionsort(T* first, T* last, ComparatorFunc comparator)
{
	T tmp;
	int previousElementIndex;

	for (int cnt = 1; cnt < last - first + 1; cnt++)
	{
		tmp = first[cnt];
		previousElementIndex = cnt - 1;
		while (previousElementIndex >= 0 && comparator(tmp, first[previousElementIndex]))
		{
			first[previousElementIndex + 1] = first[previousElementIndex];
			first[previousElementIndex] = tmp;
			previousElementIndex--;
		}
	}
}


template<typename T, typename ComparatorFunc>
void sort(T* first, T* last, ComparatorFunc comparator)
{
	if (last - first < MAXTHRESH)
		insertionsort(first, last, comparator);
	else
		quicksort(first, last, comparator);
}


template <typename T>
bool ForwardComparator(T a, T b)
{
	return a < b;
}


template <typename T>
bool BorwardComparator(T a, T b)
{
	return a > b;
}


#endif // QUICKSORT_H
