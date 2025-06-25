//-----include section-----
#include "Projectile.h"
#include <cmath>
#include <iostream>
#include <CollisionFactory.h>

//-----functions section------
//-----------------------------------------------------------------------------
Projectile::Projectile(sf::Vector2f position, sf::Vector2f dir, float spd, int dmg)
    : UpdateableObject(position, "projectile"), direction(dir), speed(spd),
    isActive(true), damage(dmg), elapsedTime(0.0f)
{
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y); // to get same speed for all directions.
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
//-----------------------------------------------------------------------------  
// Collision handler for Bullet vs Enemy - Order independent  
void handlePlayerBulletEnemyCollision(GameObject& obj1, GameObject& obj2)  
{  
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
       // Only player bullets can kill enemies  
       if (bullet->getOwner() == PLAYER)  
       {  
           std::cout << "Player bullet hit enemy - Enemy killed!" << std::endl;  
           enemy->setLife(true); // Mark enemy as dead  
           bullet->setActive(false); // Deactivate bullet  
       }  
       // If enemy bullet hits enemy, do nothing (no friendly fire)  
       else  
       {  
           std::cout << "Enemy bullet hit enemy - No effect (no friendly fire)" << std::endl;  
           // Bullet continues through enemy without effect  
       }  
   }  
}

//-----------------------------------------------------------------------------
// Collision handler for Bullet vs Player - Order independent
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
        if (bullet->getOwner() == BulletOwner::ENEMY)
        {
            std::cout << "Enemy bullet hit player!" << std::endl;
            player->decLife();
            bullet->setActive(false); // Deactivate bullet
        }
        // Player bullets don't hurt player (self-protection)
        else
        {
            std::cout << "Player bullet hit player - No effect (self-protection)" << std::endl;
            // Bullet continues without effect
        }
    }
}

//-----------------------------------------------------------------------------
// Collision handler for Bullet vs Wall - Order independent
void handleBulletWallCollision(GameObject& obj1, GameObject& obj2)
{
    Projectile* bullet = nullptr;

    // Check both parameter orders
    if (auto* b = dynamic_cast<Projectile*>(&obj1)) 
    {
        bullet = b;
    }
    else if (auto* b = dynamic_cast<Projectile*>(&obj2)) 
    {
        bullet = b;
    }

    if (bullet) 
    {
        std::cout << "Bullet hit wall - Bullet destroyed" << std::endl;
        bullet->setActive(false); // All bullets are stopped by walls
    }
}

//-----------------------------------------------------------------------------
// Register bullet collision handlers
void Projectile::registerBulletCollisions()
{
    static bool registered = false;
    if (registered) return;

    auto& collisionFactory = CollisionFactory::getInstance();

    // Register bullet-enemy collisions (handles both player and enemy bullets)
    collisionFactory.registerTypedCollision<Bullets, Enemy>(handlePlayerBulletEnemyCollision);

    // Register bullet-player collisions (handles both player and enemy bullets)
    collisionFactory.registerTypedCollision<Bullets, Player>(handleEnemyBulletPlayerCollision);

    // Register bullet-wall collisions (all bullets are stopped by walls)
    collisionFactory.registerTypedCollision<Bullets, Wall>(handleBulletWallCollision);

    registered = true;
    std::cout << "Bullet collisions registered." << std::endl;
}

//-----------------------------------------------------------------------------
// Auto-registration helper - runs when first Bullet is created
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