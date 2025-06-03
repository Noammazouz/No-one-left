#pragma once

#include "MoveBehavior.h"

class BfsMoveBehavior : public MoveBehavior
{
public:
	BfsMoveBehavior() = default;
	virtual ~BfsMoveBehavior() = default;

	// Override the move method
	virtual void Move(sf::Vector2f playerLoc) override;
};