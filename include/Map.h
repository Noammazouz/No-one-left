#pragma once 

//-----include section-----
#include <iostream>
#include <vector>
#include <string>
#include "Const.h"
#include "UpdateableObject.h"
#include "StaticObject.h"

class Player;

//-----class section-----
class Map
{
public:
	Map();
	void LoadMap(std::vector<std::unique_ptr<UpdateableObject>>& m_movingObj
		, std::vector<std::unique_ptr<StaticObject>>& m_staticObj, Player& m_player);
	int loadLevel(const int& currStage);

private:
	std::vector<std::string> m_level;
	int m_rows;
	int m_cols;
};