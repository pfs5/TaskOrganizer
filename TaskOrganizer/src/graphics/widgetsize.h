#pragma once

struct WidgetSize
{
	enum class EType : uint8_t
	{
		Absolute,
		Relative
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

	Bounds2f TransformBounds(sf::Vector2f localPos, const Bounds2f& inBounds) const
	{
		Bounds2f outBounds;

		switch (Type)
		{
			case WidgetSize::EType::Absolute:
			{
				outBounds.Min = inBounds.Min + localPos;
				outBounds.Max.x = outBounds.Min.x + AbsoluteSize.x;
				outBounds.Max.y = outBounds.Min.y + AbsoluteSize.y;

				break;
			}
			case WidgetSize::EType::Relative:
			{
				outBounds.Min = inBounds.Min + localPos;
				outBounds.Max.x = outBounds.Min.x + (inBounds.Max.x - inBounds.Min.x) * RelativeSize.x;
				outBounds.Max.y = outBounds.Min.y + (inBounds.Max.y - inBounds.Min.y) * RelativeSize.y;

				break;
			}
			default:
			{
				ensureMsg(false, "Unhandled case.");
				break;
			}
		}

		return outBounds;
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
		size.Type = EType::Relative;
		size.RelativeSize.x = 1.0f;
		size.RelativeSize.y = 1.0f;
		return size;
	}
};