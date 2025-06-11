//-----include section-----
#include "UpdateableObject.h"
#include <SFML/System.hpp>

UpdateableObject::UpdateableObject() {}

UpdateableObject::UpdateableObject(sf::Vector2f position, const sf::Texture& texture)
	: GameObject(sf::Texture(), sf::Vector2f(), 0, 0), m_starting_position(0, 0), m_prev_location(0, 0)
{
}

sf::Vector2f UpdateableObject::getPrevLocation() const 
{
	return m_prevLocation;
};

void UpdateableObject::setPrevLocation(const sf::Vector2f& pos)
{
    m_prevLocation = pos;
}