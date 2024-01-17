#pragma once

#include "graphics/windowcommon.h"
#include "graphics/renderwindow.h"
#include "SFML/Window/Mouse.hpp"
#include "math/math.h"

namespace sf
{
	class Drawable;
}
class SubWindowBase;
class WindowContainer;

class Window
{
public:
	struct CreationParams
	{
		uint32_t Width = 720;
		uint32_t Height = 480;

		const char* Title = "NewWindow";

		sf::Color BackgroundColor = sf::Color::Black;

		CreationParams& SetWidth(uint32_t value) { Width = value; return *this; }
		CreationParams& SetHeight(uint32_t value) { Height = value; return *this; }
		CreationParams& SetTitle(const char* value) { Title = value; return *this; }
		CreationParams& SetBackgroundColor(const sf::Color& value) { BackgroundColor = value; return *this; }
	};
public:
	Window(const CreationParams& params);

	void Update();

	bool IsOpen() const { return _window.isOpen(); }
	uint32_t GetWidth() const { return _window.getSize().x; }
	uint32_t GetHeigth() const { return _window.getSize().y; }

	sf::RenderTarget& GetRenderer() { return _window; }

	// New window is added to the active container or the first leaf if none is active.
	// SplitRatio in [0, 1]
	template <typename T, typename... Args>
	T* AddSubWindow(EWindowSplitType split, const WindowSize& size, const Args&... args)
	{
		WindowContainer* targetContainer = CreateNewContainer(split, size);
		assert(targetContainer != nullptr);
	
		T* subWindow = CreateSubWindow<T>(*targetContainer, std::forward<const Args>(args)...);
		assert(subWindow != nullptr);

		InitializeWindowContainer(*targetContainer, *subWindow);
		subWindow->ConstructSubWindow();

		return subWindow;
	}
	
// Containers
	const WindowContainer* GetActiveContainer() const { return _activeContainer; }

// Drawing
	void Draw(const sf::Drawable& drawable);

private:
	sf::Color _clearColor;
	RenderWindow _window;
	bool _isDirty = true;

	WindowContainer* _rootContainer = nullptr;
	WindowContainer* _activeContainer = nullptr;

	// Mouse input tracking
	static constexpr int64_t MAX_MOUSE_CLICK_DURATION_MILLI = 50;
	int64_t _mouseButtonDownTimestampMilli [std::underlying_type_t<sf::Mouse::Button>(sf::Mouse::Button::ButtonCount)];

private:
	void ReDraw();
	void Clear();
	void Draw();

	WindowContainer* CreateContainer();
	WindowContainer* CreateRootContainer();
	WindowContainer* AddContainer(WindowContainer& parent, EWindowSplitType split, const WindowSize& size);

	template <typename T, typename... Args>
	T* CreateSubWindow(WindowContainer& parentContainer, const Args&... args)
	{
		// todo - pool
		return new T(parentContainer, std::forward<const Args>(args)...);
	}

	WindowContainer* CreateNewContainer(EWindowSplitType split, const WindowSize& size);
	void InitializeWindowContainer(WindowContainer& container, SubWindowBase& subWindow);

	using ForEachContainerPredicate = std::function<void(WindowContainer& container, uint32_t depth, bool& shouldBreak)>;
	void ForEachContainer(const ForEachContainerPredicate& predicate);

	using ForEachContainerConstPredicate = std::function<void(const WindowContainer& container, uint32_t depth, bool& shouldBreak)>;
	void ForEachContainer(const ForEachContainerConstPredicate& predicate) const;

	// Don't call this function explicitly Use ForeachContainer instead
	void ForEachContainerInternal(WindowContainer& root, uint32_t depth, bool& shouldBreak, const ForEachContainerConstPredicate& predicate) const;

	WindowContainer* FindContainerAtLocation(uint32_t x, uint32_t y);
	// Rightmost in tree.
	WindowContainer* FindFirstLeafContainer();

// Events
	void OnMouseButtonPressed(uint32_t x, uint32_t y, sf::Mouse::Button button);
	void OnMouseButtonReleased(uint32_t x, uint32_t y, sf::Mouse::Button button);
	void OnMouseButtonClicked(uint32_t x, uint32_t y, sf::Mouse::Button button);
};

