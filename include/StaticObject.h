#pragma once

//-----include section-----
#include "GameObject.h"

//-----class section-----
class StaticObject : public GameObject
{
public:
	StaticObject();
	StaticObject(const sf::Texture& texture, const sf::Vector2f& position, float width, float height);
	virtual ~StaticObject() = default;
};
