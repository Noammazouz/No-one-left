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
	void enemyCollide(Enemy& otherObject) override;
	void explosionCollide(Explosion& otherobject) override;
	void playerCollide(Player& otherObject) override;
	void setFreezing(bool freeze) override;
};