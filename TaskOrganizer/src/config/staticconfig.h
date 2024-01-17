#pragma once

#include "config/themes.h"

// Constants defined at compile time used to setup the app.
namespace StaticConfig
{
	// Layout setup
	static constexpr uint32_t SUBWINDOW_MENUBAR_HEIGHT = 40;
	static constexpr float SUBWINDOW_TASKTRACKER_RELATIVESIZE = 0.75f;
	static constexpr float SUBWINDOW_PROPERTIES_RELATIVESIZE = 0.75f;

	// UI
	static constexpr uint32_t BUTTON_HEIGHT = 20;

	// Paths
	static constexpr const char* PATH_CONFIGFILE = "appconfig.json";
}