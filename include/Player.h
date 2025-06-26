#pragma once

//-----include section-----
#include <iostream>
#include <vector>
#include <memory>
#include "Const.h"
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
#include "RifleGift.h"
#include "MachineGunGift.h"
#include "BazookaGift.h"

class GamePlay;
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
	void initialization(sf::Vector2f pos, std::string name, GamePlay* gamePlay);

	static int getNumOfBullets();
	static void addBullets(int bullets);
	static void decBullets();
	static bool isBulletsAvailable();
	sf::Vector2f getCurrentDirection() const;
	void handleShooting();
	void setAttackBehavior(std::unique_ptr<AttackBehavior> attackBehavior);

private:
	bool checkDirection();
	void setDirection();

	sf::Vector2f m_direction;
	int m_lives;
	static int m_score;
	static int m_bulletCount;
	bool m_win = false;
	bool m_isShooting = false;
	std::unique_ptr<AttackBehavior> m_attackBehavior;
	GamePlay* m_gamePlay;
	sf::Vector2f m_facingDirection = sf::Vector2f(0.f, -1.f); // Default facing up
};