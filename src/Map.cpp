//-----include section-----
#include "Map.h"
#include "ResourcesManager.h"
#include <fstream>
#include <sstream>
#include <stdlib.h>

//-----functions section------
//-----------------------------------------------------------------------------
void Map::loadFromCSV(std::vector<std::unique_ptr<StaticObject>>& m_staticObj, Player& player)
{
    std::ifstream file("Level1.csv");
    if (!file.is_open()) {
        std::cerr << "[ERROR] Cannot open " << "Level1" << "\n";
        return;
    }

    auto trim = [&](std::string s) {
        // remove leading/trailing whitespace (including '\r')
        while (!s.empty() && std::isspace((unsigned char)s.front())) s.erase(s.begin());
        while (!s.empty() && std::isspace((unsigned char)s.back()))  s.pop_back();
        return s;
        };

    std::string line;
    bool firstLine = true;
    while (std::getline(file, line)) {
        line = trim(line);
        if (line.empty()) continue;

        // split on commas into tokens
        std::vector<std::string> tokens;
        {
            std::istringstream ss(line);
            std::string field;
            while (std::getline(ss, field, ',')) {
                tokens.push_back(trim(field));
            }
        }

        // skip the header row
        if (firstLine && tokens.size() > 0 && tokens[0] == "type") {
            firstLine = false;
            continue;
        }
        firstLine = false;

        if (tokens.size() != 6) {
            std::cerr << "[WARN] expected 6 fields but got "
                << tokens.size() << " in: " << line << "\n";
            continue;
        }

        // now tokens = { type, key, sx, sy, sw, sh }
        float x = std::stof(tokens[2]);
        float y = std::stof(tokens[3]);
        float w = std::stof(tokens[4]);
        float h = std::stof(tokens[5]);

        if (tokens[0] == "wall") {
            ResourcesManager& res = ResourcesManager::getInstance();
            m_staticObj.emplace_back(
                std::make_unique<Wall>(
                    res.getTexture(tokens[1]), // textureKey
                    sf::Vector2f(x, y),
                    w, h
                )
            );
        }
        // … handle other types …
    }
}
    //std::ifstream file("Level1.csv");
    //if (!file) { /* error */ return; }

    //std::string line;
    //while (std::getline(file, line))
    //{
    //    //// parse CSV into: type, textureKey, x, y, w, h
    //    //if (type == "wall")
    //    //{
    //    //    // Create a Wall at (x,y) with size (w,h) and push into staticObjs:
    //    //    staticObjs.push_back(
    //    //        std::make_unique<Wall>(
    //    //            sf::Vector2f(x, y),
    //    //            ResourcesManager::getInstance().getTexture("back"),
    //    //            w, h));
    //    //}
    //    //else if (type == "player")
    //    //{
    //    //    // “spawn,player,x,y,0,0”
    //    //    player.setPosition({ x, y });
    //    //}
    //    
    //}

//-----------------------------------------------------------------------------
void Map::SetEnemies()
{}