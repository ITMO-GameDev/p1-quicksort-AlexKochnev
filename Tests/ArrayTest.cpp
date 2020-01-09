#include "gtest/gtest.h"
#include "../algoritms/containers.h"


template <typename T>
void FillTestArrays(Array<T>& tested, std::vector<T>& to_cmp, int size)
{
    for (T i = 0; i < size; i++)
    {
        tested.insert(i);
        to_cmp.push_back(i);
    }
}


template <typename T>
bool ArrayContentEq(Array<T>& arr_to_check, std::vector<T> to_cmp)
{
    int i = 0;
    auto it = arr_to_check.begin();
    while (it.hasNext()) {
        it.next();
        if (it.get() != to_cmp.at(i++))
            return false;
    }
    return true;
}



template <typename T>
void PrintArrayInfo(Array<T>& arr)
{
    std::cout << "Array capacity = " << arr.capacity() << std::endl;
    std::cout << "Array size = " << arr.size() << std::endl;

    auto it = arr.begin();
    while (it.hasNext()) {
        it.next();
        std::cout << it.get() << ' ';
    };
    std::cout << std::endl;
    std::cout << "-------------------------\n";
}



template <typename T>
Array<T> generatearray_via_move(std::vector<T>& valuescontainer)
{
    Array<int> a(0);
    for (int i = 0; i < valuescontainer.size(); i++)
        a.insert(valuescontainer.at(i));
    Array<int> b(std::move(a));
    return b;
}


template <typename T>
Array<T> generatearray_via_copy(std::vector<T>& valuescontainer)
{
    Array<int> a(10);
    for (int i = 0; i < valuescontainer.size(); i++)
        a.insert(valuescontainer.at(i));
    Array<int> b = a;
    return b;
}


TEST(ArrayTest, NullCapacityCtor)
{
    Array<int> a(0);
    EXPECT_EQ(a.returnCapacity(), 0);
}


TEST(ArrayTest, CapacityGetter)
{
    int size = 10;
    Array<int> a(size);

    EXPECT_EQ(a.returnCapacity(), size);
}


TEST(ArrayTest, SizeGetter)
{
    Array<int> a(0);
    std::vector<int> a1;
    int size = 10;

    EXPECT_EQ(a.returnSize(), 0);
    FillTestArrays(a, a1, size);
    EXPECT_EQ(a.returnSize(), size);
}


TEST(ArrayTest, Insertion)
{
    Array<int> a(8);
    std::vector<int> a1;
    int size = 6;

    EXPECT_EQ(a.returnCapacity(), 8);
    FillTestArrays(a, a1, size);
    EXPECT_EQ(a.returnCapacity(), 8);
    EXPECT_EQ(a.returnSize(), size);
    EXPECT_TRUE(ArrayContentEq(a, a1));
}


TEST(ArrayTest, InsertionWithExpansion)
{
    Array<int> a(0);
    std::vector<int> a1;
    int size = 6;

    FillTestArrays(a, a1, size);
    EXPECT_EQ(a.returnSize(), size);
    EXPECT_TRUE(ArrayContentEq(a, a1));
}


TEST(ArrayTest, InsertionWithMultipleExpansion)
{
    Array<int> a(0);
    std::vector<int> a1;
    int size = 1000;

    FillTestArrays(a, a1, size);
    EXPECT_EQ(a.returnSize(), size);
    EXPECT_TRUE(ArrayContentEq(a, a1));
}


TEST(ArrayTest, IndexedInsertion)
{
    Array<int> a(0);
    std::vector<int> a1{ 1, 2, 3, 4, 5, 6 };
    a.insert(1);
    a.insert(3);
    a.insert(6);
    a.insert(1, 2);
    a.insert(3, 5);
    a.insert(3, 4);

    EXPECT_EQ(a.returnSize(), 6);
    EXPECT_TRUE(ArrayContentEq(a, a1));
}


TEST(ArrayTest, TestSimpleMoveCtor)
{
    Array<int> a(0);
    std::vector<int> a1{ 100, 200, 300, 400, 500, 600 };

    a = generatearray_via_move(a1);
    EXPECT_TRUE(ArrayContentEq(a, a1));
    EXPECT_EQ(a.returnSize(), 6);
}


TEST(ArrayTest, TestCopyCtor)
{
    Array<int> a(0);
    std::vector<int> a1{ 700, 500, 200, 333, 123, 444 };

    a = generatearray_via_copy(a1);
    EXPECT_TRUE(ArrayContentEq(a, a1));
    EXPECT_EQ(a.returnSize(), 6);
}


TEST(ArrayTest, Templates)
{
    Array<char> a(0);
    std::vector<char> a1;
    int size = 120;

    FillTestArrays(a, a1, size);
    EXPECT_EQ(a.returnSize(), size);
}
