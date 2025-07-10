#pragma once

//-----include section-----
#include "MoveBehavior.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <queue>
#include <memory>
#include <array>

//-----struct section-----
struct MapSection 
{
    int sectionX, sectionY;
    std::vector<std::vector<bool>> localGrid;
    bool isWalkable; //Can this entire section be entered?

    MapSection(int x, int y, int localSize)
        : sectionX(x), sectionY(y), isWalkable(true) 
    {
        localGrid.resize(localSize, std::vector<bool>(localSize, true));
    }
};

//-----class section-----
class BfsMoveBehavior : public MoveBehavior
{
public:
    BfsMoveBehavior();
	~BfsMoveBehavior() = default;

    sf::Vector2f Move(sf::Vector2f playerPos, sf::Time deltaTime, sf::Vector2f enemyPos);
    //Note: Obstacle management methods removed - using collision-based approach instead
    void OnCollision();
    void ClearAvoidance();

private:
    bool m_preferHorizontal = true; //primary chase axis
    sf::Vector2f m_avoidDirection = { 0.f, 0.f };
    bool m_avoiding = false;
    sf::Vector2f m_lastDir; //direction that caused collision
};