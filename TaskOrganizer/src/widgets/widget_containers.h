#pragma once
#include "graphics/widget.h"

enum class EWidgetStackingType : uint8_t
{
	Vertical,
	Horizontal
};

template <EWidgetStackingType stackingType>
class Widget_StackingContainer : public Widget
{
public:
	void SetSpacing(float value) { _spacing = value; }

private:
	float _spacing = 0.f;

private:
	void DrawChildWidgets(const DrawParams& params) final
	{
		sf::Vector2f offset { _padding.Left, _padding.Top }; // children are stacking after the previous, depending on the stacking type.
		for (WidgetBase* child : _childWidgets)
		{
			const sf::Vector2f childLocalPosition = child->GetWidgetLocalPosition();
			const WidgetSize childSize = child->GetWidgetSize();

			DrawParams childParams{ params.Renderer };
			childParams.WidgetGlobalBounds = childSize.TransformBounds(childLocalPosition, params.WidgetGlobalBounds);
			childParams.WidgetGlobalBounds += offset;

			child->DrawWidget(childParams);

			if (stackingType == EWidgetStackingType::Horizontal)
			{
				offset.x += childParams.WidgetGlobalBounds.GetSizeX() + _spacing;
			}
			else if (stackingType == EWidgetStackingType::Vertical)
			{
				offset.y += childParams.WidgetGlobalBounds.GetSizeY() + _spacing;
			}
		}
	}
};

using Widget_Rows = Widget_StackingContainer<EWidgetStackingType::Vertical>;
using Widget_Columns = Widget_StackingContainer<EWidgetStackingType::Horizontal>;