#pragma once 

//-----include section-----
#include <iostream>
#include <vector>
#include <string>
#include "Const.h"
#include "UpdateableObject.h"
#include "StaticObject.h"
#include "Wall.h"

//-----forward declaration section-----
class Player;
class GamePlay;

//-----class section-----
class Map
{
public:
	Map() = default;
	~Map() = default;
	void loadlevelobj(std::vector<std::unique_ptr<UpdateableObject>>& m_movingObj,
					  std::vector<std::unique_ptr<StaticObject>>& m_staticObj, Player& player, GamePlay* gamePlay);

private:
	void loadFromCSV(std::vector<std::unique_ptr<StaticObject>>& m_staticObj, Player& player, GamePlay* gamePlay);
	void loadEnemies(std::vector<std::unique_ptr<UpdateableObject>>& m_movingObj, GamePlay* gamePlay);
	void loadObstacles(std::vector<std::unique_ptr<StaticObject>>& m_staticObj, GamePlay* gamePlay);
	std::vector<std::string> m_level;
};