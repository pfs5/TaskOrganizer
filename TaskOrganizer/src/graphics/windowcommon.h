#pragma once
#include "math/math.h"

enum class EWindowSplitType : uint8_t
{
	Horizontal,
	Vertical
};

struct WindowSize
{
	enum class EType : uint8_t
	{
		Absolute,
		Relative
	};

	EType Type;

	// Use matching data depending on type.
	union
	{
		float AbsoluteSize;
		float RelativeSize;
	};

	static WindowSize MakeAbsoluteSize(float value)
	{
		WindowSize size;
		size.Type = EType::Absolute;
		size.AbsoluteSize = value;
		return size;
	}

	static WindowSize MakeRelativeSize(float value)
	{
		WindowSize size;
		size.Type = EType::Relative;
		size.RelativeSize = value;
		return size;
	}

	// Calculate the size relative to the input size
	float CalculateRelativeSize(float inSize) const
	{
		if (Type == EType::Absolute)
		{
			return Math::Min(AbsoluteSize, inSize);
		}

		if (Type == EType::Relative)
		{
			return inSize * RelativeSize;
		}

		assert(false);
		return 0.f;
	}
};