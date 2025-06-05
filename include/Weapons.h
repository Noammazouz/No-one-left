#pragma once

//-----include section-----
#include "ItemsToCollect.h"

//-----class section-----
class Weapons : public ItemsToCollect
{
public:
	Weapons(sf::Vector2f position, const sf::Texture& texture);
	~Weapons() = default;

	virtual void collide(GameObject& otherObject) override;
<<<<<<< HEAD
	virtual void guardCollide(Enemy& otherObject) override;
=======
	virtual void enemyCollide(Enemy& otherObject) override;
>>>>>>> ebd655d612b4d4a5151048c1ea5ab80f03a4dc05
	virtual void playerCollide(Player& otherObject) override;
	virtual void explosionCollide(Explosion& otherobject) override;
};