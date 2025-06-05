#pragma once

//-----include section-----
#include <SFML/Graphics.hpp>
#include "ItemsToCollect.h"

//-----class section-----
class RemoveTime : public ItemsToCollect
{
public:
	RemoveTime(sf::Vector2f position, const sf::Texture& texture);
	~RemoveTime() = default;

	virtual void collide(GameObject& otherObject) override;
<<<<<<< HEAD
	virtual void guardCollide(Enemy& otherObject) override;
=======
	virtual void enemyCollide(Guard& otherObject) override;
>>>>>>> ebd655d612b4d4a5151048c1ea5ab80f03a4dc05
	virtual void playerCollide(Player& otherObject) override;
	virtual void explosionCollide(Explosion& otherobject) override;
};

