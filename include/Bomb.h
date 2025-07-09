#pragma once
#include "UpdateableObject.h"
#include <SFML/System.hpp>

class GamePlay;

class Bomb : public UpdateableObject
{
public:
	Bomb(sf::Vector2f position,GamePlay* gamePlay);
	void update(sf::Time deltaTime, sf::Vector2f playerPos);
private:
	sf::Time m_timer;
	GamePlay* m_gameplay;
};