//-----include section-----
#include "UpdateableObject.h"
#include <iostream>
#include <SFML/System.hpp>

//-----functions section------
//-----------------------------------------------------------------------------
UpdateableObject::UpdateableObject() 
	: GameObject()
{}

//-----------------------------------------------------------------------------
UpdateableObject::UpdateableObject(sf::Vector2f position, std::string name)
	: GameObject(name, position), m_startingPosition(position), m_prevLocation(position)
{}

bool UpdateableObject::checkCollision(GameObject& otherObject)
{
	if (getBounds().intersects(otherObject.getBounds()))
	{
		return true;
	}
	return false;
}

//-----------------------------------------------------------------------------
sf::Vector2f UpdateableObject::getPrevLocation() const
{
	return m_prevLocation;
};

//-----------------------------------------------------------------------------
void UpdateableObject::setPrevLocation(const sf::Vector2f& pos)
{
    m_prevLocation = pos;
}