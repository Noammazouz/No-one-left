//-----include section-----
#include "AxisMoveBehavior.h"

//-----functions section------
//-----------------------------------------------------------------------------
sf::Vector2f AxisMoveBehavior::Move(sf::Vector2f playerPos, sf::Time /*deltaTime*/, sf::Vector2f enemyPos)
 {
    float xDistance = enemyPos.x - playerPos.x;
    float yDistance = enemyPos.y - playerPos.y;

    if (std::abs(yDistance) > std::abs(xDistance))
    {
        if (yDistance > 0)
        {
            return sf::Vector2f(0, -1);//up
        }
        else
        {
            return sf::Vector2f(0, 1);//down
        }
    }
    else
    {
        if (xDistance > 0)
        {
            return sf::Vector2f(-1, 0); //left
        }
        else
        {
            return sf::Vector2f(1, 0); //right
        }
    }
}