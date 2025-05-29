#pragma once

#include <vector>
#include <string>


const int HEIGHT = 900;
const int WIDTH = 1602;
const int END_GAME = 0;
const int BOARD_STARTING_X = WIDTH / 5;
const int BOARD_STARTING_Y = HEIGHT / 10;
const float PLAYER_SPEED = 200.f;
const float GUARD_SPEED = 125.f;
const int NUM_OF_BUTTON = 4;
const int NUM_OF_LIVES = 3;
const int POINT_FOR_GUARD = 3;
const int ENDING_LEVEL = 25;
const int KILL_GUARD = 5;
const int NUM_OF_DIRECTION = 4;
const float DEFUALT_WIDTH = 32.f;
const float DEFUALT_HEIGHT = 32.f;
const float BOMB_TIME = 4.f;
const int NUM_OF_EXPLOSION = 5;
const float ADDED_TIME = 10.f;

enum Direction 
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

enum menuButtons 
{
	START_GAME,
	HELP,
	EXIT,
	BACK
};

enum Present
{
	TIME,
	KILL,
	FREEZE,
	DEFAULT
};