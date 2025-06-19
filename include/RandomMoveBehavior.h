#pragma once

//-----includes section-----
#include "MoveBehavior.h"

//-----class section-----
class RandomMoveBehavior : public MoveBehavior
{
public:
    RandomMoveBehavior();
    virtual ~RandomMoveBehavior() = default;
    virtual sf::Vector2f Move(sf::Vector2f playerPos, sf::Time deltaTime, sf::Vector2f enemyPos) override;
    void OnCollision() override;
private:
    sf::Time m_timer;
	sf::Vector2f m_direction;

    void chooseNewDirection();
};


