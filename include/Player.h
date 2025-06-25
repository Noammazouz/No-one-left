#pragma once

//-----include section-----
#include <iostream>
#include <SFML/Graphics.hpp>
#include "UpdateableObject.h"
#include "ResourcesManager.h"
#include "CollisionFactory.h"
#include "Enemy.h"
#include "Wall.h"
#include "Obstacles.h"
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
	~Player() = default;

	virtual void update(sf::Time deltaTime, sf::Vector2f playerPos) override;
	void setWin(bool win);
	bool getWin() const;
    int getScore();
	void setScore(int score);
	void decLife(int decLives = 1);
	void incLife(int addLives);
	int getLife();
	sf::Vector2f getPos() const;
	void initialization(sf::Vector2f pos, std::string name);
	sf::Vector2f getDirection() const;

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
};