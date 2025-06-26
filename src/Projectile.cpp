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
    this->updatePosition(m_direction * PROJECTILE_SPEED * deltaTime.asSeconds());
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
    //std::cout << "in PlayerBulletEnemyCollision" << std::endl;
   Projectile* bullet = nullptr;  
   Enemy* enemy = nullptr;  

   // Check both parameter orders  
   if (auto* b = dynamic_cast<Projectile*>(&obj1)) 
   {  
       if (auto* e = dynamic_cast<Enemy*>(&obj2)) 
       {  
           bullet = b;  
           enemy = e;  
       }  
   }  
   else if (auto* b = dynamic_cast<Projectile*>(&obj2)) 
   {  
       if (auto* e = dynamic_cast<Enemy*>(&obj1)) 
       {  
           bullet = b;  
           enemy = e;  
       }  
   }  

   if (bullet && enemy) 
   {  
       //Only player bullets can kill enemies
       if (bullet->getOwner() == _PLAYER)  
       {  
           //std::cout << "Player bullet hit enemy - Enemy killed!" << std::endl;  
           enemy->setLife(true); //Mark enemy as dead  
           bullet->setActive(false); //Deactivate bullet  
           bullet->setLife(true);
       }  
       //If enemy bullet hits enemy, do nothing (no friendly fire)  
       else  
       {  
           //std::cout << "Enemy bullet hit enemy - No effect (no friendly fire)" << std::endl;  
           //Bullet continues through enemy without effect  
       }  
   }  
}

//-----------------------------------------------------------------------------
// Collision handler for Bullet vs Player - Order independent.
void handleEnemyBulletPlayerCollision(GameObject& obj1, GameObject& obj2)
{
    Projectile* bullet = nullptr;
    Player* player = nullptr;

    // Check both parameter orders
    if (auto* b = dynamic_cast<Projectile*>(&obj1)) 
    {
        if (auto* p = dynamic_cast<Player*>(&obj2)) 
        {
            bullet = b;
            player = p;
        }
    }
    else if (auto* b = dynamic_cast<Projectile*>(&obj2)) 
    {
        if (auto* p = dynamic_cast<Player*>(&obj1)) 
        {
            bullet = b;
            player = p;
        }
    }

    if (bullet && player) 
    {
        // Only enemy bullets can hurt player
        if (bullet->getOwner() == ENEMY)
        {
            //std::cout << "Enemy bullet hit player!" << std::endl;
            player->decLife(PROJECTILE_DAMAGE);
            bullet->setActive(false); // Deactivate bullet
            bullet->setLife(true);
        }
        // Player bullets don't hurt player (self-protection)
        else
        {
            //std::cout << "Player bullet hit player - No effect (self-protection)" << std::endl;
            // Bullet continues without effect
        }
    }
}

//-----------------------------------------------------------------------------
//Collision handler for Bullet vs Wall - Order independent.
void handleBulletWallCollision(GameObject& obj1, GameObject& obj2)
{
    Projectile* bullet = nullptr;
	Wall* wall = nullptr;

    //Check both parameter orders.
    if (auto* b = dynamic_cast<Projectile*>(&obj1)) 
    {
        if (auto* w = dynamic_cast<Wall*>(&obj2)) 
        {
            bullet = b;
            wall = w;
		}

    }
    else if (auto* b = dynamic_cast<Projectile*>(&obj2)) 
    {
      if (auto* w = dynamic_cast<Wall*>(&obj1)) 
      {
            wall = w;
            bullet = b;
	   }
        
    }

    if (bullet&& wall) 
    {
        //std::cout << "Bullet hit wall - Bullet destroyed" << std::endl;
        bullet->setActive(false); // All bullets are stopped by walls
        bullet->setLife(true);
        if(bullet->getOwner() == _PLAYER)
		wall->setLife(true); // Mark wall as destroyed (if needed)
    }
}

//-----------------------------------------------------------------------------
void handleBulletObstacleCollision(GameObject& obj1, GameObject& obj2)
{
    Projectile* bullet = nullptr;
    Obstacles* obstacle = nullptr;

    //Check both parameter orders.
    if (auto* b = dynamic_cast<Projectile*>(&obj1))
    {
        if (auto* o = dynamic_cast<Obstacles*>(&obj2))
        {
            bullet = b;
            obstacle = o;
		}
    }
    else if (auto* o = dynamic_cast<Obstacles*>(&obj1))
    {
        if (auto* b = dynamic_cast<Projectile*>(&obj2))
        {
            bullet = b;
            obstacle = o;
        }
    }

    if (bullet && obstacle)
    {
        bullet->setActive(false); //All bullets are stopped by obstacle.
        bullet->setLife(true);
        obstacle->decLife();
    }
}

void handleBulletVSBulletCollision(GameObject& obj1, GameObject& obj2)
{
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

    collisionFactory.registerTypedCollision<Projectile, Projectile>(handleBulletVSBulletCollision);

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