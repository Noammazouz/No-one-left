#pragma once

//-----include section-----
#include <vector>
#include <string>
#include <map>
#include <SFML/Graphics.hpp>

//-----enums section-----
enum Direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

enum ScreenButtons 
{
	START_GAME,
	HELP,
	EXIT
};

enum Present
{
	TIME,
	KILL,
	FREEZE,
	DEFAULT
};

enum GameButtons
{
	PAUSE,
    RESUME,
	_HELP
};

enum ScreenType
{
	START_SCREEN,
	HELP_SCREEN,
	GAME_SCREEN,
	WIN_SCREEN,
	LOSE_SCREEN
};

enum ObjectType
{
	PLAYER,
	SIMPLENEMY,
	SMARTENEMY,
	BFSENEMY,
	BULLET,
	BOMB,
	TREE,
	BUILDING,
	EXPLOSION
};

//-----constants section-----
const int MAP_WIDTH = 5000;
const int MAP_HEIGHT = 5000;
const int START_WINDOW_BUTTONS_NUM = 3;
const int FONT_CHARACTERS_SIZE = 26;
const int END_GAME = 0;
const int NUM_OF_BUTTON = 4;
const int NUM_OF_LIVES = 3;
const int POINT_FOR_ENEMY = 3;
const int ENDING_LEVEL = 25;
const int KILL_ENEMY = 5;
const int NUM_OF_DIRECTION = 4;
const int NUM_OF_EXPLOSION = 5;

const float CHANGE_DIRECTION_TIME = 0.f;
const float BUTTON_WIDTH = 300;
const float BUTTON_HEIGHT = 100;
const float BUTTON_SPACING = 40.f;
const float PLAYER_SPEED = 200.f;
const float ENEMY_SPEED = 125.f;
const float DEFUALT_WIDTH = 32.f;
const float DEFUALT_HEIGHT = 32.f;
const float BOMB_TIME = 4.f;
const float ADDED_TIME = 10.f;
const float WINDOW_RATIO = 0.92f;
const float ROTATION_SPEED = 200.f; //degrees per second

const std::string MENU_MUSIC = "menu";
const std::string GAME_MUSIC = "game";
const std::string RETURN_BUTTON = "return";

const int MAX_BULLETS = 29; //Maximum number of bullets that a gun have.
const int MIN_BOUND_BULLETS = 0; //Minimum number of bullets that a gun have.