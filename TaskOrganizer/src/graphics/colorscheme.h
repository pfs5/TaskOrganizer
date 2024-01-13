#pragma once

struct ColorScheme
{
	sf::Color Background;
	sf::Color Foreground;
	sf::Color Text;

	ColorScheme& SetBackground (const sf::Color& value) { Background = value; return *this; }
	ColorScheme& SetForeground(const sf::Color& value) { Foreground = value; return *this; }
	ColorScheme& SetText(const sf::Color& value) { Text = value; return *this; }
};