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
	GameObject(const sf::Texture& texture, const sf::Vector2f& position,
			   float width, float height);
	virtual ~GameObject() = default;

	sf::FloatRect getBounds() const;

	virtual void draw(sf::RenderWindow& window) ;
	virtual sf::Vector2f getPosition() const { return sf::Vector2f(); };

	void setPosition(const sf::Vector2f& position) {};
	sf::Vector2f getObjPosition() const;
	bool isDead() const {};
	void setLife(const bool life) {};

	virtual void setRotation(const sf::Vector2f& direction);

protected:
	void updatePosition(sf::Vector2f direction);
	void mirrorImage(sf::Vector2f direction) {};

private:
	void setSprite(sf::Vector2f pos) {};
	bool checkDirection();
	sf::Vector2f m_direction;
	float m_targetAngle = 0.f; 

	sf::Sprite m_pic;
	float m_cell_size[2]; 
	bool m_is_dead = false;
	bool m_facingRight = true;
};