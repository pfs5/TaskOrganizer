#pragma once

// Currently a very basic implementation of a in-place vector. Asserts if number of elements is larger than size.
// todo - Future improvements should use dynamic memory if the in-place size is exceeded.
template <typename T, size_t InplaceSize>
class InplaceVector
{
public:
	InplaceVector() = default;

	void PushBack(const T& value)
	{
		ensureMsg(_nextSlotIndex < InplaceSize, "Inplace size exceeded.");
	}

	const T& operator[](size_t index) const { assert(IsValidIndex(index)); return _data[index]; }

	bool IsValidIndex(size_t index) const { return index < _nextSlotIndex; }

private:
	T _data [InplaceSize];
	size_t _nextSlotIndex = 0;
};