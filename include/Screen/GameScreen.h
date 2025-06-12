#pragma once

//-----include section-----
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
#include "CollisionFactory.h"

//-----class section-----
class GameScreen : public Screen
{
public:
	GameScreen();

	void draw(sf::RenderWindow& window) override;
	virtual void activate(sf::Clock& clockin, int& m_currrentScreen) override;
	virtual void run(sf::RenderWindow& window, int& m_currrentScreen) override;
	virtual void handleMouseClick(const sf::Vector2f& clickPos, sf::RenderWindow& window, int& screenState) override;

protected:
	void initButtons() override;

private:
	void move(sf::Clock& clock);
	void handleCollision();
	void setbomb();
	void handleErasing();
	void explosion();
	void calculateScore();
	void setExpoDirection(int index);
	void checkExpo();
	void checkVaildDraw();
	void handleLoadingLevel();
	void handleSocreboard();
	void removeGuard();
	void addTime();
	sf::Vector2f clampViewPosition(const sf::FloatRect& bounds);

	sf::RenderWindow m_window;
	sf::Time m_timer;
	//sf::Clock m_clock;
	sf::Sound m_sound;
	sf::View m_view;
	sf::FloatRect worldBounds;
	Map m_map;
	Player m_player;
	Scoreboard m_scoreboard;

	bool m_win = false;
	bool m_paused = false;
	std::vector<std::unique_ptr<UpdateableObject>> m_movingObj;
	std::vector<std::unique_ptr<StaticObject>> m_staticObj;
};