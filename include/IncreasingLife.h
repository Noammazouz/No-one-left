#pragma once

//-----include section-----
#include <SFML/Graphics.hpp>
#include "ItemsToCollect.h"

//-----class section-----
class IncreasingLife : public ItemsToCollect
{
public:
	IncreasingLife(sf::Vector2f position, const sf::Texture& texture, float CELL_WIDTH, float CELL_HEIGHT);

	virtual void collide(GameObject& otherObject) override;
	virtual void guardCollide(Enemy& otherObject) override;
	virtual void playerCollide(Player& otherObject) override;
	virtual void explosionCollide(Explosion& otherobject) override;

	~IncreasingLife() = default;
};