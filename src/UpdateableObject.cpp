//-----include section-----
#include "UpdateableObject.h"
#include <SFML/System.hpp>

//-----functions section------
//-----------------------------------------------------------------------------
UpdateableObject::UpdateableObject() 
{}

//-----------------------------------------------------------------------------
UpdateableObject::UpdateableObject(sf::Vector2f position, const sf::Texture& texture)
	: GameObject(sf::Texture(), sf::Vector2f(), 0, 0), m_starting_position(position), m_prevLocation(position)
{}

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