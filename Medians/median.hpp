#pragma once

#include "vec.hpp"
#include "heap.hpp"
#include "sorted_vec.hpp"
#include "algorithm.hpp"


// Online median finding algorithm, based on two binary heaps.
// Running time:
// push - O (lg n)
// median - O (1)
// Total time for n values - O (n * lg n)
// Because we sometimes need to call delete-min operation to maintain balance, 
// we cannot beat worst-case cost of lg n unless we can have constrains on input set (like only values 0..255)
// as insert, find_min, delete_min are bounded by lg n (contradiction of lower bound of comparison sorting)
// Using other fancier heap like Fibbonaci may provide theoretical improvement, for some inputs.
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

////////////////////////////////////////////////////////////

// Simple algorithm that works by having sorted set.
// For simplicity, it's based on vector with insert sort implemented.
// This makes it O(n^2) for n input.
// Changing sorted_vec to BST (AVL, Red-Black etc) could improve time
// as we could insert data in lg n instead of n.
template<class T>
struct sort_based_median
{
public:
	// O (n)
	void push(const T& value)
	{
		sortedInput_.push_back(value);
	}

	// O (1)
	double median() const
	{
		auto size = sortedInput_.size();

		if (size == 0) return std::numeric_limits<double>::quiet_NaN();
		const auto half = size / 2;
		if (algorithm::is_odd(size))
		{
			return sortedInput_[half];
		}
		else
		{
			return 0.5 * (sortedInput_[half] + sortedInput_[half - 1]);
		}
	}
private:
	sorted_vec<T> sortedInput_;
};  // struct sort_based_median


// This is median finder that does not sort input data,
// it's using quick select algorithm instead.
// This makes finding median in O(n) average time but sometimes 
// it may fall to run in O(n^2).
template<class T>
struct qselect_median
{
public:

	// Amortized O(1)
	void push(const T& value)
	{
		input_.push_back(value);
	}

	// Average: O(n), worst case: O(n^2).
	double median()
	{
		auto size = input_.size();

		if (size == 0) return std::numeric_limits<double>::quiet_NaN();
		if (size == 1) return input_[0];
		
		const auto half = size / 2;
		if (algorithm::is_odd(size))
		{
			algorithm::quick_select_kth(input_.begin(), input_.end(), half);
			return input_[half];
		}
		else
		{
			algorithm::quick_select_kth(input_.begin(), input_.end(), half);
			algorithm::quick_select_kth(input_.begin(), input_.end(), half - 1);
			return 0.5 * (input_[half] + input_[half - 1]);
		}
	}
private:
	vec<T> input_;
};
