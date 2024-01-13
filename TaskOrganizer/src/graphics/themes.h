#pragma once

#include "graphics/colorscheme.h"

namespace Themes
{
	static inline const ColorScheme Dark { ColorScheme{}
		.SetBackground(sf::Color{30, 30, 30})
		.SetForeground(sf::Color{37, 37, 38})
		.SetText(sf::Color{255, 255, 255})
	};
}