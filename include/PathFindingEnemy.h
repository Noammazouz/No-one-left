#pragma once

//-----include section-----
#include "Enemy.h"

//-----class section-----
class PathFindingEnemy : public Enemy
{
public:
	PathFindingEnemy(sf::Vector2f position, const sf::Texture& texture);
	~PathFindingEnemy() = default;

	void update(sf::Time deltaTime) override;
	void setDirection(sf::Vector2f position) override;

	void collide(GameObject& otherObject) override;
<<<<<<< HEAD
	void guardCollide(Enemy& otherObject) override;
=======
	void enemyCollide(Enemy& otherObject) override;
>>>>>>> ebd655d612b4d4a5151048c1ea5ab80f03a4dc05
	void explosionCollide(Explosion& otherobject) override;
	void playerCollide(Player& otherObject) override;
	void setFreezing(bool freeze) override;
};