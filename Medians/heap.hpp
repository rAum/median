#pragma once

#include "vec.hpp"

template<class T>
struct heap_order
{
	struct min { bool operator()(const T& a, const T&b) { return a < b; } };
	struct max { bool operator()(const T& a, const T&b) { return a > b; } };
};  // struct heap_order

// Minimal, vector based, binary heap implementation.
// push: O (lg n)
// pop: O (lg n)
// value: O (1)
// size: O (1)
template<class T, class Order = heap_order<T>::min>
class heap
{
public:
	heap()
	{
		heap_.push_back(T()); // skip first element
	}

	void push(const T& value)
	{
		auto p = size();
		heap_.push_back(value);
		swim(p);
	}

	const T& value() const { return heap_[1]; }

	void pop() 
	{
		std::swap(heap_[1], heap_[size() - 1]);
		heap_.pop_back();
		sink(1);
	}

	size_t size() const { return heap_.size(); }
private:
	size_t parent(size_t i) const
	{
		return i / 2;
	}

	void sink(size_t i)
	{
		size_t kid = 2 * i;
		while (kid < size())
		{
			if (kid < size() -1 && order_(heap_[kid+1], heap_[kid])) ++kid;
			if (order_(heap_[i], heap_[kid])) break;
			std::swap(heap_[i], heap_[kid]);
			i = kid;
			kid = 2 * i;
		}
	}

	void swim(size_t i)
	{
		size_t p = parent(i);
		while (i > 1 && !order_(heap_[p], heap_[i]))
		{
			std::swap(heap_[p], heap_[i]);
			i = p;
			p = parent(i);
		}
	}

	vec<T> heap_;
	Order  order_;
};  // classs heap

template<class T>
using MinHeap = heap<T, typename heap_order<T>::min>;

template<class T>
using MaxHeap = heap<T, typename heap_order<T>::max>;
