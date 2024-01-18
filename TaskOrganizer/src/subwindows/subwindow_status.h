#pragma once

#include "graphics/subwindow.h"

class SubWindow_Status : public SubWindow<SubWindow_Status>
{
	using Super = SubWindow<SubWindow_Status>;
	using Super::Super;

public:
	void ConstructSubWindow() override;
};