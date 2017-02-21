#include <algorithm>
#include "gtest/gtest.h"
#include "median.hpp"
#include "algorithm.hpp"

struct MedianTest : public ::testing::TestWithParam<size_t>
{
	void SetUp() override
	{
		srand(42);
	}

	static double reference_median_implementation(std::vector<int>& input)
	{
		const size_t n = input.size();
		if (n == 0) 
			return std::numeric_limits<double>::quiet_NaN();

		if (algorithm::is_odd(n))
		{
			size_t location = n / 2;
			std::nth_element(input.begin(), input.begin() + location, input.end());
			return input[location];
		}
		else
		{
			size_t location = n / 2;
			std::nth_element(input.begin(), input.begin() + location, input.end());
			auto m1 = input[location];

			location -= 1;
			std::nth_element(input.begin(), input.begin() + location, input.end());
			auto m2 = input[location];

			return 0.5 * (m1 + m2);
		}
	}

	static vec<int> random_input(size_t size)
	{
		vec<int> sut_input;
		for (size_t i = 0; i < size; ++i)
			sut_input.push_back(rand());
		return sut_input;
	}

	static vec<int> sorted_input(size_t size)
	{
		vec<int> sut_input;
		size_t s = rand();
		for (size_t i = 0; i < size; ++i)
			sut_input.push_back(s = s + rand() % 5 + 1);
		return sut_input;
	}

	static vec<int> desc_sorted_input(size_t size)
	{
		vec<int> sut_input;
		int s = size;
		for (size_t i = 0; i < size; ++i)
			sut_input.push_back(s--);
		return sut_input;
	}

	template<class InputGenerator, class MedianImplementation>
	static void perform_test(size_t size, InputGenerator generate_input, MedianImplementation mediana)
	{
		vec<int> sut_input = generate_input(size);
		std::vector<int> ref_input(sut_input.begin(), sut_input.end());

		double ref_median = reference_median_implementation(ref_input);
		double sut_medina = mediana(sut_input);

		ASSERT_EQ(IsNaN(sut_medina), IsNaN(ref_median));
		if (IsNaN(ref_median) || IsNaN(sut_medina)) return;

		ASSERT_EQ(sut_medina, ref_median);
	}

	static double IsNaN(double d) { return d != d; }
};

TEST_F(MedianTest, PassSanityChecksForReferenceImplementation)
{
	ASSERT_TRUE( IsNaN(reference_median_implementation(std::vector<int>())) );
	std::vector<int> numbers { 3,2,5,4,1 }; // median: 3
	ASSERT_EQ(3, reference_median_implementation(numbers));
	numbers.push_back(100);
	ASSERT_DOUBLE_EQ(3.5, reference_median_implementation(numbers));
}

struct MedianTesting : public ::testing::TestWithParam<size_t>
{

};

TEST_P(MedianTesting, SortedInput)
{
	const size_t test_size = GetParam();
	MedianTest::perform_test(test_size, MedianTest::sorted_input, median<int>::of_sorted_set);
}

TEST_P(MedianTesting, DescSortedInput)
{
	const size_t test_size = GetParam();
	MedianTest::perform_test(test_size, MedianTest::desc_sorted_input, median<int>::of_sorted_set);
}

/*TEST_P(MedianTesting, RandomInput)
{
	const size_t test_size = GetParam();
	MedianTest::perform_test(test_size, MedianTest::random_input, median<int>::of_sorted_set);
}*/

const size_t sizes[] = { 0, 1, 2, 3, 4, 10, 13 };
INSTANTIATE_TEST_CASE_P(ForDifferentInputSizes, MedianTesting, ::testing::ValuesIn(sizes));