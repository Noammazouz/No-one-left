//-----include section-----
#include "AllDirectionsAttackBehavior.h"
#include <iostream>

//-----functions section------
//-----------------------------------------------------------------------------
void AllDirectionsAttackBehavior::Attack(sf::Vector2f position, sf::Vector2f direction, std::vector<std::unique_ptr<Projectile>>& projectile, BulletOwner owner)
{
    sf::Vector2f directions[NUM_OF_DIRECTIONS] =
    {
        sf::Vector2f(0, -1),    // up
        sf::Vector2f(1, -1),    // right and up
        sf::Vector2f(1, 0),     // right
        sf::Vector2f(1, 1),     // right and down
        sf::Vector2f(0, 1),     // down
        sf::Vector2f(-1, 1),    // left and down
        sf::Vector2f(-1, 0),    // left
        sf::Vector2f(-1, -1)    // left and up
    };

    for (int directionBullet = 0; directionBullet < NUM_OF_DIRECTIONS; directionBullet++)
    {
        sf::Vector2f bulletDirection = directions[directionBullet];
        auto bullet = std::make_unique<Projectile>(position, bulletDirection, 300.0f, owner);
        projectile.push_back(std::move(bullet));
    }
}