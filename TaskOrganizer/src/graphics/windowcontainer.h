#pragma once

#include "graphics/windowcommon.h"

class SubWindowBase;

namespace sf
{
	class RenderTarget;
}

// Base class for any kind of content inside a window. One window can contain multiple containers in a tree-like structure.
// The container uses local and global coordinates for drawing. Local is relative to the container position inside the window while global refers to the parent window.
class WindowContainer
{
	friend class Window;

public:
	WindowContainer(Window& window);
	
	WindowContainer* GetParent() const { return _parent; }
	WindowContainer* GetLeftChild() const { return _childLeft; }
	WindowContainer* GetRightChild() const { return _childRight; }
	bool IsLeaf() const { return _childLeft == nullptr && _childRight == nullptr; }

	sf::Vector2<uint32_t> GetGlobalBoundsMin() const;
	sf::Vector2<uint32_t> GetGlobalBoundsMax() const;

	void Draw();

	sf::RenderTarget& GetRenderer();

// todo - make private
protected:
	WindowContainer* _parent = nullptr;
	WindowContainer* _childLeft = nullptr;
	WindowContainer* _childRight = nullptr;
	Window* _parentWindow;

	// Valid only for internal nodes
	EWindowSplitType _splitType = EWindowSplitType::Horizontal;

	// Valid only for leaf nodes
	WindowSize _size;
	SubWindowBase* _subWindow;

	// todo - remove
	sf::Vector2<float> _normalizedRelativeBoundsMin;
	sf::Vector2<float> _normalizedRelativeBoundsMax;

protected:
	WindowContainer() = default;	// private ctor, only Window should create new containers.

private:
	// Coordinates are in [0, 1] range and map to the parent window -> [0, width] [0, height]
	// Coordinates are relative to parent container.
	void SetNormalizedBounds(const sf::Vector2<float>& min, const sf::Vector2<float>& max)
	{
		_normalizedRelativeBoundsMin = min;
		_normalizedRelativeBoundsMax = max;
	}

	void DrawDebug();
};