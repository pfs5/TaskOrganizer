#pragma once

class SubWindow
{
public:
	virtual ~SubWindow() = default;
	virtual const char* GetSubWindowName() const = 0;
};