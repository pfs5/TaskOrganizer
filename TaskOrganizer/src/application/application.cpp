#include "pch.h"

#include "application/application.h"
#include "graphics/window.h"
#include "graphics/themes.h"

#include "graphics/windowcontainer.h"
#include "graphics/subwindow.h"

void Application::Run()
{
	Window mainWindow{ Window::CreationParams{}
		.SetWidth(720)
		.SetHeight(480)
		.SetTitle("TaskOrganizer")
		.SetBackgroundColor(Themes::Dark.Background)
	};

	// Test setup for containers
	SubWindow* s1 = mainWindow.AddSubWindow<SubWindow>(EWindowSplitType::Horizontal);

	while (mainWindow.IsOpen())
	{
		mainWindow.Update();
	}
}