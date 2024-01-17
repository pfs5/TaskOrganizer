#pragma once

#include "graphics/subwindow.h"

class SubWindow_MenuBar : public SubWindow<SubWindow_MenuBar>
{
	using Super = SubWindow<SubWindow_MenuBar>;
	using Super::Super;

public:
	void ConstructSubWindow() {}

};