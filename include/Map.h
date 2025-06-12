#pragma once 

//-----include section-----
#include <iostream>
#include <vector>
#include <string>
#include "Const.h"`
#include "UpdateableObject.h"
#include "StaticObject.h"
#include "Wall.h"

class Player;

//-----class section-----
class Map
{
public:
	Map()=default;
	void loadFromCSV(std::vector<std::unique_ptr<StaticObject>>& m_staticObj, Player& player);
	void draw();

private:
	void SetEnemies();
	std::vector<std::string> m_level;
	int m_rows;
	int m_cols;
};