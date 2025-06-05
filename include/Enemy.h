#pragma once

//-----constants section-----
#include "UpdateableObject.h"
#include "AttackBehavior.h"
#include "MoveBehavior.h"

//-----class section-----
class Enemy : public UpdateableObject
{
public:
	Enemy(sf::Vector2f position, const sf::Texture& texture, float CELL_WIDTH, float CELL_HEIGHT);
	~Enemy() = default;

	void update(sf::Time deltaTime) override;
	void setDirection(sf::Vector2f position) override;

	virtual void collide(GameObject& otherObject) override;
	virtual void guardCollide(Enemy& otherObject) override;
	virtual void explosionCollide(Explosion& otherobject) override;
	virtual void playerCollide(Player& otherObject) override;
	virtual void setFreezing(bool freeze) override;
	virtual void Display() {};

	void PerformAttack();
	void PerformMove();
	void SetMoveBehavior(std::unique_ptr<MoveBehavior>	pMoveBehavior);
	void SetAttackBehavior(std::unique_ptr<AttackBehavior>	pAttackBehavior);

	static void resetNumOfGuards();
	static int getNumOfStartingGuards();
	static int getNumOfGuardsAlive();

private:
	//void checktimer();
	std::unique_ptr<AttackBehavior>	pAttackBehavior_;
	std::unique_ptr<MoveBehavior>	pMoveBehavior_;
	static int m_num_of_guards;
	static int m_num_of_guards_alive;
	bool m_freeze = false;

	sf::Vector2f m_direction;
	sf::Vector2f m_prevlocation;
	//sf::Time m_freezeTime;
};