#pragma once

//-----include section-----
#include <SFML/System.hpp>
#include "UpdateableObject.h"
#include "Const.h"

//-----class section-----
class Explosion : public UpdateableObject
{
public:
	Explosion(sf::Vector2f position);
	void update(sf::Time deltaTime, sf::Vector2f playerPos);
	static void registerExplosionCollisions();

private:
	sf::Time m_timer = sf::seconds(EXPLOSION_TIME);
};