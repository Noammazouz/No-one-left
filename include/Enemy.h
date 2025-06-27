#pragma once

//-----constants section-----
#include "UpdateableObject.h"
#include "AttackBehavior.h"
#include "MoveBehavior.h"

class Enemy : public UpdateableObject
{
public:
	Enemy(sf::Vector2f position, std::string name);
	~Enemy();

	void update(sf::Time deltaTime, sf::Vector2f playerPos) override;
	virtual void Display() {};
	void SetMoveBehavior(std::unique_ptr<MoveBehavior>	pMoveBehavior);
	void SetAttackBehavior(std::unique_ptr<AttackBehavior>	pAttackBehavior);
	void SetDirection(sf::Vector2f direction);
	sf::Vector2f getDirection() const;
	std::vector<sf::Vector2f> getShottingDirections();
	void NotifyCollision();
	void OnSuccessfulMove();
	bool wantsToFire() const;
	void clearFireFlag();

	static int getNumOfStartingEnemies(const std::vector<std::unique_ptr<UpdateableObject>>& movingObjs);
	static int getNumOfEnemiesAlive();

private:
	//void checktimer();
	std::unique_ptr<AttackBehavior>	m_AttackBehavior;
	std::unique_ptr<MoveBehavior>	m_MoveBehavior;
	static int m_numOfEnemies;
	static int m_numOfEnemiesAlive;
	float m_fireTimer = 0.0f;
	bool m_shouldFire=false;
	sf::Vector2f m_direction;
	sf::Vector2f m_prevlocation;
	//sf::Time m_freezeTime;
};