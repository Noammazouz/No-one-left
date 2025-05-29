#pragma once 

#include "Enemy.h"

class StupidEnemy : public Enemy
{
public:
	StupidEnemy(sf::Vector2f position, const sf::Texture& texture, float CELL_WIDTH, float CELL_HEIGHT);

	void update(sf::Time deltaTime) override;
	void setDirection(sf::Vector2f position) override;

	void collide(GameObject& otherObject) override;
	void guardCollide(Guard& otherObject) override;
	void explosionCollide(Explosion& otherobject) override;
	void playerCollide(Player& otherObject) override;
	void setFreezing(bool freeze) override;

	~StupidEnemy() = default;
};