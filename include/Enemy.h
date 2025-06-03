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
	virtual void Display() {};

	void PerformAttack();
	void PerformMove();
	void SetMoveBehavior(unique_ptr<MoveBehavior>	pMoveBehavior);
	void SetAttackBehavior(unique_ptr<AttackBehavior>	pAttackBehavior);

	static void resetNumOfGuards();
	static int getNumOfStartingGuards();
	static int getNumOfGuardsAlive();

	~Enemy();
private:
	//void checktimer();
	unique_ptr<AttackBehavior>	pAttackBehavior_;
	unique_ptr<MoveBehavior>	pMoveBehavior_;
	static int m_num_of_guards;
	static int m_num_of_guards_alive;
	bool m_freeze = false;

	sf::Vector2f m_direction;
	sf::Vector2f m_prevlocation;
	//sf::Time m_freezeTime;
};