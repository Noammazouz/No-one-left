#pragma once

//-----include section-----
#include <vector>
#include <string>
#include <map>

//-----enums section-----
enum Direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

//enum ScreenButtons 
//{
//	START_GAME,
//	HELP,
//	EXIT,
//	BACK
//};

enum Present
{
	TIME,
	KILL,
	FREEZE,
	DEFAULT
};

enum GameState
{
	START,
	HELP,
	GAME,
	PUASE
};

enum ScreenType
{
	START_SCREEN,
	HELP_SCREEN,
	GAME_SCREEN,
	END_SCREEN
};

enum ObjectType
{
	PLAYER,
	ENEMY,
	BULLET,
	BOMB,
	TREE,
	BUILDING,
	EXPLOSION
};

//-----constants section-----
const int WINDOW_HEIGHT = 900;
const int WINDOW_WIDTH = 1602;
const int MAP_WIDTH = 5000;
const int MAP_HEIGHT = 5000;
const float BUTTON_WIDTH = 300;
const float BUTTON_HEIGHT = 100;
const float BUTTON_SPACING = 40.f;
const int START_WINDOW_BUTTONS_NUM = 3;
const int FONT_CHARACTERS_SIZE = 26;
const int END_GAME = 0;
const int BOARD_STARTING_X = WINDOW_WIDTH / 5;
const int BOARD_STARTING_Y = WINDOW_HEIGHT / 10;
const float PLAYER_SPEED = 200.f;
const float ENEMY_SPEED = 125.f;
const int NUM_OF_BUTTON = 4;
const int NUM_OF_LIVES = 3;
const int POINT_FOR_ENEMY = 3;
const int ENDING_LEVEL = 25;
const int KILL_ENEMY = 5;
const int NUM_OF_DIRECTION = 4;
const float DEFUALT_WIDTH = 32.f;
const float DEFUALT_HEIGHT = 32.f;
const float BOMB_TIME = 4.f;
const int NUM_OF_EXPLOSION = 5;
const float ADDED_TIME = 10.f;
const float WINDOW_RATIO = 0.92f;
const std::map<GameState, std::vector<std::string> > GAME_BUTTONS = 
{
	{START, {"Start", "Help", "Exit"}},
	{HELP, {"Back"}},
	{GAME, {"Pause"}},
	{PUASE, {"Resume", "Help"}}
};


//-----------------------------------------------------------------------------
//std::string getStartMenuButtonStringByChar(char buttonType)
//{
//	switch (buttonType)
//	{
//	case 'N':
//		return NEW_GAME_BUTTON_NAME;
//	case 'H':
//		return HELP_BUTTON_NAME;
//	case 'E':
//		return EXIT_BUTTON_NAME;
//	}
//}


//-----------------------------------------------------------------------------
//This function check if the mouse is in the bounds of the button or the cell
//that called to this function.
//bool CheckLimits(const sf::Vector2f mousePosition,
//	const sf::Vector2f buttonCellPos,
//	const sf::Vector2f buttonCellSize)
//{
//	if (buttonCellPos.x < mousePosition.x && buttonCellPos.x + buttonCellSize.x > mousePosition.x &&
//		buttonCellPos.y < mousePosition.y && buttonCellPos.y + buttonCellSize.y > mousePosition.y)
//	{
//		return true;
//	}
//
//	return false;
//}
