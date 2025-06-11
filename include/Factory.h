#pragma once
#include <memory>
#include <string>
#include <map>
#include "GameObject.h"

class Factory {
public:
	using createFunc = std::function<std::unique_ptr<GameObject>(const sf::Texture&, const sf::Vector2f&, float, float)>;

	static bool registerType(const std::string& type, createFunc func);
	static std::unique_ptr<GameObject> create(const std::string& type, const sf::Texture& texture, const sf::Vector2f& position, float width, float height);

private:
	static std::map<std::string, createFunc>& getRegistry();
};