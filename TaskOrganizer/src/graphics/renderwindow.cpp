#include "pch.h"
#include "graphics/renderwindow.h"

void RenderWindow::onResize()
{
	Super::onResize();

	sf::View view = getView();
	view.setSize((float)getSize().x, (float)getSize().y);
	view.setCenter(getSize().x * 0.5f, getSize().y * 0.5f);
	setView(view);
}
