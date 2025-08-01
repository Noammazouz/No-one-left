#pragma once

//-----include section-----
#include <string>
#include <SFML/Graphics.hpp>
#include "Const.h"
#include "ResourcesManager.h"

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

	virtual void draw(sf::RenderWindow& window);

	void setPosition(const sf::Vector2f& position);
	sf::Vector2f getPosition() const;
	bool isDead() const;
	void setLife(const bool life);

protected:
	sf::Sprite m_pic;

private:
	bool m_isDead = false;
};