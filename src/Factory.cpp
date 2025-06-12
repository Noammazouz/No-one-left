#include "Factory.h"

bool Factory::registerType(const std::string& type, createFunc func)
{
	getRegistry()[type] = func;
	return true;
}

std::unique_ptr<GameObject> Factory::create(const std::string& type, const sf::Texture& texture, const sf::Vector2f& position, float width, float height)
{
	auto it = getRegistry().find(type);
	if (it != getRegistry().end())
	{
		return it->second(texture, position, width, height);
	}
	return nullptr; // or throw an exception if type not found
}


std::map<std::string, Factory::createFunc>& Factory::getRegistry()
{
	static std::map<std::string, createFunc> registry;
	return registry;
}