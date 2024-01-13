#pragma once

// Utility library for non-safe random numbers.
namespace Random
{
	float RandomFloatNormalized()
	{
		std::random_device rd;
		std::mt19937 rengine(rd());
		std::uniform_real_distribution<float> dist(0.f, 1.f);
		return dist(rengine);
	}

	// [min, max] , undefined for min > max
	float RandomFloat(float min, float max)
	{
		assert(max >= min);

		return RandomFloatNormalized() * (max - min) + min;
	}

	template <typename T>
	T RandomInt(T min, T max)
	{
		static_assert(std::is_integral_v<T>);
		return (T)RandomFloat(float(min), float(max));
	}
}