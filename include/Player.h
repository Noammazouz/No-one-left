#pragma once

//-----include section-----
#include <iostream>
#include <vector>
#include <utility>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Const.h"
#include "UpdateableObject.h"
#include "ResourcesManager.h"
#include "CollisionFactory.h"
#include "Enemy.h"
#include "Wall.h"
#include "Obstacles.h"
#include "BulletsGift.h"
#include "Projectile.h"
#include "AttackBehavior.h"
#include "RifleGift.h"
#include "MachineGunGift.h"
#include "BazookaGift.h"
#include "MedkitGift.h"
#include "RemoveTime.h"
#include "RemoveEnemy.h"

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

	int getNumOfBullets();
	void addBullets(int bullets);
	void decBullets();
	bool isBulletsAvailable();
	sf::Vector2f getCurrentDirection() const;
	void handleShooting();
	void setAttackBehavior(std::unique_ptr<AttackBehavior> attackBehavior);
	void presentSound();
	void medkitSound();
	void setShootCooldown(const std::string& weaponName);
	void removeEnemyGift();
	void removeTimeGift();
	bool isBombsAvailable();
	int getNumOfBombs() const;

private:
	bool checkDirection();
	void setDirection();

	sf::Vector2f m_direction;
	int m_lives;
	int m_score;
	int m_bulletCount;
	bool m_win = false;
	std::unique_ptr<AttackBehavior> m_attackBehavior;
	GamePlay* m_gamePlay;
	sf::Vector2f m_facingDirection = sf::Vector2f(0.f, -1.f); //Default facing up.
	sf::Sound m_sound;

	//Shooting cooldown times for each type of weapon.
	std::vector<std::pair<std::string, sf::Time>> m_shootCooldowns = {
		{RIFLE_NAME, SHOOTING_TIME_RIFLE},
		{MACHINE_GUN_NAME, SHOOTING_TIME_MACHINE_GUN},
		{BAZOOKA_NAME, SHOOTING_TIME_BAZOOKA}
	};

	sf::Clock m_shootClock;
	sf::Time m_shootCooldown;

	int m_bombsCount;
	bool m_bKeyPressed; 
};