#pragma once
#include "MoveBehavior.h"
#include <vector>
#include <queue>

class BFSMoveBehavior : public MoveBehavior
{
public:
    BFSMoveBehavior(int gridWidth, int gridHeight, int cellSize);
    virtual ~BFSMoveBehavior() = default;
    virtual void Move(sf::Vector2f playerPos, float deltaTime) override;

    void setObstaclesFromMap(const std::vector<sf::Vector2f>& wallPositions);

private:
    std::vector<std::vector<bool>> grid; 
    std::vector<sf::Vector2i> currentPath;
    size_t currentPathIndex = 0;
    int gridWidth, gridHeight, cellSize;
    float pathUpdateTimer = 0;
    const float PATH_UPDATE_INTERVAL = 0.3f; 


    sf::Vector2i worldToGrid(sf::Vector2f worldPos);
    sf::Vector2f gridToWorld(sf::Vector2i gridPos);

 
    std::vector<sf::Vector2i> findPath(sf::Vector2f start, sf::Vector2f target);
    bool isValidCell(int x, int y);
    bool isWalkable(int x, int y);
};