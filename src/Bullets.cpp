#include "Bullets.h"
//-----include section-----
#include "Bullets.h"
#include "Enemy.h"
#include "Player.h"
#include "Explosion.h"
#include <cmath>
#include <iostream>

//-----functions section------
//-----------------------------------------------------------------------------
Bullets::Bullets(sf::Vector2f position, sf::Vector2f dir, float spd)
    : ItemsToCollect("bullets", position), direction(dir), speed(spd), isActive(true)
{
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y); // to get same speed for all directions
    if (length > 0)
    {
        direction.x /= length;
        direction.y /= length;
    }
}

void Bullets::update(float deltaTime)  
{  
   if (!isActive) return;  

   sf::Vector2f movement = direction * speed * deltaTime;  
   sf::Vector2f currentPos = getPosition();  
   setPosition(sf::Vector2f(currentPos.x + movement.x, currentPos.y + movement.y));  

   if (isOutOfMap())  
   {  
       isActive = false;  
   }  
}

//-----------------------------------------------------------------------------
void Bullets::setDirection(sf::Vector2f dir)
{ 
   direction = dir;
}

//-----------------------------------------------------------------------------
void Bullets::setSpeed(float spd)
{ 
    speed = spd;
}

//-----------------------------------------------------------------------------
sf::Vector2f Bullets::getDirection() const
{ 
    return direction;
}

//-----------------------------------------------------------------------------
float Bullets::getSpeed() const
{ 
    return speed;
}

//-----------------------------------------------------------------------------
bool Bullets::getIsActive() const
{ 
    return isActive;
}

//-----------------------------------------------------------------------------
void Bullets::setActive(bool active)
{
    isActive = active;
}

////-----------------------------------------------------------------------------
//void Bullets::collide(GameObject& otherObject)
//{
//    isActive = false;
//}
//
////-----------------------------------------------------------------------------
//void Bullets::enemyCollide(Enemy& otherObject)
//{
//    isActive = false;
//}
//
////-----------------------------------------------------------------------------
//void Bullets::playerCollide(Player& otherObject)
//{
//    isActive = false;
//}
//
////-----------------------------------------------------------------------------
//void Bullets::explosionCollide(Explosion& otherObject)
//{
//    isActive = false;
//}

//-----------------------------------------------------------------------------
bool Bullets::isOutOfMap() const
{
    sf::Vector2f pos = getPosition();
    return (pos.x < -50 || pos.x > MAP_WIDTH + 50 || pos.y < -50 || pos.y > MAP_HEIGHT + 50);
}