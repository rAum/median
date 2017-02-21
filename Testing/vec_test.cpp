#include "gtest/gtest.h"
#include <vector>
#include "vec.hpp"

struct VecShould : public ::testing::Test
{
	using VecInt = vec<int>;
};

TEST_F(VecShould, BeDefaultConstructed)
{
	ASSERT_NO_THROW(VecInt());
}

TEST_F(VecShould, HasZeroSizeWhenDefaultConstructed)
{
	VecInt v;
	ASSERT_EQ(v.size(), 0);
}

TEST_F(VecShould, HaveSuccessfullyPutOneElement)
{
	constexpr int element = 42;
	
	VecInt v;
	v.push_back(element);
	
	ASSERT_EQ(v.size(), 1);
	EXPECT_EQ(v[0], element);
}

TEST_F(VecShould, SuccsesfullyAllocateMoreMemoryWithoutLoosingData)
{
	srand(42);

	VecInt v;

	const auto required_elements_to_reallocate = v.capacity() * 2 + 1;
	std::vector<int> reference_data;
	reference_data.reserve(required_elements_to_reallocate);
	for (size_t i = 0; i < required_elements_to_reallocate; ++i)
		reference_data.emplace_back(rand() % 300);

	for (auto i : reference_data)
	{
		v.push_back(i);
	}

	ASSERT_EQ(v.size(), reference_data.size());
	for (size_t i = 0; i < reference_data.size(); ++i)
	{
		EXPECT_EQ(reference_data[i], v[i]);
	}
}
