#pragma once

#include <SFML/Graphics.hpp>


class MoveBehavior
{
	public:
		MoveBehavior() = default;
		virtual ~MoveBehavior() = default;
		virtual void MoveBehavior(sf::Vector2f playerLoc = {0 ,0}) = 0;
};


class OneDirectionAttackBehavior :public AttackBehavior
{
public:
	void Attack()
	{
		//shoot in one line to the front
	}
};
class AllDirectionsAttackBehavior :public AttackBehavior
{
public:
	void Attack()
	{
		//shoot to all directions
	}
};

class SmartMoveBehavior :public MoveBehavior
{
public:
	void Move()
	{
		//smart algorithm
	}
};
class ForwardMoveBehavior :public MoveBehavior
{
public:
	void Move()
	{
		//move only forward
	}
};