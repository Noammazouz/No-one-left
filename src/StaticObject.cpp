//-----include section-----
#include "StaticObject.h"

//-----functions section------
//-----------------------------------------------------------------------------
StaticObject::StaticObject(const sf::Texture& texture, const sf::Vector2f& position, float width, float height)
	:GameObject(texture, position, width, height)
{}

//-----------------------------------------------------------------------------
StaticObject::StaticObject()
	:GameObject()
{}