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
	virtual void enemyCollide(Enemy& otherObject) override;
	virtual void playerCollide(Player& otherObject) override;
	virtual void explosionCollide(Explosion& otherobject) override;
};

