#pragma once 

//-----include section-----
#include "MoveBehavior.h"

//-----class section-----
class AxisMoveBehavior : public MoveBehavior
{
public:
    AxisMoveBehavior() = default;
    virtual ~AxisMoveBehavior() = default;
    virtual sf::Vector2f Move(sf::Vector2f playerPos, sf::Time /*deltaTime*/, sf::Vector2f enemyPos) override;
};
