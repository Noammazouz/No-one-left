//-----include section-----
#include "Projectile.h"
#include <cmath>
#include <iostream>

//-----functions section------
//-----------------------------------------------------------------------------
Projectile::Projectile(sf::Vector2f position, sf::Vector2f dir, float spd, int dmg)
    : UpdateableObject(position, "projectile"), direction(dir), speed(spd),
    isActive(true), damage(dmg), elapsedTime(0.0f)
{
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y); // to get same speed for all directions
    if (length > 0)
    {
        direction.x /= length;
        direction.y /= length;
    }
}

//-----------------------------------------------------------------------------
void Projectile::update(sf::Time deltaTime, sf::Vector2f playerPos)
{
    if (!isActive) return;

    float dt = deltaTime.asSeconds();
    elapsedTime += dt;

    sf::Vector2f movement = direction * speed * dt;
    sf::Vector2f currentPos = getPosition();
    setPosition(sf::Vector2f(currentPos.x + movement.x, currentPos.y + movement.y));

    if (isOutOfMap() || isExpired())
    {
        isActive = false;
    }
}

//-----------------------------------------------------------------------------
void Projectile::setDirection(sf::Vector2f dir)
{
    direction = dir;
}

//-----------------------------------------------------------------------------
void Projectile::setSpeed(float spd)
{
    speed = spd;
}

//-----------------------------------------------------------------------------
sf::Vector2f Projectile::getDirection() const
{
    return direction;
}

//-----------------------------------------------------------------------------
float Projectile::getSpeed() const
{
    return speed;
}

//-----------------------------------------------------------------------------
bool Projectile::getIsActive() const
{
    return isActive;
}

//-----------------------------------------------------------------------------
void Projectile::setActive(bool active)
{
    isActive = active;
}

//-----------------------------------------------------------------------------
int Projectile::getDamage() const
{
    return damage;
}

//-----------------------------------------------------------------------------
bool Projectile::isExpired() const
{
    return elapsedTime >= 3.0f; // 3 seconds 
}

//-----------------------------------------------------------------------------
bool Projectile::isOutOfMap() const
{
    sf::Vector2f pos = getPosition();
    return (pos.x < -50 || pos.x > MAP_WIDTH + 50 || pos.y < -50 || pos.y > MAP_HEIGHT + 50);
}
