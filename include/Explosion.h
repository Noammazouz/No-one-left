#pragma once
#include "UpdateableObject.h"


class Explosion : public UpdateableObject
{
public:
	Explosion(sf::Vector2f position, const sf::Texture& texture);

	virtual void update(sf::Time deltaTime) override;
	virtual void collide(GameObject& otherObject) override;
	virtual void guardCollide(Guard& otherObject) override;
	virtual void setDirection(sf::Vector2f position) override;

private:
     sf::Time m_timeToLive;
	 sf::Sprite m_explosion;
};