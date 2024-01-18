#pragma once

#include "config/staticconfig.h"
#include "containers/inplacevector.h"
#include "graphics/padding.h"
#include "graphics/widgetmanager.h"

namespace sf
{
	class RenderTarget;
}

struct WidgetSize;

class WidgetBase
{
public:
	struct DrawParams
	{
		Bounds2f WidgetGlobalBounds;
		sf::RenderTarget& Renderer;

		DrawParams(sf::RenderTarget& renderer) :
			Renderer{ renderer }
		{

		}
	};

public:
	virtual void DrawWidget(const DrawParams& params);

	virtual WidgetSize GetWidgetSize() const = 0;
	virtual sf::Vector2f GetWidgetLocalPosition() const = 0;

	template<typename WidgetClass, typename... Args>
	WidgetClass* CreateChildWidget(const Args&... args)
	{
		WidgetClass* newWidget = WidgetManagerProxy::Get().InstantiateWidget<WidgetClass>(std::forward<const Args>(args)...);
		assert(newWidget != nullptr);

		_childWidgets.PushBack(newWidget);

		return newWidget;
	}

	void SetPadding(PaddingF value) { _padding = value; }

protected:
	WidgetBase* _parentWidget = nullptr;
	InplaceVector<WidgetBase*, StaticConfig::WIDGET_MAX_CHILDREN> _childWidgets;
	PaddingF _padding;

private:
	virtual void DrawChildWidgets(const DrawParams& params);	// can be overridden to achieve different layouts
	void DrawWidgetDebug(const DrawParams& params);
};