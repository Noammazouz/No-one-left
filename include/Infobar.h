#pragma once

//-----include section-----
#include "ResourcesManager.h"
#include "Const.h"
#include <SFML/Graphics.hpp>

//-----class section-----
class InfoBar
{
public:
	InfoBar();
	~InfoBar() = default;

	void updateLives(int numberOfLives);
	void updateNumOfBullets(int BulletsAmount);
	void updateTime(sf::Time deltaTime);
	void updateNumOfEnemiesAlive(); 
	void updateNumOfBombs(int AmountOfBombs);
	void draw(sf::RenderWindow& window);

private:
	void initializeLives();
	void initializeBullets();
	void initializeTime();
	void initializeNumOfEnemies();
	void initializeBombs();
	void decreaseLifeLevel(float lifePercentage);

	sf::Text m_lifePercentages, m_amountOfBullets, m_time, m_enemies, m_amountOfBombs;
	sf::Sprite m_livesIcon, m_bulletsIcon, m_timeIcon, m_enemiesIcon, m_bombsIcon;

	std::vector<sf::IntRect> livesFrames;
};