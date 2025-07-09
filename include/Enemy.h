#pragma once

//-----include section-----
#include "UpdateableObject.h"
#include "AttackBehavior.h"
#include "MoveBehavior.h"

//-----class section-----
class Enemy : public UpdateableObject
{
public:
	Enemy(sf::Vector2f position, std::string name, int numOfLives);
	~Enemy();

	void update(sf::Time deltaTime, sf::Vector2f playerPos) override;
	void SetMoveBehavior(std::unique_ptr<MoveBehavior>	pMoveBehavior);
	void SetAttackBehavior(std::unique_ptr<AttackBehavior>	pAttackBehavior);
	void SetDirection(sf::Vector2f direction);
	sf::Vector2f getDirection() const;
	std::vector<sf::Vector2f> getShottingDirections();
	void NotifyCollision();
	void OnSuccessfulMove();
	bool wantsToFire();
	void clearFireFlag();
	void setDeathName(const std::string& name);
	std::string getDeathName() const;
	void takeDamage(int damage);
	bool isAlive() const;

	static int getNumOfEnemiesAlive();
	static int getNumOfEnemiesAtTheStart();
	static void resetNumOfEnemeis();

private:
	std::unique_ptr<AttackBehavior>	m_AttackBehavior;
	std::unique_ptr<MoveBehavior>	m_MoveBehavior;
	static int m_numOfEnemies;
	static int m_numOfEnemiesAlive;
	int m_numOfLives;
	float m_fireTimer = 0.0f;
	bool m_shouldFire = false;
	bool m_dead = false;
	std::string m_deathName;
	sf::Vector2f m_direction;
	sf::Vector2f m_prevlocation;
};