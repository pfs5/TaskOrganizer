#pragma once

#include "util/proxy.h"

class WidgetManager
{
public:
	// todo - this should use a pool eventually.
	template <typename WidgetClass, typename... Args>
	WidgetClass* InstantiateWidget(const Args&... args)
	{
		return new WidgetClass(std::forward<const Args>(args)...);
	}
};

class WidgetManagerProxy : public Proxy<WidgetManager>
{
public:
	WidgetManagerProxy();
};