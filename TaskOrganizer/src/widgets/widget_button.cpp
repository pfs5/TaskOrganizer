#include "pch.h"
#include "widgets/widget_button.h"

#include "resource/resourcemanager.h"
#include "config/staticconfig.h"
#include "SFML/Graphics/Text.hpp"
#include "SFML/Graphics/RenderTarget.hpp"

void Widget_Button::DrawWidget(const DrawParams& params)
{
	Super::DrawWidget(params);

	if (sf::Font* font = ResourceManagerProxy::Get().GetFont(StaticConfig::DEFAULT_FONT))
	{
		sf::Text text;

		text.setString(_text);
		text.setFont(*font);
		text.setCharacterSize(_textSize);
		text.setFillColor(_textColor);

		const sf::Vector2f textSize{(float)text.getLocalBounds().width, (float)text.getCharacterSize()};
		const sf::Vector2f textPosition{
			params.WidgetGlobalBounds.GetSizeX() * 0.5f - textSize.x * 0.5f,
			params.WidgetGlobalBounds.GetSizeY() * 0.5f - textSize.y * 0.5f
		};
		text.setPosition(params.WidgetGlobalBounds.Min + textPosition);

		params.Renderer.draw(text);
	}
}
