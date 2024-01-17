#pragma once

struct WidgetSize
{
	enum class EType : uint8_t
	{
		Absolute,
		Relative,
		Fill
	};

	EType Type;
	union
	{
		sf::Vector2f AbsoluteSize;	// Size in pixels
		sf::Vector2f RelativeSize;	// Size in percentages of the parent, [0, 1]
	};

	WidgetSize() :
		Type{ EType::Absolute },
		AbsoluteSize{ 100.f, 30.f }
	{

	}

	static WidgetSize MakeAbsoluteSize(float x, float y)
	{
		WidgetSize size;
		size.Type = EType::Absolute;
		size.AbsoluteSize.x = x;
		size.AbsoluteSize.y = y;
		return size;
	}

	static WidgetSize MakeRelativeSize(float x, float y)
	{
		WidgetSize size;
		size.Type = EType::Relative;
		size.RelativeSize.x = x;
		size.RelativeSize.y = y;
		return size;
	}

	static WidgetSize MakeFillSize()
	{
		WidgetSize size;
		size.Type = EType::Fill;
		return size;
	}
};