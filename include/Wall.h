#pragma once

//-----include section-----
#include "StaticObject.h"

//-----class section-----
class Wall : public StaticObject
{
public:
	Wall(sf::Vector2f position, const sf::Texture& texture, float WIDTH, float HEIGHT);

	virtual void collide(GameObject& otherObject) override;
	virtual void explosionCollide(Explosion& otherobject)override;
	virtual void guardCollide(Guard& otherObject) override;
	virtual void playerCollide(Player& otherObject) override;

	~Wall() = default;
};