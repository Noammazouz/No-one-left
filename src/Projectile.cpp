//-----include section-----
#include "Projectile.h"
#include <cmath>
#include <iostream>
#include <numbers>
#include "CollisionFactory.h"
#include "Factory.h"

//-----functions section------
//-----------------------------------------------------------------------------
Projectile::Projectile(sf::Vector2f position, sf::Vector2f direction, BulletOwner owner)
    : UpdateableObject(position, PROJECTILE_NAME), isActive(true), m_elapsedTime(0.0f), m_direction(direction), m_owner(owner)
{
    float length = std::sqrt(m_direction.x * m_direction.x + m_direction.y * m_direction.y); // to get same speed for all directions
    if (length > 0)
    {
        m_direction.x /= length;
        m_direction.y /= length;
    }

    float angleRadians = std::atan2(m_direction.y, m_direction.x);
    float angleDegrees = angleRadians * 180.0f / std::numbers::pi;
    m_pic.setRotation(angleDegrees + 90.0f);
}

//-----------------------------------------------------------------------------
void Projectile::update(sf::Time deltaTime, sf::Vector2f playerPos)
{
    if (!isActive) return;
    m_pic.move(m_direction * PROJECTILE_SPEED * deltaTime.asSeconds());
    m_elapsedTime += deltaTime.asSeconds();

    if (isExpired())
    {
        isActive = false;
        this->setLife(true);
    }
}

//-----------------------------------------------------------------------------
void Projectile::setDirection(sf::Vector2f dir)
{   
    m_direction = dir;
}

//-----------------------------------------------------------------------------
sf::Vector2f Projectile::getDirection() const
{
    return m_direction;
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
bool Projectile::isExpired() const
{
    return m_elapsedTime >= PROJECTILE_AIR_TIME;
}

//-----------------------------------------------------------------------------  
//Collision handler for Bullet vs Enemy - Order independent.  
void handlePlayerBulletEnemyCollision(GameObject& obj1, GameObject& obj2)  
{  
   Projectile* bulletPtr = nullptr;  
   Enemy* enemyPtr = nullptr;  

   // Check both parameter orders  
   if (auto* bullet = dynamic_cast<Projectile*>(&obj1)) 
   {  
       if (auto* enemy = dynamic_cast<Enemy*>(&obj2)) 
       {  
           bulletPtr = bullet;
           enemyPtr = enemy;
       }  
   }  
   else if (auto* bullet = dynamic_cast<Projectile*>(&obj2))
   {  
       if (auto* enemy = dynamic_cast<Enemy*>(&obj1))
       {  
           bulletPtr = bullet;
           enemyPtr = enemy;
       }  
   }  

   if (bulletPtr && enemyPtr)
   {  
       //Only player bullets can kill enemies
       if (bulletPtr->getOwner() == _PLAYER)  
       {  
           enemyPtr->takeDamage(1);
           bulletPtr->setActive(false); //Deactivate bullet  
           bulletPtr->setLife(true);
           if (!enemyPtr->isAlive())
           {
               enemyPtr->setLife(true); //Mark enemy as dead  
           }
       }  
   }  
}

//-----------------------------------------------------------------------------
// Collision handler for Bullet vs Player - Order independent.
void handleEnemyBulletPlayerCollision(GameObject& obj1, GameObject& obj2)
{
    Projectile* bulletPtr = nullptr;
    Player* playerPtr = nullptr;

    // Check both parameter orders
    if (auto* bullet = dynamic_cast<Projectile*>(&obj1)) 
    {
        if (auto* player = dynamic_cast<Player*>(&obj2)) 
        {
            bulletPtr = bullet;
            playerPtr = player;
        }
    }
    else if (auto* bullet = dynamic_cast<Projectile*>(&obj2)) 
    {
        if (auto* player = dynamic_cast<Player*>(&obj1))
        {
            bulletPtr = bullet;
            playerPtr = player;
        }
    }

    if (bulletPtr && playerPtr)
    {
        // Only enemy bullets can hurt player
        if (bulletPtr->getOwner() == ENEMY)
        {
            playerPtr->decLife(PROJECTILE_DAMAGE);
            bulletPtr->setActive(false); // Deactivate bullet
            bulletPtr->setLife(true);
        }
    }
}

//-----------------------------------------------------------------------------
//Collision handler for Bullet vs Wall - Order independent.
void handleBulletWallCollision(GameObject& obj1, GameObject& obj2)
{
    Projectile* bulletPtr = nullptr;
	Wall* wallPtr = nullptr;

    //Check both parameter orders.
    if (auto* bullet = dynamic_cast<Projectile*>(&obj1))
    {
        if (auto* wall = dynamic_cast<Wall*>(&obj2)) 
        {
            bulletPtr = bullet;
            wallPtr = wall;
		}

    }
    else if (auto* bullet = dynamic_cast<Projectile*>(&obj2)) 
    {
      if (auto* wall = dynamic_cast<Wall*>(&obj1)) 
      {
            wallPtr = wall;
            bulletPtr = bullet;
	   }
        
    }

    if (bulletPtr && wallPtr)
    {
        bulletPtr->setActive(false); // All bullets are stopped by walls
        bulletPtr->setLife(true);
    }
}

//-----------------------------------------------------------------------------
void handleBulletObstacleCollision(GameObject& obj1, GameObject& obj2)
{
    Projectile* bulletPtr = nullptr;
    Obstacles* obstaclePtr = nullptr;

    //Check both parameter orders.
    if (auto* bullet = dynamic_cast<Projectile*>(&obj1))
    {
        if (auto* obstacle = dynamic_cast<Obstacles*>(&obj2))
        {
            bulletPtr = bullet;
            obstaclePtr = obstacle;
		}
    }
    else if (auto* obstacle = dynamic_cast<Obstacles*>(&obj1))
    {
        if (auto* bullet = dynamic_cast<Projectile*>(&obj2))
        {
            bulletPtr = bullet;
            obstaclePtr = obstacle;
        }
    }

    if (bulletPtr && obstaclePtr)
    {
        bulletPtr->setActive(false); //All bullets are stopped by obstacle.
        bulletPtr->setLife(true);
        obstaclePtr->decLife();
    }
}

//-----------------------------------------------------------------------------
//Register bullet collision handlers.
void Projectile::registerBulletCollisions()
{
    static bool registered = false;
    if (registered) return;

    auto& collisionFactory = CollisionFactory::getInstance();

    // Register bullet-enemy collisions (handles both player and enemy bullets)
    collisionFactory.registerTypedCollision<Projectile, Enemy>(handlePlayerBulletEnemyCollision);

    // Register bullet-player collisions (handles both player and enemy bullets)
    collisionFactory.registerTypedCollision<Projectile, Player>(handleEnemyBulletPlayerCollision);

    // Register bullet-wall collisions (all bullets are stopped by walls)
    collisionFactory.registerTypedCollision<Projectile, Wall>(handleBulletWallCollision);

    collisionFactory.registerTypedCollision<Projectile, Obstacles>(handleBulletObstacleCollision);

    registered = true;
}

//-----------------------------------------------------------------------------
//Auto-registration helper - runs when first Bullet is created.
bool g_bulletCollisionRegistered = []()
    {
        Projectile::registerBulletCollisions();
        return true;
    }();

//-----------------------------------------------------------------------------
BulletOwner Projectile::getOwner() const
{
    return m_owner;
}
