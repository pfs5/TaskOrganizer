#include "pch.h"
#include "subwindows/subwindow_menubar.h"

#include "widgets/widget_containers.h"
#include "widgets/widget_button.h"

void SubWindow_MenuBar::ConstructSubWindow()
{
	Super::ConstructSubWindow();

	Widget_Columns* columns = CreateChildWidget<Widget_Columns>();
	columns->SetLocalPosition(sf::Vector2f{ 0.f, 0.f });
	columns->SetWidgetSize(WidgetSize::MakeFillSize());
	columns->SetSpacing(10.f);
	columns->SetPadding(PaddingF{}.SetLeft(10.f).SetTop(10.f));
	columns->SetBackgroundColor(StaticConfig::COLOR_SCHEME.WindowBackground);

	{
		Widget_Button* w = columns->CreateChildWidget<Widget_Button>("File");
		w->SetLocalPosition(sf::Vector2f{ 0.f, 0.f });
		w->SetWidgetSize(WidgetSize::MakeAbsoluteSize(65.f, 20.f));
		w->SetBackgroundColor(StaticConfig::COLOR_SCHEME.Button);
		w->SetTextColor(StaticConfig::COLOR_SCHEME.ButtonText);
	}

	{
		Widget_Button* w = columns->CreateChildWidget<Widget_Button>("Windows");
		w->SetLocalPosition(sf::Vector2f{ 0.f, 0.f });
		w->SetWidgetSize(WidgetSize::MakeAbsoluteSize(65.f, 20.f));
		w->SetBackgroundColor(StaticConfig::COLOR_SCHEME.Button);
		w->SetTextColor(StaticConfig::COLOR_SCHEME.ButtonText);
	}

	{
		Widget_Button* w = columns->CreateChildWidget<Widget_Button>("Exit");
		w->SetLocalPosition(sf::Vector2f{ 0.f, 0.f });
		w->SetWidgetSize(WidgetSize::MakeAbsoluteSize(65.f, 20.f));
		w->SetBackgroundColor(StaticConfig::COLOR_SCHEME.Button);
		w->SetTextColor(StaticConfig::COLOR_SCHEME.ButtonText);
	}
}

