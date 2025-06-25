//-----include section-----
#include "AllDirectionsAttackBehavior.h"
#include <iostream>

//-----functions section------
//-----------------------------------------------------------------------------
std::vector<sf::Vector2f> AllDirectionsAttackBehavior::Attack(sf::Vector2f position)
{

    m_directrions.push_back(sf::Vector2f(0, -1));    // up
    m_directrions.push_back(sf::Vector2f(1, -1));    // right and up
    m_directrions.push_back(sf::Vector2f(1, 0));     // right
    m_directrions.push_back(sf::Vector2f(1, 1));     // right and down
    m_directrions.push_back(sf::Vector2f(0, 1));     // down
    m_directrions.push_back(sf::Vector2f(-1, 1));    // left and down
    m_directrions.push_back(sf::Vector2f(-1, 0));    // left
    m_directrions.push_back(sf::Vector2f(-1, -1));   // left and up

    return m_directrions;
}