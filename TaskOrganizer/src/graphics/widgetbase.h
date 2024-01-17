#pragma once

#include "config/staticconfig.h"
#include "containers/inplacevector.h"
#include "graphics/widgetmanager.h"

class WidgetBase
{

protected:
	WidgetBase* _parent = nullptr;
	InplaceVector<WidgetBase*, StaticConfig::WIDGET_MAX_CHILDREN> _children;

protected:
	template<typename WidgetClass, typename... Args>
	WidgetClass* CreateChildWidget(const Args&... args)
	{
		WidgetClass* newWidget = WidgetManagerProxy::Get().InstantiateWidget(std::forward<const Args>(args)...);
		assert(newWidget != nullptr);

		return newWidget;
	}
};