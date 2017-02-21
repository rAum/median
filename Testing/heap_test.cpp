#include "gtest/gtest.h"
#include <vector>
#include <algorithm>
#include "heap.hpp"

struct HeapShould : public ::testing::Test
{
	using HeapMin = heap<int, heap_order<int>::min>;
	using HeapMax = heap<int, heap_order<int>::max>;

	void SetUp() override
	{
		numbers = { 400, 13, 100, 220, 1, 544, 93 };
	}

	template<class T>
	void insert_values_to(T& h)
	{
		for (auto value : numbers)
		{
			h.push(value);
		}
	}

	std::vector<int> numbers;
};

TEST_F(HeapShould, HaveValidMinValue)
{
	HeapMin h;
	insert_values_to(h);
	EXPECT_EQ(h.value(), 1);
}

TEST_F(HeapShould, HaveValidNextMinValue)
{
	HeapMin h;
	insert_values_to(h);
	h.pop();
	EXPECT_EQ(h.value(), 13);
}

TEST_F(HeapShould, BeAbleToSortValues)
{
	HeapMin h;
	insert_values_to(h);
	std::sort(numbers.begin(), numbers.end());
	for (auto value : numbers)
	{
		ASSERT_EQ(h.value(), value);
		h.pop();
	}
}

TEST_F(HeapShould, ReturnMaxValue)
{
	HeapMax h;
	insert_values_to(h);
	EXPECT_EQ(h.value(), 544);
}
