//-----include section-----
#include "Enemy.h"
#include "Factory.h"
#include "RandomMoveBehavior.h"
#include "AxisMoveBehavior.h"
#include "BfsMoveBehavior.h"
#include "OneDirectionAttackBehavior.h"
#include "GamePlay.h"
#include <iostream>
#include "AllDirectionsAttackBehavior.h"
#include "CollisionFactory.h"
#include "Wall.h"

//-----static member initialization-----
int Enemy::m_num_of_Enemies = 0;
int Enemy::m_num_of_Enemies_alive = 0;

//-----functions section------
//-----------------------------------------------------------------------------
Enemy::Enemy(sf::Vector2f position, std::string name, GamePlay* gameplay)
	: UpdateableObject(position, name), m_direction(0, 0), m_prevlocation(position), m_gamePlay(gameplay)
{
    m_num_of_Enemies++;
    m_num_of_Enemies_alive++;
}


//-----------------------------------------------------------------------------
// Collision handler function for Enemy-Wall collisions (bidirectional)
void handleEnemyWallCollision(GameObject& obj1, GameObject& obj2)
{
    // Handle Enemy vs Wall collision (bidirectional)
    if (auto* enemy = dynamic_cast<Enemy*>(&obj1)) 
    {
        if (auto* wall = dynamic_cast<Wall*>(&obj2)) 
        {
            // Enemy hit wall - revert to previous position
            enemy->setPosition(enemy->getPrevLocation());
			enemy->SetDirection(-enemy->getDirection()); // Reverse direction
            return;
        }
    }
    // Handle Wall vs Enemy collision (reverse direction)
    if (auto* wall = dynamic_cast<Wall*>(&obj1)) 
    {
        if (auto* enemy = dynamic_cast<Enemy*>(&obj2)) 
        {
            // Enemy hit wall - revert to previous position
            enemy->setPosition(enemy->getPrevLocation());
			enemy->SetDirection(-enemy->getDirection()); // Reverse direction
            return;
        }
    }
}
//-----------------------------------------------------------------------------
// Collision handler function for Enemy-Wall collisions (multimethods style)
void handleEnemyEnemyCollision(GameObject& obj1, GameObject& obj2)
{
    // Cast to specific types and handle collision
    // Only need to handle one direction since CollisionFactory handles symmetry
    if (auto* enemy = dynamic_cast<Enemy*>(&obj1))
    {
        if (auto* enemy2 = dynamic_cast<Enemy*>(&obj2))
        {
            // Enemy hit another enemy - revert to previous position
            enemy->setPosition(enemy->getPrevLocation());
            enemy->SetDirection(-enemy->getDirection()); // Reverse direction

            return;
        }
    }
}



//-----------------------------------------------------------------------------
// Register Enemy-Wall collision handler (multimethods approach)
static bool enemyWallCollisionRegistered = []() {
    auto& collisionFactory = CollisionFactory::getInstance();
    collisionFactory.registerTypedCollision<Enemy, Wall>(handleEnemyWallCollision);
    return true;
}();

// Register Enemy-Enemy collision handler (multimethods approach)
static bool enemyenemyCollisionRegistered = []() {
    auto& collisionFactory = CollisionFactory::getInstance();
    collisionFactory.registerTypedCollision<Enemy, Enemy>(handleEnemyEnemyCollision);
    return true;
    }();

static auto regSimple = Factory<UpdateableObject>::instance().registerType(
    ObjectType::SIMPLENEMY,
    [](const sf::Vector2f& pos, GamePlay* gamePlay) -> std::unique_ptr<UpdateableObject> {
        auto enemy = std::make_unique<Enemy>(pos, "SimpleEnemy",gamePlay);
        enemy->SetMoveBehavior(std::make_unique<RandomMoveBehavior>());
        enemy->SetAttackBehavior(std::make_unique<OneDirectionAttackBehavior>());
        return enemy;
    });

static auto regSmart = Factory<UpdateableObject>::instance().registerType(
    ObjectType::SMARTENEMY,
    [](const sf::Vector2f& pos, GamePlay* gamePlay) -> std::unique_ptr<UpdateableObject> {
        auto enemy = std::make_unique<Enemy>(pos, "SmartEnemy",gamePlay);
        enemy->SetMoveBehavior(std::make_unique<AxisMoveBehavior>());
        enemy->SetAttackBehavior(std::make_unique<OneDirectionAttackBehavior>());
        return enemy;
    });

static auto regBfs = Factory<UpdateableObject>::instance().registerType(
    ObjectType::BFSENEMY,
    [](const sf::Vector2f& pos, GamePlay* gamePlay) -> std::unique_ptr<UpdateableObject> {
        auto enemy = std::make_unique<Enemy>(pos, "BfsEnemy",gamePlay);
        enemy->SetMoveBehavior(std::make_unique<BfsMoveBehavior>());
        enemy->SetAttackBehavior(std::make_unique<AllDirectionsAttackBehavior>());
        return enemy;
    });

//-----------------------------------------------------------------------------
void Enemy::update(sf::Time deltaTime, sf::Vector2f playerPos)
{
    m_direction = m_MoveBehavior->Move(playerPos, deltaTime, this->getPosition());

	this->setPrevLocation(this->getPosition());
	this->updatePosition(m_direction * ENEMY_SPEED * deltaTime.asSeconds());
}

//-----------------------------------------------------------------------------
void Enemy::SetMoveBehavior(std::unique_ptr<MoveBehavior> pMoveBehavior)
{
    m_MoveBehavior = std::move(pMoveBehavior);
}

//-----------------------------------------------------------------------------
void Enemy::SetAttackBehavior(std::unique_ptr<AttackBehavior> pAttackBehavior)
{
    m_AttackBehavior = std::move(pAttackBehavior);
}

//-----------------------------------------------------------------------------
void Enemy::SetDirection(sf::Vector2f direction)
{
	m_direction = direction;
}

//-----------------------------------------------------------------------------
sf::Vector2f Enemy::getDirection() const
{
    return m_direction;
}


void Enemy::NotifyCollision()
{
    // revert movement
    setPosition(getPrevLocation());
    // tell the behavior to reset
    if (m_MoveBehavior)
    {
        m_MoveBehavior->OnCollision();
    }
}

void Enemy::OnSuccessfulMove() {
    // Only clear avoidance if the current move behavior supports it
    m_MoveBehavior->ClearAvoidance();
    // (No need to know which concrete type it is)
}

//-------------------------------------
Enemy::~Enemy()
{
    m_num_of_Enemies_alive--;

}
//-------------------------------------
int Enemy::getNumOfEnemiesAlive()
{
    return m_num_of_Enemies_alive;
}


int Enemy::getNumOfStartingEnemies(const std::vector<std::unique_ptr<UpdateableObject>>& movingObjs)
{
    return static_cast<int>(movingObjs.size());
}