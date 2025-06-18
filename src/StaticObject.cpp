//-----include section-----
#include "StaticObject.h"

//-----functions section------
//-----------------------------------------------------------------------------
StaticObject::StaticObject(std::string name, const sf::Vector2f& position)
	:GameObject(name, position)
{}

//-----------------------------------------------------------------------------
StaticObject::StaticObject()
	:GameObject()
{}