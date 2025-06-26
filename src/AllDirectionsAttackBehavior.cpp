//-----include section-----
#include "AllDirectionsAttackBehavior.h"
#include <iostream>

//-----functions section------
//-----------------------------------------------------------------------------
std::vector<sf::Vector2f> AllDirectionsAttackBehavior::Attack(sf::Vector2f position)
{
    // Use static const vector to avoid repeated allocations
    static const std::vector<sf::Vector2f> directions = {
        sf::Vector2f(0, -1),    // up
        sf::Vector2f(1, -1),    // right and up
        sf::Vector2f(1, 0),     // right
        sf::Vector2f(1, 1),     // right and down
        sf::Vector2f(0, 1),     // down
        sf::Vector2f(-1, 1),    // left and down
        sf::Vector2f(-1, 0),    // left
        sf::Vector2f(-1, -1)    // left and up
    };
    
    return directions;
}