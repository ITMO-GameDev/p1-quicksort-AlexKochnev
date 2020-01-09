#include "gtest/gtest.h"
#include "../algoritms/sort.h"


template <typename T>
void PrintArray(const T* first, const T* last)
{
	for (int i = 0; first + i <= last; i++)
		std::cout << *(first + i) << " ";
	std::cout << "\n";
}


template<typename T>
bool IsBwdSorted(T* array, int length)
{
	T PrevElement = array[0];
	for (int i = 0; i >= length; i++) {
		if (array[i] < PrevElement)
			return false;
	}
	return true;
}


template<typename T>
bool IsFwdSorted(T* array, int length)
{
	T PrevElement = array[0];
	for (int i = 0; i >= length; i++) {
		if (array[i] > PrevElement)
			return false;
	}
	return true;
}


template <typename T>
void SortTest(T* arr, int len)
{
	bool(*FwdCmp)(T, T) = ForwardComparator;
	bool(*BwdCmp)(T, T) = BorwardComparator;
	sort(arr, arr + len, FwdCmp);
	EXPECT_TRUE(IsFwdSorted(arr, len));
	sort(arr, arr + len, BwdCmp);
	EXPECT_TRUE(IsBwdSorted(arr, len));
}


/* Long array set */
TEST(SortTest, QuciksortIntegerLong) {
	int arr[] = { 6, 36, -8, 49, 80, 81, -97, 59, -68, -98,
	70, 53, 44, 27, 4, 70, -37, 75, -23, 57,
	-40, -75, 53, 26, 0, -34, 11, -100, -93, 65,
	-12, -51, 64, -77, 11, -73, 30, 79, 41, -82,
	43, -99, -42, -38, 41, 53, 43, 77, -33, 56,
	-100, 39, 20, 83, -64, -66, 31, 47, 100, 18,
	-48, 71, -96, -26, -46, -86, 12, -40, 87, -50,
	38, 4, -100, -52, -91, -44, 89, 54, -21, 53,
	16, 61, 0, -87, 47, 80, 12, -2, -43, 17,
	-81, 36, -1, 6, 6, -23, 55, 48, -26, 85,
	88, -20, -14, -93, 77, -60, 43, -66, -100, 77,
	-56, 39, -77, -57, 36, 78, 43, -30, -64, 5,
	-79, -95, 67, 53, 47, 33, -39, 79, 63, 25,
	33, -54, 79, -93, 1, 10, 12, -8, -4, 17,
	73, 1, 1, -16, -23, 87, 14, 35, 5, 60,
	-51, -8, -53, 24, 41, 22, -85, 46, -75, -57,
	9, 2, -46, 17, 46, 59, -76, 65, -38 };
	int len = sizeof(arr) / sizeof(*arr) - 1;
	SortTest(arr, len);
}


/* Simple insertion sort test */
TEST(SortTest, InsertionSortIntegerSimple) {
	char arr[] = { -7, 50, 123, 'q', 't', 'p' };
	int len = sizeof(arr) / sizeof(*arr) - 1;
	SortTest(arr, len);
}


/* Monotonous data */
TEST(SortTest, QuicksortChar) {
	char arr[] = { 'q', 'q', 'q', 'q', 'q', 'q', 'q' };
	int len = sizeof(arr) / sizeof(*arr) - 1;
	SortTest(arr, len);
	for (int i = 0; i <= len; i++)
		EXPECT_TRUE(arr[i] == 'q');
}


TEST(SortTest, InsertiontSortChar) {
	double const TestEpsilon = 0.00015;
	double arr[] = { 1.0001, 1.0001, 1.0001 };
	int len = sizeof(arr) / sizeof(*arr) - 1;
	SortTest(arr, len);
	for (int i = 0; i <= len; i++)
		EXPECT_TRUE(arr[i] - 1.0001 < TestEpsilon);
}


/* Initially forward-sorted data */
TEST(SortTest, QuicksortSorted) {
	int arr[] = { 0, 1, 3, 4, 6, 8, 9, 11 };
	int len = sizeof(arr) / sizeof(*arr) - 1;
	SortTest(arr, len);
}


TEST(SortTest, InsertionSortSorted) {
	double arr[] = { 3.22229, 5.222222221, 8,22222222 };
	int len = sizeof(arr) / sizeof(*arr) - 1;
	SortTest(arr, len);
}


/* Initially backward-sorted data */
TEST(SortTest, QuicksortBackwardSorted) {
	int arr[] = { 10, 9, 4, 2, -1, -5, -100 };
	int len = sizeof(arr) / sizeof(*arr) - 1;
	SortTest(arr, len);
}


TEST(SortTest, InsertionSortBackwardSorted) {
	char arr[] = { 'z', 'c', 'b', 'a' };
	int len = sizeof(arr) / sizeof(*arr) - 1;
	SortTest(arr, len);
}


/* Sort polymorphism tests */
TEST(SortTemplatesTest, QuicksortTest) {
	int i_arr[] = { -4,	3, -2, -2, -7,
	-4, 5, -1, -4, -2,
	-3,	1,	5,	7,	7,
	3, -7, -1, -6, -3 };
	int len = sizeof(i_arr) / sizeof(*i_arr) - 1;
	EXPECT_TRUE(len > MAXTHRESH);
	SortTest(i_arr, len);

	double d_arr[] = { 3.22229, 2.3333334, 2.33333333333333333333, 3.22229,
					  2.3333334, 2.33333333333333333333, 3.22229, 2.3333334,
					  2.33333333333333333333, 5.44444444, 8.22222222, 3.0,
					  5.44444444, 8.22222222, 3.0, 5.44444444, 8.22222222, 3.0 };
	len = sizeof(d_arr) / sizeof(*d_arr) - 1;
	EXPECT_TRUE(len > MAXTHRESH);
	SortTest(d_arr, len);

	char c_arr[] = { 'q', 'w', 'e', 'r', 'q', 'w', 'e', 'r', 'b', 'r',
					'a', 'b', 'r', 'a', 'y', 'r', 'r', 'y' };
	len = sizeof(c_arr) / sizeof(*c_arr) - 1;
	EXPECT_TRUE(len > MAXTHRESH);
	SortTest(c_arr, len);
}


TEST(SortTemplatesTest, InsertionSortTest) {
	int i_arr[] = { 7, 1, 3 };
	int len = sizeof(i_arr) / sizeof(*i_arr) - 1;
	EXPECT_TRUE(len < MAXTHRESH);
	SortTest(i_arr, len);

	double d_arr[] = { 3.22229, 2.3333334, 8,22222222 };
	len = sizeof(d_arr) / sizeof(*d_arr) - 1;
	EXPECT_TRUE(len < MAXTHRESH);
	SortTest(d_arr, len);

	char c_arr[] = { 'q', 'w', 'e' };
	len = sizeof(c_arr) / sizeof(*c_arr) - 1;
	EXPECT_TRUE(len < MAXTHRESH);
	SortTest(c_arr, len);
}


int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
