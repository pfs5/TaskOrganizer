#include "pch.h"
#include "graphics/widget.h"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderTarget.hpp"

void Widget::DrawWidget(const DrawParams& params)
{
	// First we draw this widget and then continue drawing the parent.

	sf::RectangleShape backgroundRect { params.WidgetGlobalBoundsMax - params.WidgetGlobalBoundsMin };
	backgroundRect.setPosition(params.WidgetGlobalBoundsMin);
	backgroundRect.setFillColor(_backgroundColor);
	params.Renderer.draw(backgroundRect);

	Super::DrawWidget(params);
}
