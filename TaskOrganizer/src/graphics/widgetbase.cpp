#include "pch.h"
#include "graphics/widgetbase.h"

#include "config/appconfig.h"
#include "graphics/widgetsize.h"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "math/math.h"

void WidgetBase::DrawWidget(const DrawParams& params)
{
	DrawWidgetDebug(params);
	DrawChildWidgets(params);
}

void WidgetBase::DrawChildWidgets(const DrawParams& params)
{
	for (WidgetBase* child : _childWidgets)
	{
		const sf::Vector2f childLocalPosition = child->GetWidgetLocalPosition();
		const WidgetSize childSize = child->GetWidgetSize();

		DrawParams childParams { params.Renderer };
		childParams.WidgetGlobalBounds = childSize.TransformBounds(childLocalPosition, params.WidgetGlobalBounds);
		childParams.WidgetGlobalBounds += sf::Vector2f{ _padding.Left, _padding.Top };

		childParams.WidgetGlobalBounds.Min.x = Math::Max(childParams.WidgetGlobalBounds.Min.x, params.WidgetGlobalBounds.Min.x + _padding.Left);
		childParams.WidgetGlobalBounds.Min.y = Math::Max(childParams.WidgetGlobalBounds.Min.y, params.WidgetGlobalBounds.Min.y + _padding.Top);

		childParams.WidgetGlobalBounds.Max.x = Math::Min(childParams.WidgetGlobalBounds.Max.x, params.WidgetGlobalBounds.Max.x - _padding.Right);
		childParams.WidgetGlobalBounds.Max.y = Math::Min(childParams.WidgetGlobalBounds.Max.y, params.WidgetGlobalBounds.Max.y - _padding.Bottom);

		child->DrawWidget(childParams);
	}
}

void WidgetBase::DrawWidgetDebug(const DrawParams& params)
{
	if (AppConfigProxy::Get().ShowWidgetBounds)
	{
		static const float BORDER_THICKNESS = 1.f;
		sf::RectangleShape boundsRect { params.WidgetGlobalBounds.Max - params.WidgetGlobalBounds.Min - 2.f * sf::Vector2f{ BORDER_THICKNESS, BORDER_THICKNESS } };
		boundsRect.setPosition(params.WidgetGlobalBounds.Min + sf::Vector2f{ BORDER_THICKNESS, BORDER_THICKNESS });

		boundsRect.setOutlineColor(sf::Color::Green);
		boundsRect.setOutlineThickness(BORDER_THICKNESS);

		boundsRect.setFillColor(sf::Color::Transparent);

		params.Renderer.draw(boundsRect);
	}
}
