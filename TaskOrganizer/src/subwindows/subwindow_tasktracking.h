#pragma once

#include "graphics/subwindow.h"

class SubWindow_TaskTracking : public SubWindow
{
	using Super = SubWindow;
	using Super::Super;

public:
	const char* GetSubWindowName() const override { return "TaskTracking"; };

};