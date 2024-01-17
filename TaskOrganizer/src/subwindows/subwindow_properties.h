#pragma once

#include "graphics/subwindow.h"

class SubWindow_Properties : public SubWindow
{
	using Super = SubWindow;
	using Super::Super;

public:
	const char* GetSubWindowName() const override { return "Properties"; };

};