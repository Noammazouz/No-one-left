#pragma once

#include <SFML/Graphics.hpp>
#include "Const.h"

class Door;
class Explosion;
class Presents;
class Player;
class Wall;
class Guard;

class GameObject
{
public:
	GameObject();
	GameObject(const sf::Texture& texture, sf::Vector2f pos, float CELL_WIDTH, float CELL_HEIGHT);
	virtual ~GameObject() = default;

	sf::FloatRect getBounds() const;

	virtual void draw(sf::RenderWindow& window);
	virtual sf::Vector2f getPosition() const;
	virtual void collide(GameObject& otherObject) = 0;
	virtual void playerCollide(Player& otherObject);
	virtual void guardCollide(Guard& otherObject) = 0;
	virtual void explosionCollide(Explosion& otherobject);

	void setPosition(const sf::Vector2f& position);
	bool isDead() const;
	void setLife(const bool life);

protected:
	void updatePosition(sf::Vector2f direction);
	void mirrorImage(sf::Vector2f direction);

private:
	void setSprite(sf::Vector2f pos);

	sf::Sprite m_pic;
	float m_cell_size[2];
	bool m_is_dead = false;
	bool m_facingRight = true;
};