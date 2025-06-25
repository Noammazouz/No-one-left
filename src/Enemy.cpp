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
int Enemy::m_numOfEnemies = 0;
int Enemy::m_numOfEnemiesAlive = 0;

//-----functions section------
//-----------------------------------------------------------------------------
Enemy::Enemy(sf::Vector2f position, std::string name, GamePlay* gameplay)
	: UpdateableObject(position, name), m_direction(0, 0), m_prevlocation(position), m_gamePlay(gameplay)
{
    m_numOfEnemies++;
    m_numOfEnemiesAlive++;
    m_numberOfFrames = m_pic.getTexture()->getSize().x / OBJECT_WIDTH; //Calculate number of frames based on texture width.
    m_pic.setRotation(180.f); //Set initial rotation to face down.
    set_frames(m_numberOfFrames, position);
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
        auto enemy = std::make_unique<Enemy>(pos, "simple_enemy_rifle",gamePlay);
        enemy->SetMoveBehavior(std::make_unique<RandomMoveBehavior>());
        enemy->SetAttackBehavior(std::make_unique<OneDirectionAttackBehavior>());
        return enemy;
    });

static auto regSmart = Factory<UpdateableObject>::instance().registerType(
    ObjectType::SMARTENEMY,
    [](const sf::Vector2f& pos, GamePlay* gamePlay) -> std::unique_ptr<UpdateableObject> {
        auto enemy = std::make_unique<Enemy>(pos, "smart_enemy_rifle",gamePlay);
        enemy->SetMoveBehavior(std::make_unique<AxisMoveBehavior>());
        enemy->SetAttackBehavior(std::make_unique<OneDirectionAttackBehavior>());
        return enemy;
    });

static auto regBfs = Factory<UpdateableObject>::instance().registerType(
    ObjectType::BFSENEMY,
    [](const sf::Vector2f& pos, GamePlay* gamePlay) -> std::unique_ptr<UpdateableObject> {
        auto enemy = std::make_unique<Enemy>(pos, "bfs_enemy_rifle",gamePlay);
        enemy->SetMoveBehavior(std::make_unique<BfsMoveBehavior>());
        enemy->SetAttackBehavior(std::make_unique<AllDirectionsAttackBehavior>());
        return enemy;
    });

//-----------------------------------------------------------------------------
void Enemy::update(sf::Time deltaTime, sf::Vector2f playerPos)
{
    m_direction = m_MoveBehavior->Move(playerPos, deltaTime, this->getPosition());
    this->setRotation(m_direction);
	this->setPrevLocation(this->getPosition());
	this->updatePosition(m_direction * ENEMY_SPEED * deltaTime.asSeconds());
    this->updateFrames(m_direction, PLAYER_FRAME_TIME, m_numberOfFrames);
    // Calculate Euclidean distance between enemy and player
    sf::Vector2f enemyPos = this->getPosition();
    float deltaX = playerPos.x - enemyPos.x;
    float deltaY = playerPos.y - enemyPos.y;
    float squaredDistance = deltaX * deltaX + deltaY * deltaY;

    m_fireTimer += deltaTime.asSeconds();

    if (squaredDistance <= DISTANCE && m_fireTimer >= FIRE_COOLDOWN) 
    {
        m_shouldFire = true;
        m_fireTimer = 0.0f; // Reset timer
    }
    else
    {
        m_shouldFire = false;
    }
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
    m_numOfEnemiesAlive--;

}
//-------------------------------------
int Enemy::getNumOfEnemiesAlive()
{
    return m_numOfEnemiesAlive;
}

//--------------------------------------------------------------------------------------------------
int Enemy::getNumOfStartingEnemies(const std::vector<std::unique_ptr<UpdateableObject>>& movingObjs)
{
    return static_cast<int>(movingObjs.size());
}