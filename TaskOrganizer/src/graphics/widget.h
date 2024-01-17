#pragma once

#include "graphics/widgetbase.h"
#include "graphics/widgetsize.h"

class Widget : public WidgetBase
{
	using Super = WidgetBase;

public:
	WidgetSize GetWidgetSize() const final { return _size; }
	sf::Vector2f GetWidgetLocalPosition() const final { return _localPosition; };

	void DrawWidget(const DrawParams& params) override;

	void SetWidgetSize(const WidgetSize& value) { _size = value; }
	void SetLocalPosition(sf::Vector2f value) { _localPosition = value; }
	void SetBackgroundColor(const sf::Color& value) { _backgroundColor = value; }

private:
	WidgetSize _size;
	sf::Vector2f _localPosition;
	sf::Color _backgroundColor = sf::Color::Transparent;
};