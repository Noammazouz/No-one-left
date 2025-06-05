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
<<<<<<< HEAD
	virtual void guardCollide(Enemy& otherObject) override;
=======
	virtual void enemyCollide(Enemy& otherObject) override;
>>>>>>> ebd655d612b4d4a5151048c1ea5ab80f03a4dc05
	virtual void setDirection(sf::Vector2f position) override;

private:
     sf::Time m_timeToLive;
	 sf::Sprite m_explosion;
};