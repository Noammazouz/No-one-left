#pragma once

//-----includes section-----
#include "MoveBehavior.h"

//-----class section-----
class RandomMoveBehavior : public MoveBehavior
{
public:
    RandomMoveBehavior();
    virtual ~RandomMoveBehavior() = default;
    virtual void Move(sf::Vector2f playerPos, float deltaTime) override;

private:
    sf::Vector2f direction{ 1, 0 };
    float Timer = 0;
    const float CHANGE_DIRECTION_TIME = 2.0f; 

    void chooseNewDirection();
};


