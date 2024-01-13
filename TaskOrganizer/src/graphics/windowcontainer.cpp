#include "pch.h"

#include "graphics/windowcontainer.h"
#include "graphics/window.h"

// todo - testin
#include "util/random.h"
#include "SFML/Graphics/RectangleShape.hpp"

WindowContainer::WindowContainer(Window& window) :
	_parentWindow{ &window },
	_backgroundColor{ Random::RandomInt<sf::Uint8>(0, 255u), Random::RandomInt<sf::Uint8>(0, 255u) , Random::RandomInt<sf::Uint8>(0, 255u) }	// todo - testing
{

}

sf::Vector2<uint32_t> WindowContainer::GetGlobalBoundsMin() const
{
	if (_parent == nullptr)
	{
		// root container is always full screen
		return sf::Vector2<uint32_t>{0, 0};
	}

	const sf::Vector2<uint32_t> parentMin = _parent->GetGlobalBoundsMin();
	const sf::Vector2<uint32_t> parentMax = _parent->GetGlobalBoundsMax();

	return sf::Vector2<uint32_t>{
		(uint32_t)(parentMin.x + (parentMax.x - parentMin.x) * _normalizedRelativeBoundsMin.x),
		(uint32_t)(parentMin.y + (parentMax.y - parentMin.y) * _normalizedRelativeBoundsMin.y)
	};
}

sf::Vector2<uint32_t> WindowContainer::GetGlobalBoundsMax() const
{
	if (_parent == nullptr)
	{
		assert(_parentWindow != nullptr);

		// root container is always full screen
		return sf::Vector2<uint32_t>{_parentWindow->GetWidth(), _parentWindow->GetHeigth()};
	}

	const sf::Vector2<uint32_t> parentMin = _parent->GetGlobalBoundsMin();
	const sf::Vector2<uint32_t> parentMax = _parent->GetGlobalBoundsMax();

	return sf::Vector2<uint32_t>{
		(uint32_t)(parentMin.x + (parentMax.x - parentMin.x) * _normalizedRelativeBoundsMax.x),
		(uint32_t)(parentMin.y + (parentMax.y - parentMin.y) * _normalizedRelativeBoundsMax.y)
	};
}

void WindowContainer::Draw()
{
	const sf::Vector2<uint32_t> globalMin = GetGlobalBoundsMin();
	const sf::Vector2<uint32_t> globalMax = GetGlobalBoundsMax();

	// Draw background
	sf::Color color = _parentWindow->GetActiveContainer() == this ?
		sf::Color{sf::Uint8(_backgroundColor.r - 20), sf::Uint8(_backgroundColor.g - 20) , sf::Uint8(_backgroundColor.b - 20) } :
		_backgroundColor;

	sf::RectangleShape rect{ sf::Vector2f{(float)(globalMax.x - globalMin.x), (float)(globalMax.y - globalMin.y)} };
	rect.setPosition((float)globalMin.x, (float)globalMin.y);
	rect.setFillColor(color);
	_parentWindow->Draw(rect);

}
