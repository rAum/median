#pragma once

#include <memory>

/// Very minimal implementation of a vector 
template<class T>
class vec
{
	static constexpr size_t DefaultCapacity = 128;
	static constexpr double GrowthRatio = 1.8;
public:
	vec()
		: capacity_(DefaultCapacity), size_(0), buff_(std::make_unique<T[]>(DefaultCapacity))
	{

	}

	vec(const vec<T>&) = delete; // warn if trying to copy vector
	vec(vec<T>&& other) // allow only moving
		: capacity_(other.capacity_), size_(other.size_), buff_(std::move(other.buff_))
	{
		other.capacity_ = other.size_ = 0;
	}

	~vec() = default;

	void push_back(const T& value)
	{
		const auto new_size = size_ + 1;
		
		if (new_size > capacity_)
			increase_capacity();
		
		buff_[size_] = value;
		size_ = new_size;
	}

	size_t size()     const { return size_; }
	size_t capacity() const { return capacity_; }

	T* begin() { return &buff_[0]; }
	T* end() { return &buff_[size_]; }
	const T* begin() const { return &buff_[0]; }
	const T* end() const { return &buff_[size_]; }


	const T& operator[](size_t i) const { return buff_[i]; }
	T& operator[](size_t i) { return buff_[i]; }
private:
	void increase_capacity()
	{
		const auto new_capacity = static_cast<size_t>(capacity_ * GrowthRatio);
		std::unique_ptr<T[]> new_buff(std::make_unique<T[]>(new_capacity));
		unsafe_copy_all_to(new_buff.get());
		buff_ = std::move(new_buff);
		capacity_ = new_capacity;
	}

	void unsafe_copy_all_to(T* target)
	{
		T* src = &buff_[0];
		const T* end = &buff_[size_];
		while (src != end)
		{
			*target = *src;
			++target;
			++src;
		}
	}

	size_t               capacity_;
	size_t               size_;
	std::unique_ptr<T[]> buff_;
};
