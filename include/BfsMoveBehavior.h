#pragma once

//-----include section-----
#include "MoveBehavior.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <queue>
#include <memory>

//-----struct section-----
struct MapSection 
{
    int sectionX, sectionY;
    std::vector<std::vector<bool>> localGrid;
    bool isWalkable; // Can this entire section be entered?

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
    sf::Vector2f Move(sf::Vector2f playerPos, sf::Time deltaTime, sf::Vector2f enemyPos);
    // Note: Obstacle management methods removed - using collision-based approach instead
    void OnCollision();
    void ClearAvoidance();

private:
    // High-level grid (sections)
    int highLevelWidth, highLevelHeight;
    int sectionSize; // Size of each section in world pixels
    int localGridSize; // Grid resolution within each section

    std::vector<std::vector<std::unique_ptr<MapSection>>> sections;

    // Current path tracking
    std::vector<sf::Vector2i> highLevelPath; // Path between sections
    std::vector<sf::Vector2i> lowLevelPath;  // Path within current section
    size_t currentHighLevelIndex;
    sf::Time pathUpdateTimer;
    static const sf::Time PATH_UPDATE_INTERVAL;
    bool hasObstaclesSet; // Flag to track if obstacles have been set

    // Helper functions
    sf::Vector2i worldToSection(sf::Vector2f worldPos);
    sf::Vector2i worldToLocalGrid(sf::Vector2f worldPos);
    sf::Vector2f sectionToWorld(sf::Vector2i sectionPos);
    sf::Vector2f localGridToWorld(sf::Vector2i localPos, sf::Vector2i sectionPos);
    sf::Vector2f findSectionEdgePoint(sf::Vector2i fromSection, sf::Vector2i toSection);

    std::vector<sf::Vector2i> findHighLevelPath(sf::Vector2f start, sf::Vector2f target);
    std::vector<sf::Vector2i> findLowLevelPath(sf::Vector2f start, sf::Vector2f target, sf::Vector2i section);

    bool isValidSection(int x, int y);
    bool isSectionWalkable(int x, int y);
    bool isValidLocalCell(int x, int y);

    sf::Vector2f m_lastTriedDirection = { 0.f, 0.f };
    sf::Vector2f m_avoidDirection = { 0.f, 0.f };
    bool m_avoiding = false;
    std::array<sf::Vector2f, 3> m_avoidOptions;  // three candidate dodge vectors
    int                        m_avoidIndex = 0;
};