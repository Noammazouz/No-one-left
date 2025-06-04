#pragma once

//-----include section-----
#include <vector> 
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <stack>
#include "Map.h"
#include "Player.h"
#include "Bombs.h"
#include "Enemy.h"
#include "ResourcesManager.h"
#include "Const.h"
#include "UpdateableObject.h"
#include "StaticObject.h"
#include "GameObject.h"
#include "Screen.h"
#include "Scoreboard.h"
#include "Explosion.h"

//-----class section-----
class GameController
{
public:
	GameController();
	void newGame();

private:
	void runLevel();
	void drawWindow();
	void move(sf::Clock& clock);
	void handleCollision();
	void setbomb();
	void handleErasing();
	void explosion();
	void calculateScore();
	void setExpoDirection(int index);
	void resetLevel();
	void checkExpo();
	void checkVaildDraw();
	void handleLoadingLevel(sf::Clock& clock);
	void handleMusicTransition(bool toGameplay);
	void handleMuting();
	void handleSocreboard();
	void handlePresents();
	void removeGuard();
	void addTime();
	void lostWindow();
	void winWindow();
	void handleKeyPressed(sf::Event::KeyEvent event);


	sf::RenderWindow m_window;
	sf::Time m_timer;
	sf::Sound m_sound;
	Map m_board;
	Player m_player;
	std::stack<Screen> m_screen;
	Scoreboard m_scoreboard;

	int m_level;
	bool m_inGameplay = false;
	bool m_win = false;
	std::vector<std::unique_ptr<UpdateableObject>> m_movingObj;
	std::vector<std::unique_ptr<StaticObject>> m_staticObj;
};
