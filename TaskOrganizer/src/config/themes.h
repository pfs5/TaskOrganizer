#pragma once

#include "graphics/colorscheme.h"

namespace Themes
{
	static inline const ColorScheme Dark { ColorScheme{}
		.SetBackground(sf::Color{0x444444ff})
		.SetForeground(sf::Color{0xAAAAAAff})
		.SetText(sf::Color{0x211E29ff})
		.SetButton(sf::Color{0xB7B7B7ff})
		.SetButtonText(sf::Color{0x211E29ff})
		.SetWindowBackground(sf::Color{0x707070ff})
		.SetSectionBackground(sf::Color{0x444444ff})
	};
}