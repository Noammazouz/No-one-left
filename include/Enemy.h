#pragma once

//-----constants section-----
#include "UpdateableObject.h"
#include "AttackBehavior.h"
#include "MoveBehavior.h"

//-----class section-----
class Enemy : public UpdateableObject
{
public:
	Enemy(sf::Vector2f position, std::string name);
	~Enemy() = default;

	void update(sf::Time deltaTime, sf::Vector2f playerPos) override;
	virtual void Display() {};
	void SetMoveBehavior(std::unique_ptr<MoveBehavior>	pMoveBehavior);
	void SetAttackBehavior(std::unique_ptr<AttackBehavior>	pAttackBehavior);
	void SetDirection(sf::Vector2f direction);
	sf::Vector2f getDirection() const;
	//void NotifyCollision();
	//void OnSuccessfulMove();

	//static int getNumOfStartingEnemies();
	//static int getNumOfEnemiesAlive();

private:
	//void checktimer();
	std::unique_ptr<AttackBehavior>	m_AttackBehavior;
	std::unique_ptr<MoveBehavior>	m_MoveBehavior;
	/*static int m_num_of_enemies;
	static int m_num_of_enemies_alive;
	bool m_freeze = false;*/

	sf::Vector2f m_direction;
	sf::Vector2f m_prevlocation;
	//sf::Time m_freezeTime;
};