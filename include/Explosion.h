#pragma once
#include "UpdateableObject.h"
#include <SFML/System.hpp>
#include "Const.h"

class Explosion : public UpdateableObject
{
public:
	Explosion(sf::Vector2f position);
	void update(sf::Time deltaTime, sf::Vector2f playerPos);
	static void registerExplosionCollisions();

private:
	sf::Time m_timer = sf::seconds(EXPLOSION_TIME);
};