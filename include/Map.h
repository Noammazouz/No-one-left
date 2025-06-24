#pragma once 

//-----include section-----
#include <iostream>
#include <vector>
#include <string>
#include "Const.h"
#include "UpdateableObject.h"
#include "StaticObject.h"
#include "Wall.h"

class Player;

//-----class section-----
class Map
{
public:
	Map() = default;
	~Map() = default;
	void loadlevelobj(std::vector<std::unique_ptr<UpdateableObject>>& m_movingObj,
					  std::vector<std::unique_ptr<StaticObject>>& m_staticObj, Player& player);
	void draw();

private:
	void loadFromCSV(std::vector<std::unique_ptr<StaticObject>>& m_staticObj, Player& player);
	void loadEnemies(std::vector<std::unique_ptr<UpdateableObject>>& m_movingObj, std::vector<std::unique_ptr<StaticObject>>& m_staticObj);
	void loadObstacles(std::vector<std::unique_ptr<StaticObject>>& m_staticObj, std::vector<std::unique_ptr<UpdateableObject>>& m_movingObj);
	bool isPositionFree(const sf::FloatRect& newBounds,
		const std::vector<std::unique_ptr<StaticObject>>& staticObj,
		const std::vector<std::unique_ptr<UpdateableObject>>& movingObj);
	std::vector<std::string> m_level;
};