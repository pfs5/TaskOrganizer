#include "pch.h"
#include "resource/resourcemanager.h"

#include "SFML/Graphics/Font.hpp"

ResourceManager::ResourceManager()
{

}

ResourceManager::~ResourceManager()
{

}

sf::Font* ResourceManager::GetFont(const char* resourceName)
{
	auto it = _fonts.find(resourceName);
	if (it != _fonts.end())
	{
		return it->second.get();
	}

	auto resourcePathIt = _fontPaths.find(resourceName);
	assert(resourcePathIt != _fontPaths.end());

	sf::Font* font = _fonts.emplace(resourceName, new sf::Font{}).first->second.get();
	assert(font != nullptr);
	font->loadFromFile(resourcePathIt->second);
	return font;
}

ResourceManagerProxy::ResourceManagerProxy()
{

}
