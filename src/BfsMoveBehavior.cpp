//-----includes section-----
#include "BfsMoveBehavior.h"
#include <cmath>
#include <algorithm>

//-----functions section------
//-----------------------------------------------------------------------------
BfsMoveBehavior::BfsMoveBehavior()
{}

//-----------------------------------------------------------------------------
sf::Vector2f BfsMoveBehavior::Move(sf::Vector2f playerPos, sf::Time /*deltaTime*/, sf::Vector2f enemyPos) 
{
    //Calculate direct direction to player
    sf::Vector2f direction = playerPos - enemyPos;
    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    
    if (m_avoiding) 
    {
        //Side?step perpendicular to lastDir
        if (m_preferHorizontal) 
        {
            direction.x = 0.f;
            direction.y = (m_lastDir.x > 0.f ? 1.f : -1.f);
        }
        else 
        {
            direction.x = (m_lastDir.y > 0.f ? -1.f : 1.f);
            direction.y = 0.f;
        }
    }
    else 
    {
        //If we're close enough, don't move
        if (distance < 50.0f)
        {
            return sf::Vector2f(0.0f, 0.0f);
        }

        //Return normalized direction - collision system will handle walls
        if (distance > 0.0f)
        {
            return sf::Vector2f(direction.x / distance, direction.y / distance);
        }
    }

    m_lastDir = direction;
    return direction;
}

//-----------------------------------------------------------------------------
void BfsMoveBehavior::OnCollision() 
{
    m_avoiding = true;
    m_preferHorizontal = !m_preferHorizontal;
}

//-----------------------------------------------------------------------------
void BfsMoveBehavior::ClearAvoidance() 
{
    m_avoiding = false;
}