#pragma once

#include "graphics/widgetbase.h"
#include "util/typehelper.h"

class WindowContainer;

class SubWindowBase : public WidgetBase
{
public:
	SubWindowBase(WindowContainer& parentContainer) :
		_parentContainer{ &parentContainer }
	{

	}

	virtual ~SubWindowBase() = default;
	
	virtual const std::string& GetSubWindowName() const = 0;

	virtual void ConstructSubWindow() {}
	virtual void Draw() {}

protected:
	WindowContainer* _parentContainer = nullptr;

};

template <typename CRTP>
class SubWindow : public SubWindowBase
{
	using SubWindowBase::SubWindowBase;

public:
	const std::string& GetSubWindowName() const final
	{
		return _name;
	}

private:
	static const std::string _name;
};

template <typename CRTP>
const std::string SubWindow<CRTP>::_name = TypeHelper<CRTP>::GetName();
