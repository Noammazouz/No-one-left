//-----include section-----
#include "AxisMoveBehavior.h"

//-----functions section------
//-----------------------------------------------------------------------------
sf::Vector2f AxisMoveBehavior::Move(sf::Vector2f playerPos, sf::Time /*dt*/, sf::Vector2f enemyPos) {
    float xDist = playerPos.x - enemyPos.x;
    float yDist = playerPos.y - enemyPos.y;
    sf::Vector2f dir(0.f, 0.f);

    // Decide primary axis based on preference
    if (m_preferHorizontal) {
        if (std::abs(xDist) >= std::abs(yDist)) {
            dir.x = (xDist > 0.f ? 1.f : -1.f);
        }
        else {
            dir.y = (yDist > 0.f ? 1.f : -1.f);
        }
    }
    else {
        if (std::abs(yDist) >= std::abs(xDist)) {
            dir.y = (yDist > 0.f ? 1.f : -1.f);
        }
        else {
            dir.x = (xDist > 0.f ? 1.f : -1.f);
        }
    }
    return dir;
}

void AxisMoveBehavior::OnCollision() {
    // Flip axis preference when an obstacle is hit
    m_preferHorizontal = !m_preferHorizontal;
}