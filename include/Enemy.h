#pragma once
#include "UpdateableObject.h"

class Enemy : public UpdateableObject
{
public:
	Enemy(sf::Vector2f position, const sf::Texture& texture, float CELL_WIDTH, float CELL_HEIGHT);
	void update(sf::Time deltaTime) override;
	void setDirection(sf::Vector2f position) override;

	virtual void collide(GameObject& otherObject) override;
	virtual void guardCollide(Guard& otherObject) override;
	virtual void explosionCollide(Explosion& otherobject) override;
	virtual void playerCollide(Player& otherObject) override;
	virtual void setFreezing(bool freeze) override;

	static void resetNumOfGuards();
	static int getNumOfStartingGuards();
	static int getNumOfGuardsAlive();

	~Enemy();
private:
	//void checktimer();

	static int m_num_of_guards;
	static int m_num_of_guards_alive;
	bool m_freeze = false;

	sf::Vector2f m_direction;
	sf::Vector2f m_prevlocation;
	//sf::Time m_freezeTime;
};