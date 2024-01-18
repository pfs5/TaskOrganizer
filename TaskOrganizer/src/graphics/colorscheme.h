#pragma once

struct ColorScheme
{
	sf::Color Background;
	sf::Color Foreground;
	sf::Color Text;

	sf::Color Button;
	sf::Color ButtonText;

	sf::Color WindowBackground;
	sf::Color SectionBackground;

	ColorScheme& SetBackground (const sf::Color& value) { Background = value; return *this; }
	ColorScheme& SetForeground(const sf::Color& value) { Foreground = value; return *this; }
	ColorScheme& SetText(const sf::Color& value) { Text = value; return *this; }
	ColorScheme& SetButton(const sf::Color& value) { Button = value; return *this; }
	ColorScheme& SetButtonText(const sf::Color& value) { ButtonText = value; return *this; }
	ColorScheme& SetWindowBackground(const sf::Color& value) { WindowBackground = value; return *this; }
	ColorScheme& SetSectionBackground(const sf::Color& value) { SectionBackground = value; return *this; }
};