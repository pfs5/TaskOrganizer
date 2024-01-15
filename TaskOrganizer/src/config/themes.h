#pragma once

#include "graphics/colorscheme.h"

namespace Themes
{
	static inline const ColorScheme Dark { ColorScheme{}
		.SetBackground(sf::Color{0x444444ff})
		.SetForeground(sf::Color{0xAAAAAAff})
		.SetText(sf::Color{0x211E29ff})
	};
}