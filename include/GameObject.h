#pragma once

//-----include section-----
#include <SFML/Graphics.hpp>
#include "Const.h"
#include "ResourcesManager.h"

class Door;
class Explosion;
class Presents;
class Player;
class Wall;
class Enemy;

//-----class section-----
class GameObject
{
public:
	GameObject();
	GameObject(std::string name, const sf::Vector2f& position);
	virtual ~GameObject() = default;

	sf::FloatRect getBounds() const;

	virtual void draw(sf::RenderWindow& window) ;

	void setPosition(const sf::Vector2f& position);
	sf::Vector2f getPosition() const;
	bool isDead() const;
	void setLife(const bool life);

protected:
	void updatePosition(sf::Vector2f direction);
	void mirrorImage(sf::Vector2f direction) {};
	void setRotation(const sf::Vector2f& direction);

private:
	bool checkDirection();
	sf::Vector2f m_direction;
	float m_targetAngle = 0.f; 

	sf::Sprite m_pic;
	float m_cell_size[2]; 
	bool m_isDead = false;
	bool m_facingRight = true;
};