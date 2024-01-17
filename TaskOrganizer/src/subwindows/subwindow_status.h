#pragma once

#include "graphics/subwindow.h"

class SubWindow_Status : public SubWindow
{
	using Super = SubWindow;
	using Super::Super;

public:
	const char* GetSubWindowName() const override { return "Status"; };
	void Draw() override;

};