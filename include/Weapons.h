#pragma once

//-----include section-----
#include "ItemsToCollect.h"

//-----class section-----
class Weapons : public ItemsToCollect
{
public:
	Weapons(sf::Vector2f position, const sf::Texture& texture, float CELL_WIDTH, float CELL_HEIGHT);
	~Weapons() = default;

	virtual void collide(GameObject& otherObject) override;
	virtual void guardCollide(Guard& otherObject) override;
	virtual void playerCollide(Player& otherObject) override;
	virtual void explosionCollide(Explosion& otherobject) override;
};