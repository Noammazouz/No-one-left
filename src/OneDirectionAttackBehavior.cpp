//-----include section-----
#include "OneDirectionAttackBehavior.h"
#include <iostream>

//-----functions section------
//-----------------------------------------------------------------------------
std::vector<sf::Vector2f> OneDirectionAttackBehavior::Attack(sf::Vector2f position)
{
    m_directrions.clear();
    m_directrions.push_back(sf::Vector2f(position.x / 2, position.y));
    return m_directrions;
}