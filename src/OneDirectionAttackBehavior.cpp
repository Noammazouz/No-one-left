//-----include section-----
#include "OneDirectionAttackBehavior.h"
#include <iostream>

//-----functions section------
//-----------------------------------------------------------------------------
void OneDirectionAttackBehavior::Attack(sf::Vector2f position, sf::Vector2f direction, std::vector<std::unique_ptr<Projectile>>& bullets)
{
    if (direction.x == 0 && direction.y == 0)
    {
		direction = sf::Vector2f(1.0f, 0.0f); // the default direction is right if no movement 
    }

    auto bullet = std::make_unique<Projectile>(position, direction, 300.0f, 1);
    bullets.push_back(std::move(bullet));
}