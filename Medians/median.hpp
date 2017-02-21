#pragma once

#include "vec.hpp"
#include "heap.hpp"
#include "algorithm.hpp"
#include <vector>


/// Online median finding algorithm, based on two binary heaps.
/// Running time:
/// push - O (lg n)
/// median - O (1)
/// Total time for n values - O (n * lg n)
/// Because we sometimes need to call delete-min operation to maintain balance, 
/// we cannot beat worst-case cost of lg n unless we can have constrains on input set (like only values 0..255)
/// as insert, find_min, delete_min are bounded by lg n (contradiction of lower bound of comparison sorting)
/// Using other fancier heap like Fibbonacimay provide theoretical improvement, for some inputs.
template<class T>
class heap_median
{
public:
	heap_median() : median_(std::numeric_limits<double>::quiet_NaN())
	{

	}
	
	// O(lg n)
	void push(const T& value)
	{
		add_value(value);
		maintain_heaps_balance();
		compute_current_median();
	}

	// O(1)
	double median() const 
	{
		return median_;
	}

private:
	// O(1)
	long get_balance() const 
	{
		return smallerThanMedian_.size() - biggerThanMedian_.size();
	}

	// O(1)
	void compute_current_median()
	{
		auto balance = get_balance();

		if (balance == 0)
		{
			median_ = 0.5 * (smallerThanMedian_.value() + biggerThanMedian_.value());
		}
		else if (balance < 0)
		{
			median_ = biggerThanMedian_.value();
		}
		else
		{
			median_ = smallerThanMedian_.value();
		}
	}

	// O(lg n)
	void add_value(const T& value)
	{
		if (median_ != median_)
		{
			median_ = value;
			smallerThanMedian_.push(value);
			return;
		}

		if (value < median_)
		{
			smallerThanMedian_.push(value);
		}
		else if (value > median_)
		{
			biggerThanMedian_.push(value);
		}
		else // prefer smaller heap
		{
			if (smallerThanMedian_.size() < biggerThanMedian_.size())
				smallerThanMedian_.push(value);
			else
				biggerThanMedian_.push(value);
		}
	}

	// O(lg n)
	void maintain_heaps_balance()
	{
		auto balance = get_balance();

		if (balance > 1) // left one is having two more elements
		{
			biggerThanMedian_.push(smallerThanMedian_.value());
			smallerThanMedian_.pop();
		}
		else if (balance < -1) // right one is having two more elements
		{
			smallerThanMedian_.push(biggerThanMedian_.value());
			biggerThanMedian_.pop();
		}
	}

	MaxHeap<T> smallerThanMedian_;
	MinHeap<T> biggerThanMedian_;
	double     median_;
};

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
