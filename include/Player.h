#pragma once

//-----include section-----
#include <iostream>
#include <SFML/Graphics.hpp>
#include "UpdateableObject.h"
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
	Player(sf::Vector2f position, const sf::Texture& texture);
	~Player() = default;

	virtual void update(sf::Time deltaTime) override;
	virtual void setDirection(sf::Vector2f position) override;

	virtual void collide(GameObject& otherObject) override;
	virtual void enemyCollide(Enemy& otherObject) override;
	virtual void explosionCollide(Explosion& otherobject) override;

	void setWin(bool win);
	bool getWin() const;
    int getScore();
	void setScore(int score);
	void decLife();
	void incLife();
	static int getLife();
	sf::Vector2f getPos() const;
	void draw(sf::RenderWindow& window);

private:
	bool checkDeriction();

	sf::Vector2f m_direction;
	sf::RectangleShape m_pic;
	static int m_lives;
	static int m_score;
	bool m_win = false;
};