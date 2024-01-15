#pragma once

#include "graphics/subwindow.h"

class SubWindow_MenuBar : public SubWindow
{
public:
	const char* GetSubWindowName() const override { return "MenuBar"; };

};