#pragma once

//-----include section-----
#include "StaticObject.h"

//-----class section-----
class Wall : public StaticObject
{
public:
	Wall(std::string name, const sf::Vector2f& position);
	~Wall() = default;
};