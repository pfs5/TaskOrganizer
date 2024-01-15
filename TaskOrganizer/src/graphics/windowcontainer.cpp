#include "pch.h"

#include "graphics/windowcontainer.h"
#include "graphics/window.h"

#include "SFML/Graphics/RectangleShape.hpp"
#include "config/themes.h"
#include "SFML/Graphics/Text.hpp"
#include "subwindow.h"
#include "resource/resourcemanager.h"

WindowContainer::WindowContainer(Window& window) :
	_parentWindow{ &window }
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

	if (_parent->_childLeft == this)
	{
		return parentMin;
	}

	// Container is right/bottom child.
	const WindowSize& sizeLeft = _parent->_childLeft->_size;

	if (_parent->_splitType == EWindowSplitType::Horizontal)
	{
		const uint32_t x = parentMin.x + (uint32_t)sizeLeft.CalculateRelativeSize((float)(parentMax.x - parentMin.x));
		const uint32_t y = parentMin.y;
		return sf::Vector2<uint32_t>{x, y};
	}
	else if (_parent->_splitType == EWindowSplitType::Vertical)
	{
		const uint32_t x = parentMin.x;
		const uint32_t y = parentMin.y + (uint32_t)sizeLeft.CalculateRelativeSize((float)(parentMax.y - parentMin.y));
		return sf::Vector2<uint32_t>{x, y};
	}

	assert(false);
	return sf::Vector2<uint32_t>{};
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

	if (_parent->_childRight == this)
	{
		return parentMax;
	}

	// Container is left/top child.
	const WindowSize& sizeLeft = _parent->_childLeft->_size;

	if (_parent->_splitType == EWindowSplitType::Horizontal)
	{
		const uint32_t x = parentMin.x + (uint32_t)sizeLeft.CalculateRelativeSize((float)(parentMax.x - parentMin.x));
		const uint32_t y = 0;
		return sf::Vector2<uint32_t>{x, y};
	}
	else if (_parent->_splitType == EWindowSplitType::Vertical)
	{
		const uint32_t x = 0;
		const uint32_t y = parentMin.y + (uint32_t)sizeLeft.CalculateRelativeSize((float)(parentMax.y - parentMin.y));
		return sf::Vector2<uint32_t>{x, y};
	}

	assert(false);
	return sf::Vector2<uint32_t>{};

}

void WindowContainer::Draw()
{
	if (!IsLeaf())
	{
		return;
	}

	const sf::Vector2<uint32_t> globalMin = GetGlobalBoundsMin();
	const sf::Vector2<uint32_t> globalMax = GetGlobalBoundsMax();

	const ColorScheme& theme = Themes::Dark;
	const sf::Color& backgroundColor = theme.Background;
	const sf::Color& foregroundColor = theme.Foreground;
	const sf::Color& textColor = theme.Text;

	// Draw background
	sf::RectangleShape rectBackground{ sf::Vector2f{(float)(globalMax.x - globalMin.x), (float)(globalMax.y - globalMin.y)} };
	rectBackground.setPosition((float)globalMin.x, (float)globalMin.y);
	rectBackground.setFillColor(backgroundColor);
	_parentWindow->Draw(rectBackground);

	// Draw border
	static constexpr float BORDER_THICKNESS = 2.f;
	sf::RectangleShape rectBorder{ 
		sf::Vector2f{(float)(globalMax.x - globalMin.x - BORDER_THICKNESS * 0.5f), 
		(float)(globalMax.y - globalMin.y - BORDER_THICKNESS * 0.5f)} 
	};
	rectBorder.setPosition((float)globalMin.x, (float)globalMin.y);
	rectBorder.setOutlineColor(foregroundColor);
	rectBorder.setFillColor(sf::Color::Transparent);
	rectBorder.setOutlineThickness(BORDER_THICKNESS);
	_parentWindow->Draw(rectBorder);

	// Draw name
	static constexpr float NAME_TEXT_PADDING = 5.f;
	if (sf::Font* font = ResourceManagerProxy::Get().GetFont("OpenSansMedium"))
	{
		sf::Text text(_subWindow != nullptr ? _subWindow->GetSubWindowName() : "", *font, 12);
		text.setPosition(globalMin.x + NAME_TEXT_PADDING, globalMin.y + NAME_TEXT_PADDING);
		_parentWindow->Draw(text);
	}
}
