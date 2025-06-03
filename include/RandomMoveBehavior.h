#pragma once

#include "MoveBehavior.h"

class RandomMoveBehavior : public MoveBehavior
{
public:
	RandomMoveBehavior() = default;
	virtual ~RandomMoveBehavior() = default;

	// Override the move method
	virtual void Move(sf::Vector2f playerLoc) override;
};