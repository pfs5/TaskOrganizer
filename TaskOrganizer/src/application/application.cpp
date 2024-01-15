#include "pch.h"

#include "application/application.h"
#include "graphics/window.h"
#include "config/themes.h"

#include "graphics/windowcontainer.h"
#include "subwindows/subwindow_menubar.h"
#include "subwindows/subwindow_tasktracking.h"
#include "subwindows/subwindow_properties.h"
#include "subwindows/subwindow_status.h"
#include "resource/resourcemanager.h"

void Application::Run()
{
	ResourceManager resourceManager;
	ResourceManagerProxy::Open(resourceManager);

	Window mainWindow{ Window::CreationParams{}
		.SetWidth(720)
		.SetHeight(480)
		.SetTitle("TaskOrganizer")
		.SetBackgroundColor(Themes::Dark.Background)
	};

	// Test setup for containers
	SubWindow_MenuBar* subWindow_MenuBar = mainWindow.AddSubWindow<SubWindow_MenuBar>(EWindowSplitType::Horizontal, WindowSize::MakeAbsoluteSize(30.f));
	SubWindow_TaskTracking* subWindow_TaskTracking = mainWindow.AddSubWindow<SubWindow_TaskTracking>(EWindowSplitType::Vertical, WindowSize::MakeRelativeSize(0.75f));
	SubWindow_Properties* subWindow_Properties = mainWindow.AddSubWindow<SubWindow_Properties>(EWindowSplitType::Horizontal, WindowSize::MakeRelativeSize(0.75f));
	SubWindow_Status* subWindow_Status = mainWindow.AddSubWindow<SubWindow_Status>(EWindowSplitType::Vertical, WindowSize::MakeRelativeSize(1.0f));

	while (mainWindow.IsOpen())
	{
		mainWindow.Update();
	}

	ResourceManagerProxy::Close(resourceManager);
}