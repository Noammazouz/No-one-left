#pragma once

#include "StaticObject.h"

class ItemesToCollect : public StaticObject
{
public:
	ItemesToCollect(sf::Vector2f position, const sf::Texture& texture);

	virtual void collide(GameObject& otherObject) override;
	virtual void enemyCollide(Enemy& otherObject) override;
	virtual void playerCollide(Player& otherObject) override;
	virtual void explosionCollide(Explosion& otherobject) override;

	~ItemesToCollect() = default;
};