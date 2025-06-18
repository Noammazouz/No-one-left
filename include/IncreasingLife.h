#pragma once

//-----include section-----
#include <SFML/Graphics.hpp>
#include "ItemsToCollect.h"

//-----class section-----
class IncreasingLife : public ItemsToCollect
{
public:
	IncreasingLife(sf::Vector2f position, const sf::Texture& texture);
	~IncreasingLife() = default;

	virtual void collide(GameObject& otherObject) override;
	virtual void enemyCollide(Enemy& otherObject) override;
	virtual void playerCollide(Player& otherObject) override;
	virtual void explosionCollide(Explosion& otherobject) override;
};