#pragma once

//-----include section-----
#include "ItemsToCollect.h"

//-----class section-----
class RemoveEnemy : public ItemsToCollect
{
public:
	RemoveEnemy(sf::Vector2f position, const sf::Texture& texture);
	~RemoveEnemy() = default;

	virtual void collide(GameObject& otherObject) override;
	virtual void enemyCollide(Enemy& otherObject) override;
	virtual void playerCollide(Player& otherObject) override;
	virtual void explosionCollide(Explosion& otherobject) override;
};