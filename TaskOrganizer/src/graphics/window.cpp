#include "pch.h"
#include "graphics/window.h"

#include "graphics/windowcontainer.h"
#include "SFML/Window/VideoMode.hpp"
#include "SFML/Window/Event.hpp"
#include "util/time.h"
#include "util/math.h"

// todo - testing
#include "subwindow.h"

Window::Window(const Window::CreationParams& params):
	_window { sf::VideoMode{params.Width, params.Height}, params.Title },
	_clearColor { params.BackgroundColor }
{

}

void Window::Update()
{
	sf::Event event;
	while (_window.pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::Closed:
			{
				_window.close();
				break;
			}
			case sf::Event::Resized:
			{
				_isDirty = true;
				break;
			}
			case sf::Event::MouseButtonPressed:
			{
				// todo - for testing purposes, force redraw
				_isDirty = true;

				assert(event.mouseButton.x >= 0);
				assert(event.mouseButton.y >= 0);

				OnMouseButtonPressed((uint32_t)event.mouseButton.x, (uint32_t)event.mouseButton.y, event.mouseButton.button);
				break;
			}
			case sf::Event::MouseButtonReleased:
			{
				assert(event.mouseButton.x >= 0);
				assert(event.mouseButton.y >= 0);

				OnMouseButtonReleased((uint32_t)event.mouseButton.x, (uint32_t)event.mouseButton.y, event.mouseButton.button);
				break;
			}
		}
	}

	if (IsOpen() && _isDirty)
	{
		_isDirty = false;

		ReDraw();
	}
}

void Window::ReDraw()
{
	Clear();
	Draw();
}

void Window::Clear()
{
	_window.clear(_clearColor);
}

void Window::Draw()
{
	ForEachContainer([](WindowContainer& container, uint32_t depth, bool& shouldBreak)
	{
		container.Draw();
	});

	_window.display();
}

void Window::Draw(const sf::Drawable& drawable)
{
	_window.draw(drawable);
}

WindowContainer* Window::CreateContainer()
{
	// todo: this should probably use some kind of pool to place all containers in the same memory block. I use this simple impl for now.
	// todo: containers are currently never cleaned up
	return new WindowContainer(*this);
}

WindowContainer* Window::CreateRootContainer()
{
	assert(_rootContainer == nullptr);

	WindowContainer* container = CreateContainer();
	assert(container != nullptr);

	_rootContainer = container;
	return container;
}

WindowContainer* Window::AddContainer(WindowContainer& parent, EWindowSplitType split, const WindowSize& size)
{
	assert(parent.IsLeaf());	// with the current layout, we can only add new containers to leafs. non-leaf containers are invisible and are used internally for the tree structure

	WindowContainer* container = CreateContainer();
	assert(container != nullptr);

	// 1. Create new non-leaf container to act as a parent.
	WindowContainer* internalNode = CreateContainer();
	assert(internalNode != nullptr);
	internalNode->_splitType = split;

	// 2. Re-arange the tree
	if (_rootContainer == &parent)
	{
		_rootContainer = internalNode;
	}

	internalNode->_parent = parent._parent;

	if (parent._parent != nullptr)
	{
		if (parent._parent->_childLeft == &parent)
		{
			parent._parent->_childLeft = internalNode;
		}
		else
		{
			parent._parent->_childRight = internalNode;
		}
	}

	parent._parent = internalNode;
	container->_parent = internalNode;

	// We always insert to the right/bottom.
	internalNode->_childLeft = &parent;
	internalNode->_childRight = container;

	// todo - remove these bounds
	// 3. Update the bounds
	internalNode->_normalizedRelativeBoundsMin = parent._normalizedRelativeBoundsMin;
	internalNode->_normalizedRelativeBoundsMax = parent._normalizedRelativeBoundsMax;

	if (split == EWindowSplitType::Horizontal)
	{
		internalNode->_childLeft->_normalizedRelativeBoundsMin = sf::Vector2<float>{ 0.0f, 0.0f };
		internalNode->_childLeft->_normalizedRelativeBoundsMax = sf::Vector2<float>{ 1.f - 0.5f, 1.0f };

		internalNode->_childRight->_normalizedRelativeBoundsMin = sf::Vector2<float>{ 1.f - 0.5f, 0.0f };
		internalNode->_childRight->_normalizedRelativeBoundsMax = sf::Vector2<float>{ 1.0f, 1.0f };
	}
	else if (split == EWindowSplitType::Vertical)
	{
		internalNode->_childLeft->_normalizedRelativeBoundsMin = sf::Vector2<float>{ 0.0f, 0.0f };
		internalNode->_childLeft->_normalizedRelativeBoundsMax = sf::Vector2<float>{ 1.0f, 1.f - 0.5f };

		internalNode->_childRight->_normalizedRelativeBoundsMin = sf::Vector2<float>{ 0.0f, 1.f - 0.5f };
		internalNode->_childRight->_normalizedRelativeBoundsMax = sf::Vector2<float>{ 1.0f, 1.0f };
	}
	else
	{
		// Unhandled
		assert(false);
	}
	return container;
}


WindowContainer* Window::CreateNewContainer(EWindowSplitType split, const WindowSize& size)
{
	WindowContainer* targetContainer = nullptr;

	if (_rootContainer == nullptr)
	{
		targetContainer = CreateRootContainer();
	}
	else
	{
		WindowContainer* containerToSplit = _activeContainer != nullptr ? _activeContainer : FindFirstLeafContainer();
		assert(containerToSplit != nullptr);

		targetContainer = AddContainer(*containerToSplit, split, size);
	}
	
	assert(targetContainer != nullptr);

	targetContainer->_size = size;

	return targetContainer;
}

void Window::InitializeWindowContainer(WindowContainer& container, SubWindowBase& subWindow)
{
	container._subWindow = &subWindow;
}

void Window::ForEachContainer(const ForEachContainerPredicate& predicate)
{
	const_cast<const Window&>(*this).ForEachContainer([&predicate](const WindowContainer& container, uint32_t depth, bool& shouldBreak) {
		predicate(const_cast<WindowContainer&>(container), depth, shouldBreak);
	});
}

void Window::ForEachContainer(const ForEachContainerConstPredicate& predicate) const
{
	if (_rootContainer != nullptr)
	{
		bool shouldBreak = false;
		ForEachContainerInternal(*_rootContainer, 0, shouldBreak, predicate);
	}
}

//using ForEachContainerPredicate = std::function<void(const WindowContainer& container, uint32_t depth, bool& shouldBreak)>;
void Window::ForEachContainerInternal(WindowContainer& root, uint32_t depth, bool& shouldBreak, const ForEachContainerConstPredicate& predicate) const
{
	if (shouldBreak)
	{
		return;
	}

	// mid - left - right iteration
	predicate(root, depth, shouldBreak);
	if (shouldBreak)
	{
		return;
	}

	if (WindowContainer* left = root.GetLeftChild())
	{
		ForEachContainerInternal(*left, depth + 1, shouldBreak, predicate);
		if (shouldBreak)
		{
			return;
		}
	}

	if (WindowContainer* right = root.GetRightChild())
	{
		ForEachContainerInternal(*right, depth + 1, shouldBreak, predicate);
		if (shouldBreak)
		{
			return;
		}
	}
}

WindowContainer* Window::FindContainerAtLocation(uint32_t x, uint32_t y)
{
	if (_rootContainer == nullptr)
	{
		return nullptr;
	}

	// Container tree is created by subdivision so we basically do a binary search until we reach a leaf
	WindowContainer* currentContainer = _rootContainer;
	while (!currentContainer->IsLeaf())
	{
		assert(currentContainer->_childLeft != nullptr);
		assert(currentContainer->_childRight != nullptr);

		AABB boundsLeft{currentContainer->_childLeft->GetGlobalBoundsMin(), currentContainer->_childLeft->GetGlobalBoundsMax()};
		currentContainer = boundsLeft.IsPointInside(x, y) ? currentContainer->_childLeft : currentContainer->_childRight;
	}

	return currentContainer;
}

WindowContainer* Window::FindFirstLeafContainer()
{
	WindowContainer* current = _rootContainer;
	if (current == nullptr)
	{
		return nullptr;
	}

	while (!current->IsLeaf())
	{
		current = current->_childRight;
	}

	return current;
}

void Window::OnMouseButtonPressed(uint32_t x, uint32_t y, sf::Mouse::Button button)
{
	_mouseButtonDownTimestampMilli[std::underlying_type_t<sf::Mouse::Button>(button)] = Time::GetCurrentTimeMilli();

	if (WindowContainer* c = FindContainerAtLocation(x, y))
	{
		_activeContainer = c;
	}
}

void Window::OnMouseButtonReleased(uint32_t x, uint32_t y, sf::Mouse::Button button)
{
	if (Time::GetCurrentTimeMilli() - _mouseButtonDownTimestampMilli[std::underlying_type_t<sf::Mouse::Button>(button)] < MAX_MOUSE_CLICK_DURATION_MILLI)
	{
		OnMouseButtonClicked(x, y, button);
	}
}

void Window::OnMouseButtonClicked(uint32_t x, uint32_t y, sf::Mouse::Button button)
{

}
