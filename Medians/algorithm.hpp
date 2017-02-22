#pragma once

#include <iostream>

template<class It>
void print(It a, It b)
{
	for (It i = a; i != b; ++i)
		std::cout << *i << ", ";
	std::cout << std::endl;
}

namespace algorithm
{
	bool is_odd(int value);

	// Partition algorithm O(n)
	template<class It, class Pred>
	It partition(It first, It last, Pred pred)
	{
		while (first != last)
		{
			while (pred(*first)) {
				++first;
				if (first == last) return last;
			}

			do 
			{
				--last;
				if (first == last) return last;
			} while (! pred(*last));

			std::swap(*first, *last);
			++first;
		}

		return first;
	}

	// Quick select - quick-sort like algorithm to find k-th value in a set.
	// Running time: average O(n), however for some input it can fail to O(n^2) - as with quick sort
	template<class It>
	void quick_select_kth(It first, It last, int pos)
	{
		using ValueType = decltype(*first);
		const auto target_pos = first + pos;
		
		if (target_pos >= last) return;

		std::swap(*first, *target_pos); // choose pivot to be target_pos value.
		
		while (first < last)
		{
			print(first, last);
			// find place for pivot
			const ValueType& p = *first;
			auto pivot = std::partition(first, last, [&p](const ValueType& val) -> bool { return val < p; });
			std::swap(*first, *pivot); // put pivot on right place
			print(first, last);
		
			if (pivot < target_pos) // pivot is on the left of required position..
			{
				first = pivot + 1; // so we need go right, leaving pivot in right place
			}
			else if (pivot > target_pos)
			{
				last = pivot - 1; // overshooting, need to go left
			}
			else // pivot == target_pos!
			{
				break;
			}
		}
	}

	template<class It>
	It upper_bound(It first, It last, const decltype(*It)& value)
	{
		It it;
		size_t size = end - first;
		while (size > 0)
		{
			const auto step = size / 2;
			it = first + step;
			if (value < *it)
			{
				first = ++it;
				size -= step - 1;
			}
			else size = step;
		}

		return it;
	}

}  // namespace algorithm
