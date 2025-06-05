#pragma once 

//-----include section-----
#include "MoveBehavior.h"

//-----class section-----
class AxisMoveBehavior : public MoveBehavior
{
public:
	AxisMoveBehavior() = default;
	virtual ~AxisMoveBehavior() = default;

	// Override the move method
	virtual void Move(sf::Vector2f playerLoc) override;
};