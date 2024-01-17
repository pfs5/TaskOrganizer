#include "pch.h"

#include "config/appconfig.h"
#include "application/application.h"
#include "config/staticconfig.h"
#include "config/themes.h"
#include "graphics/window.h"
#include "graphics/windowcontainer.h"
#include "resource/resourcemanager.h"
#include "subwindows/subwindow_menubar.h"
#include "subwindows/subwindow_properties.h"
#include "subwindows/subwindow_status.h"
#include "subwindows/subwindow_tasktracking.h"
#include "graphics/widgetmanager.h"

void Application::Run()
{
	ResourceManager resourceManager;
	AppConfig appConfig;
	WidgetManager widgetManager;

	ResourceManagerProxy::Open(resourceManager);
	AppConfigProxy::Open(appConfig);
	WidgetManagerProxy::Open(widgetManager);

	Window mainWindow{ Window::CreationParams{}
		.SetWidth(720)
		.SetHeight(480)
		.SetTitle("TaskOrganizer")
		.SetBackgroundColor(Themes::Dark.Background)
	};

	// Test setup for containers
	SubWindow_MenuBar* subWindow_MenuBar = mainWindow.AddSubWindow<SubWindow_MenuBar>(EWindowSplitType::Horizontal, WindowSize::MakeAbsoluteSize(StaticConfig::SUBWINDOW_MENUBAR_HEIGHT));
	SubWindow_TaskTracking* subWindow_TaskTracking = mainWindow.AddSubWindow<SubWindow_TaskTracking>(EWindowSplitType::Vertical, WindowSize::MakeRelativeSize(StaticConfig::SUBWINDOW_TASKTRACKER_RELATIVESIZE));
	SubWindow_Properties* subWindow_Properties = mainWindow.AddSubWindow<SubWindow_Properties>(EWindowSplitType::Horizontal, WindowSize::MakeRelativeSize(StaticConfig::SUBWINDOW_PROPERTIES_RELATIVESIZE));
	SubWindow_Status* subWindow_Status = mainWindow.AddSubWindow<SubWindow_Status>(EWindowSplitType::Vertical, WindowSize::MakeRelativeSize(1.0f));

	// Testing config
#if defined(USE_DEBUG)
	appConfig.PrintConfig();
#endif //defined(USE_DEBUG)

	while (mainWindow.IsOpen())
	{
		mainWindow.Update();
	}

	WidgetManagerProxy::Close(widgetManager);
	AppConfigProxy::Close(appConfig);
	ResourceManagerProxy::Close(resourceManager);
}