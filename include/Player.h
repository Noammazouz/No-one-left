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
	static int getLife();
	sf::Vector2f getPos() const;

private:
	sf::Vector2f m_direction;

	bool checkDirection();
	void setDirection();
	static int m_lives;
	static int m_score;
	bool m_win = false;

	float m_targetAngle = 0.f; // add this to private section
};