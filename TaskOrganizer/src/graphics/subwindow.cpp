#include "pch.h"
#include "graphics/subwindow.h"

#include "graphics/widgetsize.h"
#include "graphics/windowcontainer.h"

void SubWindowBase::DrawSubWindow()
{
	ensure(_parentContainer != nullptr);

	const sf::Vector2<uint32_t> parentBoundsMin = _parentContainer->GetGlobalBoundsMin();
	const sf::Vector2<uint32_t> parentBoundsMax = _parentContainer->GetGlobalBoundsMax();

	// Start the widget drawing chain by drawing the subwindow as a widget.
	WidgetBase::DrawParams params { _parentContainer->GetRenderer() };
	params.WidgetGlobalBounds.Min = sf::Vector2{ (float)parentBoundsMin.x, (float)parentBoundsMin.y };
	params.WidgetGlobalBounds.Max = sf::Vector2{ (float)parentBoundsMax.x, (float)parentBoundsMax.y };

	WidgetBase::DrawWidget(params);
}

WidgetSize SubWindowBase::GetWidgetSize() const
{
	ensure(_parentContainer != nullptr);

	const sf::Vector2<uint32_t> parentBoundsMin = _parentContainer->GetGlobalBoundsMin();
	const sf::Vector2<uint32_t> parentBoundsMax = _parentContainer->GetGlobalBoundsMax();

	const WidgetSize size = WidgetSize::MakeAbsoluteSize(
		(float)(parentBoundsMax.x - parentBoundsMin.x), 
		(float)(parentBoundsMax.y - parentBoundsMin.y)
	);

	return size;
}

sf::Vector2f SubWindowBase::GetWidgetLocalPosition() const
{
	ensure(_parentContainer != nullptr);
	const sf::Vector2<uint32_t> parentBoundsMin = _parentContainer->GetGlobalBoundsMin();
	return { (float)parentBoundsMin.x, (float)parentBoundsMin.y };
}
