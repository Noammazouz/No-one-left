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
#include "Enemy.h"
#include "ResourcesManager.h"
#include "Const.h"
#include "UpdateableObject.h"
#include "StaticObject.h"
#include "GameObject.h"
#include "Infobar.h"
#include "CollisionFactory.h"
#include "Projectile.h"
#include "Bomb.h"
#include "Explosion.h"

//-----class section-----
class GamePlay : public Screen
{
public:
	GamePlay();

	void draw(sf::RenderWindow& window) override;
	virtual void activate(sf::Clock& clockin, int& m_currrentScreen) override;
	virtual void run(sf::RenderWindow& window, int& m_currrentScreen) override;
	virtual void handleMouseClick(const sf::Vector2f& clickPos, int& screenState) override;
	void addProjectile(const sf::Vector2f& pos,
					   std::vector<sf::Vector2f> directions,
					   BulletOwner owner,
					   const std::string& weaponName);
	void addExplosion(const sf::Vector2f& pos);
	void addBomb(const sf::Vector2f& pos);
	void playPresentSound();
	void playMedkitSound();
	void playHitSound();
	void removeEnemy();
	void decTime();

protected:
	void initButtons() override;

private:
	void move(sf::Clock& clock);
	void handleCollision();
	void handleErasing();
	void setExpoDirection(int index);
	void handleLoadingLevel();
	void handleInfobar();
	void resetGame();
	void resetGameOverStates();
	void handleWinState(int& m_currentScreen);
	void handleDeathState(int& m_currentScreen);
	sf::Vector2f clampViewPosition(const sf::FloatRect& bounds);

	sf::RenderWindow m_window;
	sf::Time m_stopwatch;
	sf::Sound m_sound;
	sf::View m_view;
	sf::FloatRect worldBounds;
	Map m_map;
	Player m_player;
	Infobar m_infoBar;

	bool m_paused = false;
	bool m_newGame = false;
	bool m_winStateHandled = false;
	std::vector<std::unique_ptr<UpdateableObject>> m_movingObj;
	std::vector<std::unique_ptr<StaticObject>> m_staticObj;
};