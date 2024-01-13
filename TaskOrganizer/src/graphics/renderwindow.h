#pragma once

#include "SFML/Graphics/RenderWindow.hpp"

class RenderWindow : public sf::RenderWindow
{
public:
	using Super = sf::RenderWindow;
	using Super::Super;

protected:
	void onResize() final;
};