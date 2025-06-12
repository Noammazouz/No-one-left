//-----include section-----
#include "Map.h"
#include "ResourcesManager.h"
#include <fstream>
#include <stdlib.h>



void Map::loadFromCSV(std::vector<std::unique_ptr<StaticObject>>& m_staticObj, Player& player)
{
    std::ifstream file("Level1.csv");
    if (!file) { /* error */ return; }

    std::string line;
    while (std::getline(file, line))
    {
        //// parse CSV into: type, textureKey, x, y, w, h
        //if (type == "wall")
        //{
        //    // Create a Wall at (x,y) with size (w,h) and push into staticObjs:
        //    staticObjs.push_back(
        //        std::make_unique<Wall>(
        //            sf::Vector2f(x, y),
        //            ResourcesManager::getInstance().getTexture("back"),
        //            w, h));
        //}
        //else if (type == "player")
        //{
        //    // “spawn,player,x,y,0,0”
        //    player.setPosition({ x, y });
        //}
        
    }
}

//-------------------------------------

const std::vector<sf::Vector2f>& Map::getWallPositions() const 
{
    return m_wallPositions;
}

//-------------------------------------

void SetEnemies()
{

}