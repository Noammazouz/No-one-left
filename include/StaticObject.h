#pragma once

//-----include section-----
#include "GameObject.h"

//-----class section-----
class StaticObject : public GameObject
{
public:
	StaticObject();
	StaticObject(std::string name, const sf::Vector2f& position);
	virtual ~StaticObject() = default;
};
