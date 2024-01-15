#pragma once

namespace Math
{
	template <typename T>
	T Min(T left, T right)
	{
		return std::min<T>(left, right);
	}

	template <typename T>
	T Max(T left, T right)
	{
		return std::max<T>(left, right);
	}

	template <typename T>
	T Clamp(T value, T min, T max)
	{
		return Min<T>(max, Max<T>(min, value));
	}
}