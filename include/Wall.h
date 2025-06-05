#pragma once

//-----include section-----
#include "StaticObject.h"

//-----class section-----
class Wall : public StaticObject
{
public:
	Wall(sf::Vector2f position, const sf::Texture& texture);

	virtual void collide(GameObject& otherObject) override;
	virtual void explosionCollide(Explosion& otherobject)override;
	virtual void enemyCollide(Enemy& otherObject) override;
	virtual void playerCollide(Player& otherObject) override;

	~Wall() = default;
};