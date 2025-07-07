#include "Explosion.h"
#include "ResourcesManager.h"
#include "GamePlay.h"
#include "CollisionFactory.h"
#include "Enemy.h"
#include "Wall.h"
#include "Player.h"


Explosion::Explosion(sf::Vector2f position)
	:UpdateableObject(position, EXPLOSION_NAME)
{
}

void Explosion::update(sf::Time deltaTime, sf::Vector2f playerPos)
{
    m_timer -= deltaTime;
    if (m_timer <= sf::Time::Zero)
    {
        this->setLife(true);
    }
}

void handleExplosionEnemyCollision(GameObject& obj1, GameObject& obj2)
{
    Explosion* expoPtr = nullptr;
    Enemy* enemyPtr = nullptr;
    if (auto* expo = dynamic_cast<Explosion*>(&obj1))
    {
        if (auto* enemy = dynamic_cast<Enemy*>(&obj2))
        {
            expoPtr = expo;
            enemyPtr = enemy;
        }
    }
    else if (auto* expo = dynamic_cast<Explosion*>(&obj2))
    {
        if (auto* enemy = dynamic_cast<Enemy*>(&obj1))
        {
            expoPtr = expo;
            enemyPtr = enemy;
        }
    }
    if (expoPtr && enemyPtr)
    {
        enemyPtr->setLife(true);  // or enemy->decLife()
    }
}

void handleExplosionPlayerCollision(GameObject& obj1, GameObject& obj2)
{
    Explosion* expoPtr = nullptr;
    Player* playerPtr = nullptr;
    if (auto* expo = dynamic_cast<Explosion*>(&obj1))
    {
        if (auto* player = dynamic_cast<Player*>(&obj2))
        {
            expoPtr = expo;
            playerPtr = player;
        }
    }
    else if (auto* expo = dynamic_cast<Explosion*>(&obj2))
    {
        if (auto* player = dynamic_cast<Player*>(&obj1))
        {
            expoPtr = expo;
            playerPtr = player;
        }
    }
    if (expoPtr && playerPtr)
    {
        playerPtr->decLife(EXPLOSION_DAMAGE);  // you can define EXPLOSION_DAMAGE as a const
    }
}

void handleExplosionObstacleCollision(GameObject& obj1, GameObject& obj2)
{
    Explosion* expoPtr = nullptr;
    Obstacles* ObstPtr = nullptr;
    if (auto* expo = dynamic_cast<Explosion*>(&obj1))
    {
        if (auto* Obst = dynamic_cast<Obstacles*>(&obj2))
        {
            expoPtr = expo;
            ObstPtr = Obst;
        }
    }
    else if (auto* expo = dynamic_cast<Explosion*>(&obj2))
    {
        if (auto* Obst = dynamic_cast<Obstacles*>(&obj1))
        {
            expoPtr = expo;
            ObstPtr = Obst;
        }
    }
    if (expoPtr && ObstPtr)
    {
        ObstPtr->setLife(true);  // if obstacle has lives
    }
}

void Explosion::registerExplosionCollisions()
{
    static bool registered = false;
    if (registered) return;

    auto& factory = CollisionFactory::getInstance();
    factory.registerTypedCollision<Explosion, Enemy>(handleExplosionEnemyCollision);
    factory.registerTypedCollision<Explosion, Player>(handleExplosionPlayerCollision);
    factory.registerTypedCollision<Explosion, Obstacles>(handleExplosionObstacleCollision);

    registered = true;
}


bool g_explosionCollisionRegistered = []()
    {
        Explosion::registerExplosionCollisions();
        return true;
    }();