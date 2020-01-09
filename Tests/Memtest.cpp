#include "gtest/gtest.h"
#include "../algoritms/memory_allocator.h"

class MemoryAllocatorTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        allocator.init();
    }

    void TearDown() override
    {
        allocator.free(ptr);
    }

    MemoryAllocator allocator;
    void* ptr = nullptr;
};

TEST_F(MemoryAllocatorTest, Alloc0)
{
    ptr = allocator.alloc(0);
    EXPECT_EQ(ptr, nullptr);
}

TEST_F(MemoryAllocatorTest, Alloc16)
{
    ptr = allocator.alloc(16);
    EXPECT_NE(ptr, nullptr);
    EXPECT_EQ((uintptr_t)ptr % 8, 0);
}

TEST_F(MemoryAllocatorTest, Alloc32)
{
    ptr = allocator.alloc(32);
    EXPECT_NE(ptr, nullptr);
    EXPECT_EQ((uintptr_t)ptr % 8, 0);
}

TEST_F(MemoryAllocatorTest, Alloc64)
{
    ptr = allocator.alloc(64);
    EXPECT_NE(ptr, nullptr);
    EXPECT_EQ((uintptr_t)ptr % 8, 0);
}

TEST_F(MemoryAllocatorTest, Alloc128)
{
    ptr = allocator.alloc(128);
    EXPECT_NE(ptr, nullptr);
    EXPECT_EQ((uintptr_t)ptr % 8, 0);
}

TEST_F(MemoryAllocatorTest, Alloc256)
{
    ptr = allocator.alloc(256);
    EXPECT_NE(ptr, nullptr);
    EXPECT_EQ((uintptr_t)ptr % 8, 0);
}

TEST_F(MemoryAllocatorTest, Alloc512)
{
    ptr = allocator.alloc(512);
    EXPECT_NE(ptr, nullptr);
    EXPECT_EQ((uintptr_t)ptr % 8, 0);
}

TEST_F(MemoryAllocatorTest, AllocBig)
{
    ptr = allocator.alloc(1000 * sizeof(int));
    EXPECT_NE(ptr, nullptr);
    EXPECT_EQ((uintptr_t)ptr % 8, 0);
}

TEST_F(MemoryAllocatorTest, AllocTooBig)
{
    ptr = allocator.alloc(10 * 1024 * 1024 + 1);
    EXPECT_NE(ptr, nullptr);
    EXPECT_EQ((uintptr_t)ptr % 8, 0);
}
