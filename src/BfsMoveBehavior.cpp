#include "BfsMoveBehavior.h"
#include <iostream>
#include <cmath>
#include <algorithm>

const sf::Time BfsMoveBehavior::PATH_UPDATE_INTERVAL = sf::seconds(0.2f); // Balanced update frequency

BfsMoveBehavior::BfsMoveBehavior(int /*worldWidth*/, int /*worldHeight*/, int /*sectionSize*/, int /*localGridSize*/)
    : sectionSize(50), localGridSize(10), currentHighLevelIndex(0), hasObstaclesSet(false) {
    // Simple initialization - we don't need complex grid setup for collision-based approach
    std::cout << "[BFS] Initialized - using collision-based movement" << std::endl;
}

sf::Vector2f BfsMoveBehavior::Move(sf::Vector2f playerPos, sf::Time /*deltaTime*/, sf::Vector2f enemyPos) {
    // Simple approach: Use direct movement and let collision system handle walls
    // This is much more reliable than complex pathfinding
    
    // Calculate direct direction to player
    sf::Vector2f direction = playerPos - enemyPos;
    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    
    // If we're close enough, don't move
    if (distance < 50.0f) {
        return sf::Vector2f(0.0f, 0.0f);
    }
    
    // Return normalized direction - collision system will handle walls
    if (distance > 0.0f) {
        return sf::Vector2f(direction.x / distance, direction.y / distance);
    }
    
    return sf::Vector2f(0.0f, 0.0f);
}

// Note: Obstacle management functions removed 
// BFS now uses collision-based wall avoidance instead of pathfinding

sf::Vector2i BfsMoveBehavior::worldToSection(sf::Vector2f worldPos) {
    // Ensure positive coordinates and proper bounds
    int sectionX = static_cast<int>(std::max(0.0f, worldPos.x) / sectionSize);
    int sectionY = static_cast<int>(std::max(0.0f, worldPos.y) / sectionSize);
    
    // Clamp to valid range
    sectionX = std::max(0, std::min(highLevelWidth - 1, sectionX));
    sectionY = std::max(0, std::min(highLevelHeight - 1, sectionY));
    
    return sf::Vector2i(sectionX, sectionY);
}

sf::Vector2i BfsMoveBehavior::worldToLocalGrid(sf::Vector2f worldPos) {
    sf::Vector2i section = worldToSection(worldPos);
    sf::Vector2f sectionOrigin(section.x * sectionSize, section.y * sectionSize);
    sf::Vector2f localPos = worldPos - sectionOrigin;

    int localCellSize = sectionSize / localGridSize;
    if (localCellSize <= 0) localCellSize = 1; // Prevent division by zero
    
    int localX = static_cast<int>(std::max(0.0f, localPos.x) / localCellSize);
    int localY = static_cast<int>(std::max(0.0f, localPos.y) / localCellSize);
    
    // Clamp to local grid bounds
    localX = std::max(0, std::min(localGridSize - 1, localX));
    localY = std::max(0, std::min(localGridSize - 1, localY));
    
    return sf::Vector2i(localX, localY);
}

sf::Vector2f BfsMoveBehavior::sectionToWorld(sf::Vector2i sectionPos) {
    return sf::Vector2f(
        sectionPos.x * sectionSize + sectionSize / 2.0f,
        sectionPos.y * sectionSize + sectionSize / 2.0f
    );
}

sf::Vector2f BfsMoveBehavior::localGridToWorld(sf::Vector2i localPos, sf::Vector2i sectionPos) {
    int localCellSize = sectionSize / localGridSize;
    if (localCellSize <= 0) localCellSize = 1; // Prevent issues
    
    sf::Vector2f sectionOrigin(sectionPos.x * sectionSize, sectionPos.y * sectionSize);

    return sf::Vector2f(
        sectionOrigin.x + localPos.x * localCellSize + localCellSize / 2.0f,
        sectionOrigin.y + localPos.y * localCellSize + localCellSize / 2.0f
    );
}

std::vector<sf::Vector2i> BfsMoveBehavior::findHighLevelPath(sf::Vector2f start, sf::Vector2f target) {
    sf::Vector2i startSection = worldToSection(start);
    sf::Vector2i targetSection = worldToSection(target);

    std::cout << "[BFS] Finding high-level path from (" << startSection.x << ", " << startSection.y 
              << ") to (" << targetSection.x << ", " << targetSection.y << ")" << std::endl;

    if (!isValidSection(startSection.x, startSection.y) ||
        !isValidSection(targetSection.x, targetSection.y)) {
        std::cout << "[BFS] Invalid start or target section!" << std::endl;
        return {};
    }

    // If start and target are in same section, return empty path (already there)
    if (startSection.x == targetSection.x && startSection.y == targetSection.y) {
        std::cout << "[BFS] Start and target in same section" << std::endl;
        return {};
    }

    // BFS between sections
    std::queue<sf::Vector2i> queue;
    std::vector<std::vector<bool>> visited(highLevelHeight, std::vector<bool>(highLevelWidth, false));
    std::vector<std::vector<sf::Vector2i>> parent(highLevelHeight, std::vector<sf::Vector2i>(highLevelWidth, { -1, -1 }));

    int dx[] = { 0, 0, -1, 1, -1, -1, 1, 1 }; // 8-directional for sections
    int dy[] = { -1, 1, 0, 0, -1, 1, -1, 1 };

    queue.push(startSection);
    visited[startSection.y][startSection.x] = true;

    bool pathFound = false;
    while (!queue.empty()) {
        sf::Vector2i current = queue.front();
        queue.pop();

        if (current.x == targetSection.x && current.y == targetSection.y) {
            pathFound = true;
            break;
        }

        for (int i = 0; i < 8; ++i) {
            int newX = current.x + dx[i];
            int newY = current.y + dy[i];

            if (isValidSection(newX, newY) && !visited[newY][newX] && isSectionWalkable(newX, newY)) {
                visited[newY][newX] = true;
                parent[newY][newX] = current;
                queue.push({ newX, newY });
            }
        }
    }

    if (!pathFound) {
        std::cout << "[BFS] No high-level path found!" << std::endl;
        return {};
    }

    // Reconstruct path
    std::vector<sf::Vector2i> path;
    sf::Vector2i current = targetSection;

    while (current.x != -1 && current.y != -1) {
        path.push_back(current);
        if (current.x == startSection.x && current.y == startSection.y) {
            break;
        }
        current = parent[current.y][current.x];
    }

    std::reverse(path.begin(), path.end());

    // Don't remove starting section - we need it for proper pathfinding
    std::cout << "[BFS] High-level path found with " << path.size() << " sections" << std::endl;
    return path;
}

std::vector<sf::Vector2i> BfsMoveBehavior::findLowLevelPath(sf::Vector2f start, sf::Vector2f target, sf::Vector2i section) {
    if (!isValidSection(section.x, section.y)) {
        std::cout << "[BFS] Invalid section for low-level pathfinding" << std::endl;
        return {};
    }

    sf::Vector2i startLocal = worldToLocalGrid(start);
    sf::Vector2i targetLocal = worldToLocalGrid(target);

    // Ensure coordinates are within bounds
    startLocal.x = std::max(0, std::min(localGridSize - 1, startLocal.x));
    startLocal.y = std::max(0, std::min(localGridSize - 1, startLocal.y));
    targetLocal.x = std::max(0, std::min(localGridSize - 1, targetLocal.x));
    targetLocal.y = std::max(0, std::min(localGridSize - 1, targetLocal.y));

    // If start and target are the same, return empty path
    if (startLocal.x == targetLocal.x && startLocal.y == targetLocal.y) {
        return {};
    }

    // BFS within section
    std::queue<sf::Vector2i> queue;
    std::vector<std::vector<bool>> visited(localGridSize, std::vector<bool>(localGridSize, false));
    std::vector<std::vector<sf::Vector2i>> parent(localGridSize, std::vector<sf::Vector2i>(localGridSize, { -1, -1 }));

    int dx[] = { 0, 0, -1, 1 };
    int dy[] = { -1, 1, 0, 0 };

    queue.push(startLocal);
    visited[startLocal.y][startLocal.x] = true;

    bool pathFound = false;
    while (!queue.empty()) {
        sf::Vector2i current = queue.front();
        queue.pop();

        if (current.x == targetLocal.x && current.y == targetLocal.y) {
            pathFound = true;
            break;
        }

        for (int i = 0; i < 4; ++i) {
            int newX = current.x + dx[i];
            int newY = current.y + dy[i];

            if (isValidLocalCell(newX, newY) && !visited[newY][newX] &&
                sections[section.y][section.x]->localGrid[newY][newX]) {
                visited[newY][newX] = true;
                parent[newY][newX] = current;
                queue.push({ newX, newY });
            }
        }
    }

    if (!pathFound) {
        std::cout << "[BFS] No low-level path found in section (" << section.x << ", " << section.y << ")" << std::endl;
        return {};
    }

    // Reconstruct path
    std::vector<sf::Vector2i> path;
    sf::Vector2i current = targetLocal;

    while (current.x != -1 && current.y != -1) {
        path.push_back(current);
        if (current.x == startLocal.x && current.y == startLocal.y) {
            break;
        }
        current = parent[current.y][current.x];
    }

    std::reverse(path.begin(), path.end());

    // Remove starting position
    if (!path.empty()) {
        path.erase(path.begin());
    }

    return path;
}

bool BfsMoveBehavior::isValidSection(int x, int y) {
    return x >= 0 && x < highLevelWidth && y >= 0 && y < highLevelHeight;
}

bool BfsMoveBehavior::isSectionWalkable(int x, int y) {
    return isValidSection(x, y) && sections[y][x]->isWalkable;
}

bool BfsMoveBehavior::isValidLocalCell(int x, int y) {
    return x >= 0 && x < localGridSize && y >= 0 && y < localGridSize;
}

sf::Vector2f BfsMoveBehavior::findSectionEdgePoint(sf::Vector2i fromSection, sf::Vector2i toSection) {
    // Calculate direction from current section to target section
    sf::Vector2i direction(toSection.x - fromSection.x, toSection.y - fromSection.y);
    
    // Normalize direction to unit values (-1, 0, 1)
    if (direction.x != 0) direction.x = direction.x > 0 ? 1 : -1;
    if (direction.y != 0) direction.y = direction.y > 0 ? 1 : -1;
    
    // Get the bounds of the current section in world coordinates
    sf::Vector2f sectionOrigin(fromSection.x * sectionSize, fromSection.y * sectionSize);
    sf::Vector2f sectionEnd((fromSection.x + 1) * sectionSize, (fromSection.y + 1) * sectionSize);
    
    // Find the edge point based on direction
    sf::Vector2f edgePoint;
    
    if (direction.x > 0) {
        // Moving right - use right edge
        edgePoint.x = sectionEnd.x - sectionSize * 0.1f; // Slightly inside the section
    } else if (direction.x < 0) {
        // Moving left - use left edge
        edgePoint.x = sectionOrigin.x + sectionSize * 0.1f; // Slightly inside the section
    } else {
        // No horizontal movement - use center
        edgePoint.x = sectionOrigin.x + sectionSize * 0.5f;
    }
    
    if (direction.y > 0) {
        // Moving down - use bottom edge
        edgePoint.y = sectionEnd.y - sectionSize * 0.1f; // Slightly inside the section
    } else if (direction.y < 0) {
        // Moving up - use top edge
        edgePoint.y = sectionOrigin.y + sectionSize * 0.1f; // Slightly inside the section
    } else {
        // No vertical movement - use center
        edgePoint.y = sectionOrigin.y + sectionSize * 0.5f;
    }
    
    std::cout << "[BFS] Edge point for direction (" << direction.x << ", " << direction.y 
              << ") is (" << edgePoint.x << ", " << edgePoint.y << ")" << std::endl;
    
    return edgePoint;
}
