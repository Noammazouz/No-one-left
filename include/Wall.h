#pragma once

//-----include section-----
#include "StaticObject.h"

//-----class section-----
class Wall : public StaticObject
{
public:
	Wall(const sf::Texture& texture, const sf::Vector2f& position, float width, float height);

	virtual void collide(GameObject& otherObject) override;
	virtual void explosionCollide(Explosion& otherobject)override;
	virtual void enemyCollide(Enemy& otherObject) override;
	virtual void playerCollide(Player& otherObject) override;

	~Wall() = default;
};