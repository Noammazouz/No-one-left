#pragma once

//-----include section-----
#include <iostream>
#include <SFML/Graphics.hpp>
#include "UpdateableObject.h"
#include "ResourcesManager.h"
//#include "CollisionFactory.h"
#include "Enemy.h"
#include "Wall.h"
#include "Bombs.h"
#include "Explosion.h"
#include "Bullets.h"
#include "Projectile.h"
#include "AttackBehavior.h"
#include <vector>
#include <memory>
#include "Const.h"

class GameObject;

//-----class section-----
class Player : public UpdateableObject
{
public:
	Player();
	Player(sf::Vector2f position, std::string name);
	~Player() = default;

	virtual void update(sf::Time deltaTime, sf::Vector2f playerPos) override;
	void setWin(bool win);
	bool getWin() const;
    int getScore();
	void setScore(int score);
	void decLife();
	void incLife();
	int getLife();
	sf::Vector2f getPos() const;

	static int getNumOfBullets();
	static void addBullets(int bullets);
	static void decBullets();
	static bool isBulletsAvailable();
	sf::Vector2f getCurrentDirection() const;
	void handleShooting(std::vector<std::unique_ptr<Projectile>>& bullets);
	void setAttackBehavior(std::unique_ptr<AttackBehavior> attackBehavior);

private:
	bool checkDirection();
	void setDirection();
	void doAttack(std::vector<std::unique_ptr<Projectile>>& bullets);

	sf::Vector2f m_direction;
	int m_lives;
	static int m_score;
	static int m_bulletCount;
	bool m_win = false;
	bool m_isShooting = false;
	std::unique_ptr<AttackBehavior> m_attackBehavior;
	float m_targetAngle = 0.f; // add this to private section
};