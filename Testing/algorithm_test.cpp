#include "gtest/gtest.h"
#include <vector>
#include "algorithm.hpp"

TEST(Algorithm, PartitionWorks)
{
	std::vector<int> input{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	auto pred = [](int v) -> bool { return (v & 0x1) == 1; };
	auto it = algorithm::partition(input.begin(), input.end(), pred);

	for (auto i = input.begin(); i != it; ++i)
	{
		ASSERT_TRUE(pred(*i));
	}

	for (; it != input.end(); ++it)
	{
		ASSERT_FALSE(pred(*it));
	}
}

TEST(Algorithm, QuickSelectWorks)
{
	std::vector<int> input{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	const size_t k = 3;
	const auto expected_value = input[k];
	std::random_shuffle(input.begin(), input.end());

	algorithm::quick_select_kth(input.begin(), input.end(), k);

	EXPECT_EQ(input[k], expected_value);
}

TEST(Algorithm, QuickSelectWorksWhenThereAreDuplicates)
{
	std::vector<int> input{ 0, 1, 2, 2, 2, 2, 2, 2, 8, 9 };
	std::random_shuffle(input.begin(), input.end());

	algorithm::quick_select_kth(input.begin(), input.end(), 5);

	EXPECT_EQ(input[5], 2);
}