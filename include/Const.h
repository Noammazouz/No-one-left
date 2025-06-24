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

enum LoseScreenButtons
{
	HOME = 1
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
	OBSTACLE1,
	OBSTACLE2,
	OBSTACLE3,
	BULLET,
	BOMB,
	TREE,
	BUILDING,
	EXPLOSION
};

enum  BulletOwner
{
	ENEMY = 1
};

enum WinScreenButoons
{
	_EXIT = 1
};

//-----constants section-----

//---------int const----------------------------------------
const int MAP_WIDTH = 5000;
const int MAP_HEIGHT = 5000;
const int SECTION_SIZE = 100;
const int LOCAL_GRID_SIZE = 10;
const int START_WINDOW_BUTTONS_NUM = 3;
const int FONT_CHARACTERS_SIZE = 26;
const int END_GAME = 0;
const int NUM_OF_BUTTON = 4;
const int NUM_OF_LIVES = 100;
const int POINT_FOR_ENEMY = 3;
const int ENDING_LEVEL = 25;
const int KILL_ENEMY = 5;
const int NUM_OF_DIRECTION = 4;
const int NUM_OF_EXPLOSION = 5;
const int NUM_OF_DIRECTIONS = 8;
const int NUM_OF_BULLETS = 29;
const int ONE_DIRECTION_BULLET = 1;
const int ALL_DIRECTIONS_BULLETS = 8;
const int NUM_OF_STUPID_ENEMY = 10;
const int NUM_OF_SMART_ENEMY = 5;
const int MAX_BULLETS = 29; //Maximum number of bullets that a gun have.
const int MIN_BOUND_BULLETS = 0; //Minimum number of bullets that a gun have.
const int PLAYER_HEIGHT_53 = 53; //Height of the player sprite - right now this is the height of the player sprite for checking it.
const int PLAYER_WIDTH_50 = 50; //Width of the player sprite - right now this is the height of the player sprite for checking it.
const int OBJECT_HEIGHT = 32; //Height of the player sprite.
const int OBJECT_WIDTH = 25; //Width of the player sprite.

//------------------float const--------------------------------------------------
const float PLAYER_FRAME_TIME = 0.1f; //seconds per frame for the player animation
const float CHANGE_DIRECTION_TIME = 0.f;
const float PLAYER_SPEED = 250.f;
const float ENEMY_SPEED = 125.f;
const float DEFUALT_WIDTH = 32.f;
const float DEFUALT_HEIGHT = 32.f;
const float BOMB_TIME = 4.f;
const float REMOVE_TIME = 10.f;
const float WINDOW_RATIO = 0.92f;
const float ROTATION_SPEED = 135.f; //degrees per second.

//---------------music and sound effects const--------------------------------------
const std::string MENU_MUSIC = "menu";
const std::string GAME_MUSIC = "game";
const std::string LOSING_SOUND = "death";

//-----------------buttons const----------------------------------------
const std::string RETURN_BUTTON = "return";
const std::string PAUSE_BUTTON = "pause";
const std::string RESUME_BUTTON = "resume";
const std::string HELP_MENU_BUTTON_FOR_PAUSE = "help game screen";
const std::string GAME_NAME = "No One Left";
const std::string START_NEW_GAME_BUTTON = "start game";
const std::string START_MENU_BUTTON = "start menu";
const std::string EXIT_BUTTON = "exit";
const std::string HELP_MENU_BUTTON = "help";

//----------------player and enemy sprite sheets--------------------------------
const std::string PLAYER_RIFLE = "player_rifle";
const std::string PLAYER_MACHINE_GUN = "player_machine_gun";
const std::string PLAYER_BAZOOKA = "player_bazooka";
const std::string SIMPLE_ENEMY_MACHINE_GUN = "simple_enemy_machine_gun";

//----------------warning const---------------------------------------------------
const std::string STARIC_OBLECTS_WARNING = "[WARN] No static objects were loaded are you sure your CSV has entries?\n";

//---------------background const------------------------------------
const std::string START_SCREEN_BACKGROUND = "startScreen";
const std::string GAME_BACKGROUND = "background";
const std::string HELP_SCREEN_BACKGROUND = "help screen";
const std::string LOSE_SCREEN_BACKGROUND = "game over";
const std::string WIN_SCREEN_BACKGROUND = "winning screen";

//---------------infobar icons const--------------------------
const std::string LIFE_ICON = "life";
const std::string BULLETS_ICON = "bulletIcon";
const std::string CLOCK_ICON = "clock";

//-----------------color const---------------------------------------
const sf::Color FONT_COLOR = sf::Color(128, 0, 128);

//----------------vector2f const-------------------------------------
const sf::Vector2f FIRST_PLAYER_POSITION(2500.f, 100.f); //Initial position of the player.
