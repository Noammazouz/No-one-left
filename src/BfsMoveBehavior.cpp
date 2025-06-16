#include "BFSMoveBehavior.h"
#include <cmath>
#include <algorithm>

BFSMoveBehavior::BFSMoveBehavior(int gridWidth, int gridHeight, int cellSize)
    : gridWidth(gridWidth), gridHeight(gridHeight), cellSize(cellSize) {

    grid.resize(gridHeight, std::vector<bool>(gridWidth, true));
}

void BFSMoveBehavior::Move(sf::Vector2f playerPos, float deltaTime) {
    pathUpdateTimer += deltaTime;

    if (pathUpdateTimer >= PATH_UPDATE_INTERVAL || currentPath.empty()) {
        currentPath = findPath(enemyPos, playerPos);
        currentPathIndex = 0;
        pathUpdateTimer = 0;
    }


    if (!currentPath.empty() && currentPathIndex < currentPath.size()) {
        sf::Vector2f targetPos = gridToWorld(currentPath[currentPathIndex]);
        sf::Vector2f direction = targetPos - enemyPos;


        float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        if (distance < cellSize * 0.2f) {
            currentPathIndex++;
            return;
        }


        if (distance > 0) {
            direction.x /= distance;
            direction.y /= distance;
        }

        enemyPos.x += direction.x * speed * deltaTime;
        enemyPos.y += direction.y * speed * deltaTime;
    }
}

void BFSMoveBehavior::setObstaclesFromMap(const std::vector<sf::Vector2f>& wallPositions) {
    for (int y = 0; y < gridHeight; ++y) {
        for (int x = 0; x < gridWidth; ++x) {
            grid[y][x] = true;
        }
    }

     //read wall location from csv instead
    for (const auto& wallPos : wallPositions) {
        sf::Vector2i gridPos = worldToGrid(wallPos);
        if (isValidCell(gridPos.x, gridPos.y)) {
            grid[gridPos.y][gridPos.x] = false;
        }
    }
}

sf::Vector2i BFSMoveBehavior::worldToGrid(sf::Vector2f worldPos) {
    return sf::Vector2i(
        static_cast<int>(worldPos.x / cellSize),
        static_cast<int>(worldPos.y / cellSize)
    );
}

sf::Vector2f BFSMoveBehavior::gridToWorld(sf::Vector2i gridPos) {
    return sf::Vector2f(
        gridPos.x * cellSize + cellSize / 2.0f,
        gridPos.y * cellSize + cellSize / 2.0f
    );
}

std::vector<sf::Vector2i> BFSMoveBehavior::findPath(sf::Vector2f start, sf::Vector2f target) {
    sf::Vector2i startGrid = worldToGrid(start);
    sf::Vector2i targetGrid = worldToGrid(target);


    if (!isValidCell(startGrid.x, startGrid.y) || !isValidCell(targetGrid.x, targetGrid.y)) {
        return {};
    }

    if (!isWalkable(startGrid.x, startGrid.y) || !isWalkable(targetGrid.x, targetGrid.y)) {
        return {};
    }


    std::queue<sf::Vector2i> queue;
    std::vector<std::vector<bool>> visited(gridHeight, std::vector<bool>(gridWidth, false));
    std::vector<std::vector<sf::Vector2i>> parent(gridHeight, std::vector<sf::Vector2i>(gridWidth, { -1, -1 }));

    int dx[] = { 0, 0, -1, 1 };
    int dy[] = { -1, 1, 0, 0 };

    queue.push(startGrid);
    visited[startGrid.y][startGrid.x] = true;

    while (!queue.empty()) {
        sf::Vector2i current = queue.front();
        queue.pop();

        if (current.x == targetGrid.x && current.y == targetGrid.y) {
            break;
        }

        for (int i = 0; i < 4; ++i) {
            int newX = current.x + dx[i];
            int newY = current.y + dy[i];

            if (isValidCell(newX, newY) && !visited[newY][newX] && isWalkable(newX, newY)) {
                visited[newY][newX] = true;
                parent[newY][newX] = current;
                queue.push({ newX, newY });
            }
        }
    }

    std::vector<sf::Vector2i> path;
    sf::Vector2i current = targetGrid;

    while (current.x != -1 && current.y != -1) {
        path.push_back(current);
        if (current.x == startGrid.x && current.y == startGrid.y) {
            break;
        }
        current = parent[current.y][current.x];
    }

    std::reverse(path.begin(), path.end());

    return path;
}

bool BFSMoveBehavior::isValidCell(int x, int y) {
    return x >= 0 && x < gridWidth && y >= 0 && y < gridHeight;
}

bool BFSMoveBehavior::isWalkable(int x, int y) {
    return isValidCell(x, y) && grid[y][x];
}