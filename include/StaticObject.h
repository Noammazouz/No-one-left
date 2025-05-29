#pragma once

#include "GameObject.h"

class StaticObject : public GameObject
{
public:
	StaticObject();
	StaticObject(sf::Vector2f position, const sf::Texture& texture, float CELL_WIDTH, float CELL_HEIGHT);
	virtual ~StaticObject() = default;
};
