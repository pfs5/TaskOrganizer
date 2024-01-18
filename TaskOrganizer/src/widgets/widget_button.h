#pragma once

#include "graphics/widget.h"

class Widget_Button : public Widget
{
	using Super = Widget;

public:
	Widget_Button(const char* text = "") :
		_text{ text }
	{

	}

	void DrawWidget(const DrawParams& params) override;
	void SetTextSize(uint32_t value) { _textSize = value; }
	void SetTextColor(sf::Color value) { _textColor = value; }

private:
	std::string _text;
	uint32_t _textSize = 12;
	sf::Color _textColor = sf::Color::Black;
};