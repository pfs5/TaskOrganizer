#include "pch.h"
#include "subwindows/subwindow_properties.h"

#include "graphics/widget.h"

void SubWindow_Properties::ConstructSubWindow()
{
	Super::ConstructSubWindow();

	Widget* base = CreateChildWidget<Widget>();
	base->SetLocalPosition(sf::Vector2f{ 0.f, 0.f });
	base->SetWidgetSize(WidgetSize::MakeFillSize());
	base->SetBackgroundColor(StaticConfig::COLOR_SCHEME.WindowBackground);
	base->SetPadding(PaddingF{}
		.SetLeft(StaticConfig::SUBWINDOW_PADDING)
		.SetRight(StaticConfig::SUBWINDOW_PADDING)
	);

	Widget* content = base->CreateChildWidget<Widget>();
	content->SetLocalPosition(sf::Vector2f{ 0.f, 0.f });
	content->SetWidgetSize(WidgetSize::MakeFillSize());
	content->SetBackgroundColor(StaticConfig::COLOR_SCHEME.SectionBackground);
}
