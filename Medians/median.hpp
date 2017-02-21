#pragma once

#include "vec.hpp"
#include "algorithm.hpp"
#include <vector>

/// some algorithms to find median
template<class T>
struct median
{
	using Input = vec<T>&;

	static double of_sorted_set(const Input input)
	{
		auto size = input.size();
		std::vector<int> tmp(input.begin(), input.end());
		if (size == 0) return std::numeric_limits<double>::quiet_NaN();
		if (algorithm::is_odd(size))
		{
			return input[size / 2];
		}
		else
		{
			const auto half = size / 2;
			return 0.5 * (input[half] + input[half - 1]);
		}
	}

	//template<class SortStrategy<class Inplace>>
	//static T sort_then_return(Input input)
	//{
	//	SortStrategy sort;
	//	sort(input);
	//	return of_sorted_set(input);
	//}

	//template<class SortStrategy>
	//static T sort_then_return(Input input)
	//{
	//	SortStrategy sort;
	//	return of_sorted_set(sort(input));
	//}


};  // namespace median
