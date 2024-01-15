#pragma once

#include "graphics/subwindow.h"

class SubWindow_Status : public SubWindow
{
public:
	const char* GetSubWindowName() const override { return "Status"; };

};