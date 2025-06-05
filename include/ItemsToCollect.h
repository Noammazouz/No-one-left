#pragma once

//-----include section-----
#include "StaticObject.h"

//-----class section-----
class ItemsToCollect : public StaticObject
{
public:
	ItemsToCollect(sf::Vector2f position, const sf::Texture& texture, float CELL_WIDTH, float CELL_HEIGHT);
	~ItemsToCollect() = default;

	virtual void collide(GameObject& otherObject) override;
	virtual void guardCollide(Enemy& otherObject) override;
	virtual void playerCollide(Player& otherObject) override;
	virtual void explosionCollide(Explosion& otherobject) override;
};