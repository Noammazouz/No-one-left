//-----includes section-----
#include "Obstacles.h"
#include <random>
#include "Factory.h"
#include "Enemy.h"
#include "CollisionFactory.h"
#include "GamePlay.h"

//-----functions section------
//-----------------------------------------------------------------------------
Obstacles::Obstacles(const sf::Vector2f& position, std::string name)
	: StaticObject(name, position)
{}

//-----------------------------------------------------------------------------
void Obstacles::decLife()
{
    if (m_life > 0) --m_life;
            

    if (m_life == 0) this->setLife(true); //Mark for removal in GamePlay::handleErasing()
}

//-----------------------------------------------------------------------------
void handleObstacleEnemyCollision(GameObject& obj1, GameObject& obj2)
{
    //We know from registration that one is Enemy, one is Obstacle
    Enemy* enemy = dynamic_cast<Enemy*>(&obj1);
    Obstacles* obs = dynamic_cast<Obstacles*>(&obj2);

    if (enemy && obs) 
    {
        // revert position and reverse direction
        enemy->NotifyCollision();
    }
}

//-----------------------------------------------------------------------------
static bool regObs1 = Factory<StaticObject>::instance().registerType(
    ObjectType::OBSTACLE1,
    [](const sf::Vector2f& pos, GamePlay* gamePlay) -> std::unique_ptr<StaticObject> {
        return std::make_unique<Obstacles>(pos, "obstacle1");
    });

static bool regObs2 = Factory<StaticObject>::instance().registerType(
    ObjectType::OBSTACLE2,
    [](const sf::Vector2f& pos, GamePlay* gamePlay) -> std::unique_ptr<StaticObject> {
        return std::make_unique<Obstacles>(pos, "obstacle2");
    });

static bool regObs3 = Factory<StaticObject>::instance().registerType(
    ObjectType::OBSTACLE3,
    [](const sf::Vector2f& pos, GamePlay* gamePlay) -> std::unique_ptr<StaticObject> {
        return std::make_unique<Obstacles>(pos, "obstacle3");
    });

static bool regObsColl = []() {
    auto& cf = CollisionFactory::getInstance();
    cf.registerTypedCollision<Enemy, Obstacles>(handleObstacleEnemyCollision);
    return true;
    }();
