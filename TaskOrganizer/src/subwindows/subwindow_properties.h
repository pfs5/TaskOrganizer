#pragma once

#include "graphics/subwindow.h"

class SubWindow_Properties : public SubWindow
{
public:
	const char* GetSubWindowName() const override { return "Properties"; };

};