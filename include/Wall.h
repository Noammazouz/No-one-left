#pragma once

//-----include section-----
#include "StaticObject.h"

//-----class section-----
class Wall : public StaticObject
{
public:
	Wall(const sf::Texture& texture, const sf::Vector2f& position, float width, float height);
	~Wall() = default;
};