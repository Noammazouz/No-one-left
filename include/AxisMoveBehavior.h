#pragma once 

//-----include section-----
#include "MoveBehavior.h"

//-----class section-----
class AxisMoveBehavior : public MoveBehavior {
public:
    AxisMoveBehavior();
    ~AxisMoveBehavior() override = default;

    // Compute movement direction: will side?step when avoiding, else chase
    sf::Vector2f Move(sf::Vector2f playerPos, sf::Time /*dt*/, sf::Vector2f enemyPos) override;
    void OnCollision() override;

    // Call this after a successful non colliding move to resume normal chase
    void ClearAvoidance();

private:
    bool m_preferHorizontal = true;   // primary chase axis
    bool m_avoiding = false;  // currently side stepping
    sf::Vector2f m_lastDir;                  // direction that caused collision
};
