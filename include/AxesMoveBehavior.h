#pragma once 

#include "MoveBehavior.h"

class AxesMoveBehavior : public MoveBehavior
{
public:
	AxesMoveBehavior() = default;
	virtual ~AxesMoveBehavior() = default;

	// Override the move method
	virtual void Move(sf::Vector2f playerLoc) override;
};