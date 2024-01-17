#include "pch.h"
#include "subwindows/subwindow_menubar.h"

#include "graphics/widget.h"

void SubWindow_MenuBar::ConstructSubWindow()
{
	Super::ConstructSubWindow();

	// todo - testing
	Widget* w1 = CreateChildWidget<Widget>();
	w1->SetLocalPosition(sf::Vector2f{ 0.f, 0.f });
	w1->SetWidgetSize(WidgetSize::MakeRelativeSize(0.5f, 0.25f));
	w1->SetBackgroundColor(sf::Color::Red);

	Widget* w2 = CreateChildWidget<Widget>();
	w2->SetLocalPosition(sf::Vector2f{ 10.f, 22.f });
	w2->SetWidgetSize(WidgetSize::MakeFillSize());
	w2->SetBackgroundColor(sf::Color::White);

	//Widget* w2 = CreateChildWidget<Widget>();
	//w2->SetLocalPosition(sf::Vector2f{ 400.f, 20.f });
	//w2->SetBackgroundColor(sf::Color::White);

	//Widget* w3 = CreateChildWidget<Widget>();
	//w3->SetLocalPosition(sf::Vector2f{ 500.f, 25.f });
	//w3->SetBackgroundColor(sf::Color::Cyan);

}

