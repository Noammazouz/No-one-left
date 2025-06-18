#include "Enemy.h"
#include "Factory.h"
#include "RandomMoveBehavior.h"
#include "AxisMoveBehavior.h"
#include "BfsMoveBehavior.h"
#include "OneDirectionAttackBehavior.h"
#include <iostream>
#include "AllDirectionsAttackBehavior.h"

Enemy::Enemy(sf::Vector2f position, std::string name)
	: UpdateableObject(position, name), m_direction(0, 0), m_prevlocation(position)
{
	std::cout << "Enemy created at position: " << position.x << ", " << position.y << std::endl;
}

// Note: Enemy-Wall collision handling removed due to CollisionFactory template issues
// You can implement collision handling in your game's collision detection system instead

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
        enemy->SetMoveBehavior(std::make_unique<BfsMoveBehavior>(MAP_WIDTH, MAP_HEIGHT, SECTION_SIZE, LOCAL_GRID_SIZE));
        enemy->SetAttackBehavior(std::make_unique<AllDirectionsAttackBehavior>());
        return enemy;
    });



void Enemy::update(sf::Time deltaTime, sf::Vector2f playerPos)
{
    m_direction = m_MoveBehavior->Move(playerPos, deltaTime ,this->getPosition());

	this->setPrevLocation(this->getPosition());
	this->updatePosition(m_direction * ENEMY_SPEED * deltaTime.asSeconds());
}

void Enemy::SetMoveBehavior(std::unique_ptr<MoveBehavior> pMoveBehavior)
{
    m_MoveBehavior = std::move(pMoveBehavior);
}

void Enemy::SetAttackBehavior(std::unique_ptr<AttackBehavior> pAttackBehavior)
{
    m_AttackBehavior = std::move(pAttackBehavior);
}