#pragma once

//-----include section-----
#include "UpdateableObject.h"

//-----class section-----
class Explosion : public UpdateableObject
{
public:
	Explosion(sf::Vector2f position, const sf::Texture& texture);

	virtual void update(sf::Time deltaTime) override;
	virtual void collide(GameObject& otherObject) override;
	virtual void enemyCollide(Enemy& otherObject) override;
	virtual void setDirection(sf::Vector2f position) /*override*/;

private:
     sf::Time m_timeToLive;
	 sf::Sprite m_explosion;
};