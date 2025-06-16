//-----include section-----
#include "Wall.h"

//-----functions section------
//-----------------------------------------------------------------------------
Wall::Wall(const sf::Texture& texture, const sf::Vector2f& position, 
		   float width, float height)
	:StaticObject(texture, position, width, height)
{}