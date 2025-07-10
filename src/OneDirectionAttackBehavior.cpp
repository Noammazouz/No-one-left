//-----include section-----
#include "OneDirectionAttackBehavior.h"

//-----functions section------
//-----------------------------------------------------------------------------
std::vector<sf::Vector2f> OneDirectionAttackBehavior::Attack(sf::Vector2f position)
{
    m_directions.clear();
    m_directions.push_back(sf::Vector2f(position.x / 2, position.y));
    return m_directions;
}