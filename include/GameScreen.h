#pragma once

#include "Screen.h"
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
#include "Scoreboard.h"
#include "Explosion.h"

class GameScreen : public Screen
{
public:
	GameScreen();
	~GameScreen() = default;

	void draw(sf::RenderWindow& window) override;
	virtual void activate(sf::Clock& clockin, int& m_currrentScreen) override;
	virtual void run(sf::RenderWindow& window, int& m_currrentScreen) override;
	virtual void handleMouseClick(const sf::Vector2f& clickPos, sf::RenderWindow& window) {};
	virtual void initButtons(GameState buttonAmmout) {};

private:
	//void runLevel();
	//void drawWindow();
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
	//void handleMusicTransition(bool toGameplay);
	void handleMuting();
	void handleSocreboard();
	void handlePresents();
	void removeGuard();
	void addTime();
	void lostWindow();
	void winWindow();
	//void handleKeyPressed(sf::Event::KeyEvent event);



	sf::RenderWindow m_window;
	sf::Time m_timer;
	sf::Sound m_sound;
	Map m_map;
	Player m_player;
	Scoreboard m_scoreboard;

	bool m_win = false;
	std::vector<std::unique_ptr<UpdateableObject>> m_movingObj;
	std::vector<std::unique_ptr<StaticObject>> m_staticObj;
};