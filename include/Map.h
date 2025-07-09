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
	void loadEnemies(std::vector<std::unique_ptr<UpdateableObject>>& m_movingObj, std::vector<std::unique_ptr<StaticObject>>& m_staticObj, Player& player);
	void loadObstacles(std::vector<std::unique_ptr<StaticObject>>& m_staticObj,
					   std::vector<std::unique_ptr<UpdateableObject>>& m_movingObj,
					   Player& player);
	void loadPresents(std::vector<std::unique_ptr<StaticObject>>& m_staticObj, std::vector<std::unique_ptr<UpdateableObject>>& m_movingObj, Player& player);
	bool isPositionFree(const sf::FloatRect& newBounds,
						const std::vector<std::unique_ptr<StaticObject>>& staticObjs,
						const std::vector<std::unique_ptr<UpdateableObject>>& movingObjs,
						const Player& player);
	std::vector<std::string> m_level;
};