#include "pch.h"
#include "graphics/widgetbase.h"

#include "config/appconfig.h"
#include "graphics/widgetsize.h"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderTarget.hpp"

void WidgetBase::DrawWidget(const DrawParams& params)
{
	DrawWidgetDebug(params);
	DrawChildWidgets(params);
}

void WidgetBase::DrawChildWidgets(const DrawParams& params)
{
	for (WidgetBase* child : _childWidgets)
	{
		const WidgetSize childSize = child->GetWidgetSize();
		DrawParams childParams{ params };
		switch (childSize.Type)
		{
			case WidgetSize::EType::Absolute:
			{
				const sf::Vector2f childLocalPosition = child->GetWidgetLocalPosition();
				childParams.WidgetGlobalBoundsMin = params.WidgetGlobalBoundsMin + childLocalPosition;
				childParams.WidgetGlobalBoundsMax.x = childParams.WidgetGlobalBoundsMin.x + childSize.AbsoluteSize.x;
				childParams.WidgetGlobalBoundsMax.y = childParams.WidgetGlobalBoundsMin.y + childSize.AbsoluteSize.y;

				break;
			}
			case WidgetSize::EType::Relative:
			{
				const sf::Vector2f childLocalPosition = child->GetWidgetLocalPosition();
				childParams.WidgetGlobalBoundsMin = params.WidgetGlobalBoundsMin + childLocalPosition;
				childParams.WidgetGlobalBoundsMax.x = childParams.WidgetGlobalBoundsMin.x +
					(params.WidgetGlobalBoundsMax.x - params.WidgetGlobalBoundsMin.x) * childSize.RelativeSize.x;
				childParams.WidgetGlobalBoundsMax.y = childParams.WidgetGlobalBoundsMin.y +
					(params.WidgetGlobalBoundsMax.y - params.WidgetGlobalBoundsMin.y) * childSize.RelativeSize.y;

				break;
			}
			case WidgetSize::EType::Fill:
			{
				// Do nothing, the child has the same bounds as the parent(this).
				break;
			}
		}

		child->DrawWidget(childParams);
	}
}

void WidgetBase::DrawWidgetDebug(const DrawParams& params)
{
	if (AppConfigProxy::Get().ShowWidgetBounds)
	{
		static const float BORDER_THICKNESS = 1.f;
		sf::RectangleShape boundsRect { params.WidgetGlobalBoundsMax - params.WidgetGlobalBoundsMin - 2.f * sf::Vector2f{ BORDER_THICKNESS, BORDER_THICKNESS } };
		boundsRect.setPosition(params.WidgetGlobalBoundsMin + sf::Vector2f{ BORDER_THICKNESS, BORDER_THICKNESS });

		boundsRect.setOutlineColor(sf::Color::Green);
		boundsRect.setOutlineThickness(BORDER_THICKNESS);

		boundsRect.setFillColor(sf::Color::Transparent);

		params.Renderer.draw(boundsRect);
	}
}
