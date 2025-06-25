//-----include section-----
#include "Map.h"
#include "ResourcesManager.h"
#include "GamePlay.h"
#include "Player.h"
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <random>
#include "Factory.h"
#include "AxisMoveBehavior.h"
#include "BfsMoveBehavior.h"
#include "RandomMoveBehavior.h"

//-----functions section------
//-----------------------------------------------------------------------------
void Map::loadFromCSV(std::vector<std::unique_ptr<StaticObject>>& m_staticObj, Player& player, GamePlay* gamePlay)
{
    std::ifstream file("Level1_cleaned.csv");
    if (!file.is_open()) 
    {
        throw std::runtime_error("[ERROR] Cannot open Level1.csv");
        return;
    }
    std::string line;
    while (std::getline(file, line))
    {
        // ditch empty lines
        if (line.empty())
            continue;

        // quick check for header
        if (line.rfind("type", 0) == 0)
            continue;

        // turn "wall,wall,123,456" → "wall wall 123 456"
        for (auto& c : line)
            if (c == ',') c = ' ';

        std::istringstream ss(line);
        std::string type, key;
        float x, y;
        if (!(ss >> type >> key >> x >> y))
        {
            std::cerr << "[WARN] bad line: " << line << "\n";
            continue;
        }

        if (type == "wall")
        {
            m_staticObj.emplace_back(
                std::make_unique<Wall>(key, sf::Vector2f{ x,y })
            );
        }
        // … else if for other object-types …
    }

    //player.initialization(FIRST_PLAYER_POSITION, "player_machine_gun");
    player.initialization(FIRST_PLAYER_POSITION, PLAYER_RIFLE);
}

//-----------------------------------------------------------------------------
void Map::loadlevelobj(std::vector<std::unique_ptr<UpdateableObject>>& m_movingObj, 
                       std::vector<std::unique_ptr<StaticObject>>& m_staticObj, Player& player, GamePlay* gamePlay)
{
    m_staticObj.clear();
    m_movingObj.clear();
    loadFromCSV(m_staticObj, player, gamePlay);
    loadEnemies(m_movingObj, m_staticObj, gamePlay);
    loadObstacles(m_staticObj, m_movingObj, gamePlay);
}

//-----------------------------------------------------------------------------
void Map::loadEnemies(std::vector<std::unique_ptr<UpdateableObject>>& m_movingObj, std::vector<std::unique_ptr<StaticObject>>& m_staticObj, GamePlay* gamePlay)
{
    ////random_device is a seed maker.
    ////mt19937 is a random engine.
    //std::mt19937 rng{ std::random_device{}() };
    //float thirdH = MAP_HEIGHT / 3.f;
    ////getting a random x value (can spawn everywhere from left to right)
    //auto randX = [&]()
    //    {
    //        return std::uniform_real_distribution<float>(0.f, MAP_WIDTH)(rng);
    //    };
    //// getting a random y value in a specific third
    //auto randYIn = [&](int region) 
    //    {
    //        return std::uniform_real_distribution<float>
    //            (region * thirdH, (region + 1) * thirdH)(rng);
    //    };
    constexpr float WALL_MARGIN = 50.f;
    constexpr int maxTries = 10;

    std::mt19937 rng{ std::random_device{}() };
    float thirdH = MAP_HEIGHT / 3.f;

    std::uniform_real_distribution<float> randX(WALL_MARGIN, MAP_WIDTH - WALL_MARGIN);
    auto randYIn = [&](int region)
        {
            return std::uniform_real_distribution<float>(
                region * thirdH + WALL_MARGIN, (region + 1) * thirdH - WALL_MARGIN)(rng);
        };

    auto& factory = Factory<UpdateableObject>::instance();

    auto tryPlaceEnemy = [&](ObjectType type, int region)
        {
            for (int attempt = 0; attempt < maxTries; ++attempt)
            {
                sf::Vector2f pos{ randX(rng), randYIn(region) };
                auto temp = factory.create(type, pos, gamePlay);
                if (isPositionFree(temp->getBounds(), m_staticObj, m_movingObj))
                {
                    m_movingObj.emplace_back(std::move(temp));
                    break;
                }
            }
        };

    // first third (3 simple + 3 smart)
    for (int i = 0; i < NUM_OF_STUPID_ENEMY; ++i)
    {
        tryPlaceEnemy(ObjectType::BFSENEMY, 0);
        tryPlaceEnemy(ObjectType::SMARTENEMY, 0);
    }

    // second third (1 simple, 2 smart)
    tryPlaceEnemy(ObjectType::SIMPLENEMY, 1);
    for (int i = 0; i < NUM_OF_SMART_ENEMY; ++i)
    {
        tryPlaceEnemy(ObjectType::SMARTENEMY, 1);
    }

    // third third (1 simple, 2 smart, 1 bfs)
    tryPlaceEnemy(ObjectType::SIMPLENEMY, 2);
    tryPlaceEnemy(ObjectType::BFSENEMY, 2);
    for (int i = 0; i < NUM_OF_SMART_ENEMY; ++i)
    {
        tryPlaceEnemy(ObjectType::SMARTENEMY, 2);
    }
}

void Map::loadObstacles(std::vector<std::unique_ptr<StaticObject>>& m_staticObj, std::vector<std::unique_ptr<UpdateableObject>>& m_movingObj, GamePlay* gamePlay)
{
    constexpr float WALL_MARGIN = 50.f;
    constexpr int maxTries = 10;

    std::mt19937 rng{ std::random_device{}() };
    std::uniform_real_distribution<float> randX(WALL_MARGIN, MAP_WIDTH - WALL_MARGIN);
    std::uniform_real_distribution<float> randY(WALL_MARGIN, MAP_HEIGHT - WALL_MARGIN);

    auto& factory = Factory<StaticObject>::instance();

    auto tryPlaceObstacle = [&](ObjectType type)
        {
            for (int attempt = 0; attempt < maxTries; ++attempt)
            {
                sf::Vector2f pos{ randX(rng), randY(rng) };
                auto temp = factory.create(type, pos, gamePlay);
                if (isPositionFree(temp->getBounds(), m_staticObj, m_movingObj))
                {
                    m_staticObj.emplace_back(std::move(temp));
                    break;
                }
            }
        };

    for (int i = 0; i < 20; ++i) tryPlaceObstacle(ObjectType::OBSTACLE1);
    for (int i = 0; i < 20; ++i) tryPlaceObstacle(ObjectType::OBSTACLE2);
    for (int i = 0; i < 20; ++i) tryPlaceObstacle(ObjectType::OBSTACLE3);
}

bool Map::isPositionFree(const sf::FloatRect& newBounds,
    const std::vector<std::unique_ptr<StaticObject>>& staticObjs,
    const std::vector<std::unique_ptr<UpdateableObject>>& movingObjs)
{
    for (const auto& obj : staticObjs)
        if (obj->getBounds().intersects(newBounds))
            return false;

    for (const auto& obj : movingObjs)
        if (obj->getBounds().intersects(newBounds))
            return false;

    return true;
}