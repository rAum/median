#pragma once

#include "vec.hpp"
#include "algorithm.hpp"


// Vector that is always sorted.
template<class T>
class sorted_vec
{
public:
	sorted_vec() {}

	sorted_vec(const sorted_vec<T>&) = delete; // warn if trying to copy vector
	sorted_vec(sorted_vec<T>&& other) // allow only moving
		: buff_(std::move(other.buff_))
	{
	}

	~sorted_vec() = default;

	// O(n)
	void push_back(const T& value)
	{
		buff_.push_back(value);

		if (buff_.size() == 0)
		{
			return;
		}

		for (auto it = buff_.end() - 1; it != buff_.begin(); --it)
		{
			if (*it < *(it - 1)) std::swap(*it, *(it - 1));
		}
	}

	void pop_back()	{ buff_.pop_back(); }

	size_t size()     const { return buff_.size(); }
	size_t capacity() const { return buff_.capacity(); }

	T* begin() { return &buff_[0]; }
	T* end() { return &buff_[size_]; }
	const T* begin() const { return &buff_[0]; }
	const T* end() const { return &buff_[size_]; }


	const T& operator[](size_t i) const { return buff_[i]; }
	T& operator[](size_t i) { return buff_[i]; }

private:
	vec<T> buff_;
};
