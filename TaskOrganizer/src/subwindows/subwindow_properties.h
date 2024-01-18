#pragma once

#include "graphics/subwindow.h"

class SubWindow_Properties : public SubWindow<SubWindow_Properties>
{
	using Super = SubWindow<SubWindow_Properties>;
	using Super::Super;

public:
	void ConstructSubWindow() override;
};