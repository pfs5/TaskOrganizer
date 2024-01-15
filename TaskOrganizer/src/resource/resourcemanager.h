#pragma once

#include "util/proxy.h"

namespace sf
{
	class Font;
}

class ResourceManager
{
// Resource getters. Using lazy loading - resource are only loaded when first requested.
public:
	ResourceManager();
	~ResourceManager();

	sf::Font* GetFont(const char* resourceName);

private:
	std::map<std::string, std::unique_ptr<sf::Font>> _fonts;

	// todo - this should be read from a config file
	// todo - use relative path
	static const inline std::map<std::string, std::string> _fontPaths = {
		{"OpenSansMedium", "X:\\Coding\\Projects\\Tools\\TaskOrganizer\\x64\\Debug\\OpenSans-Medium.ttf"}
	};

};

class ResourceManagerProxy : public Proxy<ResourceManager>
{
public:
	ResourceManagerProxy();
};