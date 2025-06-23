//-----include section-----
#include "Map.h"
#include "ResourcesManager.h"
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
void Map::loadFromCSV(std::vector<std::unique_ptr<StaticObject>>& m_staticObj, Player& player)
{
    std::ifstream file("Level1.csv");
    if (!file.is_open()) 
    {
        std::cerr << "[ERROR] Cannot open " << "Level1" << "\n";
        return;
    }

    auto trim = [&](std::string s) 
    {
        // remove leading/trailing whitespace (including '\r')
        while (!s.empty() && std::isspace((unsigned char)s.front())) s.erase(s.begin());
        while (!s.empty() && std::isspace((unsigned char)s.back()))  s.pop_back();
        return s;
    };

    std::string line;
    bool firstLine = true;
    while (std::getline(file, line)) 
    {
        line = trim(line);
        if (line.empty()) continue;

        // split on commas into tokens
        std::vector<std::string> tokens;
        {
            std::istringstream ss(line);
            std::string field;
            while (std::getline(ss, field, ',')) 
            {
                tokens.push_back(trim(field));
            }
        }

        // skip the header row
        if (firstLine && tokens.size() > 0 && tokens[0] == "type") 
        {
            firstLine = false;
            continue;
        }
        firstLine = false;

        if (tokens.size() != 6) 
        {
            std::cerr << "[WARN] expected 6 fields but got "
                << tokens.size() << " in: " << line << "\n";
            continue;
        }

        // now tokens = { type, key, sx, sy, sw, sh }
        float x = std::stof(tokens[2]);
        float y = std::stof(tokens[3]);
        float w = std::stof(tokens[4]);
        float h = std::stof(tokens[5]);

        if (tokens[0] == "wall") 
        {
            //ResourcesManager& res = ResourcesManager::getInstance();
            m_staticObj.emplace_back(std::make_unique<Wall>(tokens[1], sf::Vector2f(x, y)));
        }
        // … handle other types …
    }

	player = Player(FIRST_PLAYER_POSITION, "player_machine_gun");
}

//-----------------------------------------------------------------------------
void Map::loadlevelobj(std::vector<std::unique_ptr<UpdateableObject>>& m_movingObj, 
                       std::vector<std::unique_ptr<StaticObject>>& m_staticObj, Player& player)
{
    m_staticObj.clear();
    m_movingObj.clear();
    loadFromCSV(m_staticObj, player);
    loadEnemies(m_movingObj);
    loadObstacles(m_staticObj);
}

//-----------------------------------------------------------------------------
void Map::loadEnemies(std::vector<std::unique_ptr<UpdateableObject>>& m_movingObj)
{
    //random_device is a seed maker.
    //mt19937 is a random engine.
    std::mt19937 rng{ std::random_device{}() };
    float thirdH = MAP_HEIGHT / 3.f;
    //getting a random x value (can spawn everywhere from left to right)
    auto randX = [&]()
        {
            return std::uniform_real_distribution<float>(0.f, MAP_WIDTH)(rng);
        };
    // getting a random y value in a specific third
    auto randYIn = [&](int region) 
        {
            return std::uniform_real_distribution<float>
                (region * thirdH, (region + 1) * thirdH)(rng);
        };
    auto& factory = Factory<UpdateableObject>::instance();
    
    //first third (3 simple enemies)
    for (int i = 0; i < NUM_OF_STUPID_ENEMY; ++i)
    {
        m_movingObj.emplace_back(factory.create(ObjectType::SIMPLENEMY, { randX(), randYIn(0) }));
    }

    //second third (1 simple, 2 smart)
    m_movingObj.emplace_back(factory.create(ObjectType::SIMPLENEMY, { randX(), randYIn(1) }));
    for (int i = 0; i < NUM_OF_SMART_ENEMY; ++i)
    {
        m_movingObj.emplace_back(factory.create(ObjectType::SMARTENEMY, { randX(), randYIn(1) }));
    }
    //third third (1 simple, 2 smart, 1 bfs)
    m_movingObj.emplace_back(factory.create(ObjectType::SIMPLENEMY, { randX(), randYIn(2) }));
    m_movingObj.emplace_back(factory.create(ObjectType::BFSENEMY, { randX(), randYIn(2) }));
    for (int i = 0; i < NUM_OF_SMART_ENEMY; ++i)
    {
        m_movingObj.emplace_back(factory.create(ObjectType::SMARTENEMY, { randX(), randYIn(2) }));
    }
}

void Map::loadObstacles(std::vector<std::unique_ptr<StaticObject>>& m_staticObj)
{
    std::mt19937 rng{ std::random_device{}() };
    std::uniform_real_distribution<float> randX(0.f, MAP_WIDTH);
    std::uniform_real_distribution<float> randY(0.f, MAP_HEIGHT);

    auto& factory = Factory<StaticObject>::instance();

    // e.g. 10 rocks
    for (int i = 0; i < 10; ++i) {
        sf::Vector2f pos{ randX(rng), randY(rng) };
        m_staticObj.emplace_back(
            factory.create(ObjectType::OBSTACLE1, pos));
    }

    // 5 crates
    for (int i = 0; i < 5; ++i) {
        sf::Vector2f pos{ randX(rng), randY(rng) };
        m_staticObj.emplace_back(
            factory.create(ObjectType::OBSTACLE2, pos));
    }

    // 3 barrels
    for (int i = 0; i < 3; ++i) {
        sf::Vector2f pos{ randX(rng), randY(rng) };
        m_staticObj.emplace_back(
            factory.create(ObjectType::OBSTACLE3, pos));
    }
}