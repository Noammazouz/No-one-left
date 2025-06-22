#include "AxisMoveBehavior.h"
#include <cmath>

AxisMoveBehavior::AxisMoveBehavior() = default;

sf::Vector2f AxisMoveBehavior::Move(sf::Vector2f playerPos, sf::Time, sf::Vector2f enemyPos) {
    sf::Vector2f dir(0.f, 0.f);

    if (m_avoiding) {
        // Side?step perpendicular to lastDir
        if (m_preferHorizontal) {
            dir.x = 0.f;
            dir.y = (m_lastDir.x > 0.f ? 1.f : -1.f);
        }
        else {
            dir.x = (m_lastDir.y > 0.f ? -1.f : 1.f);
            dir.y = 0.f;
        }
    }
    else {
        float dx = playerPos.x - enemyPos.x;
        float dy = playerPos.y - enemyPos.y;
        // Normal chase along preferred axis
        if (m_preferHorizontal) {
            if (std::abs(dx) > std::abs(dy))
                dir.x = (dx > 0.f ? 1.f : -1.f);
            else
                dir.y = (dy > 0.f ? 1.f : -1.f);
        }
        else {
            if (std::abs(dy) > std::abs(dx))
                dir.y = (dy > 0.f ? 1.f : -1.f);
            else
                dir.x = (dx > 0.f ? 1.f : -1.f);
        }
    }

    // Always remember what we just tried
    m_lastDir = dir;
    return dir;
}

void AxisMoveBehavior::OnCollision() {
    // Enter avoidance mode and flip primary axis for side?step logic
    m_avoiding = true;
    m_preferHorizontal = !m_preferHorizontal;
}

void AxisMoveBehavior::ClearAvoidance()
{
    m_avoiding = false;
}
