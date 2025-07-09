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
	SIMPLEENEMY,
	SMARTENEMY,
	BFSENEMY,
	BOMB,
	OBSTACLE1,
	OBSTACLE2,
	OBSTACLE3,
	BULLET,
	TREE,
	BUILDING,
	EXPLOSION,
	PROJECTILE,
	RIFLE,
	MACHINE_GUN,
	BAZOOKA,
	MEDKIT,
	REMOVE_ENEMY,
	REMOVE_TIME
};

enum BulletOwner
{
	_PLAYER,
	ENEMY
};

enum WinScreenButoons
{
	_EXIT = 1
};

enum SectionType
{
	FIRST_SECTION,
	SECOND_SECTION,
	THIRD_SECTION
};

//----------constants section----------
//-----int const section-----
const int MAP_WIDTH = 5000;
const int MAP_HEIGHT = 5000;
const int START_WINDOW_BUTTONS_NUM = 3;
const int FONT_CHARACTERS_SIZE = 26;
const int END_GAME = 0;
const int NUM_OF_BUTTON = 4;
const int NUM_OF_LIVES = 100;
const int NUM_OF_DIRECTION = 4;
const int NUM_OF_EXPLOSION = 5;
const int NUM_OF_DIRECTIONS = 8;
const int NUM_OF_BULLETS = 29;
const int NUM_OF_STUPID_ENEMY = 5;
const int NUM_OF_SMART_ENEMY = 10;
const int NUM_OF_BOMBS = 10; //Maximum number of bullets that a gun have.
const int MIN_BOUND_BULLETS = 0; //Minimum number of bullets that a gun have.
const int OBJECT_HEIGHT = 32; //Height of the player sprite.
const int OBJECT_WIDTH = 25; //Width of the player sprite.
const int BOMB_HEIGHT = 30; //Width of the player sprite.
const int BOMB_WIDTH = 30; //Width of the player sprite.
const int EXPLOSION_DEC_LIVES = 30;
const int PROJECTILE_DAMAGE = 5;
const int NUM_OF_LIFE_OBSTACLE = 3;
const int ADD_LIFE = 20;
const int EXPLOSION_DAMAGE = 20;
const int MIN_BOUND_BOMBS = 0; //Minimum number of bombs that a player can have.
const int NUM_OF_WOPENS = 10;
const int NUM_OF_PRESENTS = 20; //Number of different presents.


//-----float const section-----
const float PLAYER_FRAME_TIME = 0.1f; //seconds per frame for the player animation
const float BOMB_FRAME_TIME = 0.7f; //seconds per frame for the bomb animation
const float CHANGE_DIRECTION_TIME = 0.f;
const float PLAYER_SPEED = 250.f;
const float ENEMY_SPEED = 100.f;
const float BOMB_TIME = 2.5f;
const float TIME_TO_REMOVE = 10.f;
const float WINDOW_RATIO = 0.92f;
const float ROTATION_SPEED = 135.f; //degrees per second.
const float PROJECTILE_SPEED = 750.f;
const float DISTANCE = 90000.0f;
const float FIRE_COOLDOWN = 0.5f;
const float PROJECTILE_AIR_TIME = 1.0f;
const float EXPLOSION_RADIUS = 80.f;
const float EXPLOSION_TIME = 2.f;

//-----music and sound effects const section-----
const std::string MENU_MUSIC = "menu";
const std::string GAME_MUSIC = "game";
const std::string LOSING_SOUND = "death";
const std::string WINNING_SOUND = "win sound effect";
const std::string SHOOTING_SOUND = "shoot";
const std::string EXPLOSION_SOUND = "explosion";
const std::string GAIN_HEALTH_SOUND = "health";
const std::string GAIN_PRESENT_SOUND = "present";

//-----buttons const section-----
const std::string RETURN_BUTTON = "return";
const std::string PAUSE_BUTTON = "pause";
const std::string RESUME_BUTTON = "resume";
const std::string HELP_MENU_BUTTON_FOR_PAUSE = "help game screen";
const std::string GAME_NAME = "No One Left";
const std::string START_NEW_GAME_BUTTON = "start game";
const std::string START_MENU_BUTTON = "start menu";
const std::string EXIT_BUTTON = "exit";
const std::string HELP_MENU_BUTTON = "help";

//-----player and enemy sprite sheets const names section-----
const std::string PLAYER_RIFLE = "player_rifle";
const std::string PLAYER_MACHINE_GUN = "player_machine_gun";
const std::string PLAYER_BAZOOKA = "player_bazooka";
const std::string SIMPLE_ENEMY_RIFLE = "simple_enemy_rifle";
const std::string SMART_ENEMY_RIFLE = "smart_enemy_rifle";
const std::string BFS_ENEMY_RIFLE = "bfs_enemy_rifle";

//-----Items const section-----
const std::string RIFLE_NAME = "rifle";
const std::string MACHINE_GUN_NAME = "machine gun";
const std::string BAZOOKA_NAME = "bazooka";
const std::string BULLETS_NAME = "Bullet";
const std::string MED_KIT_NAME = "medkit";
const std::string REMOVE_ENEMY_NAME = "remove enemy";
const std::string REMOVE_TIME_NAME = "remove time";
 

//-----texture names const section-----
const std::string PROJECTILE_NAME = "projectile";
const std::string BOMB_NAME = "bomb";
const std::string EXPLOSION_NAME = "explosion";
const std::string OBSTACLE1_NAME = "obstacle1";
const std::string OBSTACLE2_NAME = "obstacle2";
const std::string OBSTACLE3_NAME = "obstacle3";
const std::string WALL_NAME = "wall";

//-----warning const section-----
const std::string STARIC_OBJECTS_WARNING = "[WARN] No static objects were loaded are you sure your CSV has entries?\n";

//-----background const section-----
const std::string START_SCREEN_BACKGROUND = "startScreen";
const std::string GAME_BACKGROUND = "background";
const std::string HELP_SCREEN_BACKGROUND = "help screen";
const std::string LOSE_SCREEN_BACKGROUND = "game over";
const std::string WIN_SCREEN_BACKGROUND = "winning screen";

//-----InfoBar icons const section-----
const std::string LIFE_ICON = "life";
const std::string BULLETS_ICON = "bulletIcon";
const std::string CLOCK_ICON = "clock";
const std::string ENEMIES_ICON = "enemeis icon";
const std::string BOMBS_ICON = "bombs icon";

//-----color const section-----
const sf::Color FONT_COLOR = sf::Color(128, 0, 128);

//-----sf::Vector2f const section-----
const sf::Vector2f FIRST_PLAYER_POSITION(2500.f, 100.f); //Initial position of the player.
const sf::Vector2f DEFAULT_BOMB_DIRECTION(1.f, 1.f); //Default direction of the bomb.
const sf::Vector2f DEFAULT_VECTOR(0.f, 0.f); //Default direction of the projectile.

//-----Font const section-----
const std::string FONT_NAME = "ARCADE_N.TTF"; //Name of the font file.

//-----File Name const section-----
const std::string HELP_FILE_NAME = "help.txt"; //Name of the help file.

//-----Shooting Time const section-----
const sf::Time SHOOTING_TIME_RIFLE = sf::seconds(0.2f); //Time between shots in seconds for rifle.
const sf::Time SHOOTING_TIME_MACHINE_GUN = sf::seconds(0.1f); //Time between shots in seconds for machine gun.
const sf::Time SHOOTING_TIME_BAZOOKA = sf::seconds(0.5f); //Time between shots in seconds for bazooka.