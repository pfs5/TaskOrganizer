#pragma once

class WindowContainer;

class SubWindow
{
public:
	SubWindow(WindowContainer& parentContainer) :
		_parentContainer{ &parentContainer }
	{

	}

	virtual ~SubWindow() = default;
	
	virtual const char* GetSubWindowName() const = 0;
	virtual void Draw() {}

protected:
	WindowContainer* _parentContainer = nullptr;
};