//-----include section-----
#include "Enemy.h"
#include "Factory.h"
#include "RandomMoveBehavior.h"
#include "AxisMoveBehavior.h"
#include "BfsMoveBehavior.h"
#include "OneDirectionAttackBehavior.h"
#include <iostream>
#include "AllDirectionsAttackBehavior.h"
#include "CollisionFactory.h"
#include "Wall.h"

//-----static member initialization-----
//int Enemy::m_num_of_enemies = 0;
//int Enemy::m_num_of_enemies_alive = 0;

//-----functions section------
//-----------------------------------------------------------------------------
Enemy::Enemy(sf::Vector2f position, std::string name)
	: UpdateableObject(position, name), m_direction(0, 0), m_prevlocation(position)
{
 /*   m_num_of_enemies++;
    m_num_of_enemies_alive++;*/
}

//-----------------------------------------------------------------------------
// Collision handler function for Enemy-Wall collisions (multimethods style)
void handleEnemyWallCollision(GameObject& obj1, GameObject& obj2)
{
    // Cast to specific types and handle collision
    // Only need to handle one direction since CollisionFactory handles symmetry
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
}

//-----------------------------------------------------------------------------
// Register Enemy-Wall collision handler (multimethods approach)
static bool enemyWallCollisionRegistered = []() {
    auto& collisionFactory = CollisionFactory::getInstance();
    collisionFactory.registerTypedCollision<Enemy, Wall>(handleEnemyWallCollision);
    return true;
}();

static auto regSimple = Factory<UpdateableObject>::instance().registerType(
    ObjectType::SIMPLENEMY,
    [](const sf::Vector2f& pos) -> std::unique_ptr<UpdateableObject> {
        auto enemy = std::make_unique<Enemy>(pos, "SimpleEnemy");
        enemy->SetMoveBehavior(std::make_unique<RandomMoveBehavior>());
        enemy->SetAttackBehavior(std::make_unique<OneDirectionAttackBehavior>());
        return enemy;
    });

static auto regSmart = Factory<UpdateableObject>::instance().registerType(
    ObjectType::SMARTENEMY,
    [](const sf::Vector2f& pos) -> std::unique_ptr<UpdateableObject> {
        auto enemy = std::make_unique<Enemy>(pos, "SmartEnemy");
        enemy->SetMoveBehavior(std::make_unique<AxisMoveBehavior>());
        enemy->SetAttackBehavior(std::make_unique<OneDirectionAttackBehavior>());
        return enemy;
    });

static auto regBfs = Factory<UpdateableObject>::instance().registerType(
    ObjectType::BFSENEMY,
    [](const sf::Vector2f& pos) -> std::unique_ptr<UpdateableObject> {
        auto enemy = std::make_unique<Enemy>(pos, "BfsEnemy");
        enemy->SetMoveBehavior(std::make_unique<BfsMoveBehavior>());
        enemy->SetAttackBehavior(std::make_unique<AllDirectionsAttackBehavior>());
        return enemy;
    });

//-----------------------------------------------------------------------------
void Enemy::update(sf::Time deltaTime, sf::Vector2f playerPos)
{
    if (m_freeze) return; // Skip update if frozen
    
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

//-----------------------------------------------------------------------------
sf::Vector2f Enemy::getPrevLocation() const
{
    return m_prevlocation;
}

//-----------------------------------------------------------------------------
void Enemy::PerformAttack(std::vector<std::unique_ptr<Bullets>>& bullets)
{
    if (!m_AttackBehavior) return;
    
    sf::Vector2f position = getPosition();
    sf::Vector2f direction = getDirection();
    
    // Enemy bullets are marked with BulletOwner::ENEMY
    m_AttackBehavior->Attack(position, direction, bullets, BulletOwner::ENEMY);
}

//-----------------------------------------------------------------------------
void Enemy::collide(GameObject& otherObject)
{
    // Basic collision handling - can be extended
}

//-----------------------------------------------------------------------------
void Enemy::enemyCollide(Enemy& otherObject)
{
    // Enemy-Enemy collision handling - enemies avoid each other
    setPosition(getPrevLocation());
}

//-----------------------------------------------------------------------------
void Enemy::explosionCollide(Explosion& otherObject)
{
    // Enemy dies from explosion
    setLife(true); // Mark as dead
}

//-----------------------------------------------------------------------------
void Enemy::playerCollide(Player& otherObject)
{
    // Enemy collides with player - damage player
    otherObject.decLife();
}

//-----------------------------------------------------------------------------
void Enemy::setFreezing(bool freeze)
{
    m_freeze = freeze;
}

//-----------------------------------------------------------------------------
void Enemy::resetNumOfEnemies()
{
    m_num_of_enemies = 0;
    m_num_of_enemies_alive = 0;
}

//-----------------------------------------------------------------------------
int Enemy::getNumOfStartingEnemies()
{
    return m_num_of_enemies;
}

//-----------------------------------------------------------------------------
int Enemy::getNumOfEnemiesAlive()
{
    return m_num_of_enemies_alive;
}