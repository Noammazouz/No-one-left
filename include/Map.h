#pragma once 

//-----include section-----
#include <iostream>
#include <vector>
#include <string>
#include "Const.h"`
#include "UpdateableObject.h"
#include "StaticObject.h"
#include "Player.h"

class Player;

//-----class section-----
class Map
{
public:
	Map()=default;
	void loadFromCSV(std::vector<std::unique_ptr<StaticObject>>& m_staticObj, Player& player);
	void draw();
	//const std::vector<sf::Vector2f>& getWallPositions() const;

private:
	std::vector<std::string> m_level;
	//std::vector<sf::Vector2f> m_wallPositions;
	int m_rows;
	int m_cols;
};