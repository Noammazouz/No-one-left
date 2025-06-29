#pragma once

//-----include section-----
#include "ResourcesManager.h"
#include "Const.h"
#include <SFML/Graphics.hpp>

//-----class section-----
class Infobar
{
public:
	Infobar();
	~Infobar() = default;

	void updateLives(int numberOfLives);
	void updateNumOfBullets(int BulletsAmount);
	void updateTime(sf::Time deltaTime);
	void updateNumOfEnemiesAlive();
	void draw(sf::RenderWindow& window);

private:

	void initializeLives();
	void initializeBullets();
	void initializeTime();
	void initializeNumOfEnemies();
	void decreaseLifeLevel(float lifePercentage);

	sf::Text m_lifePercentages, m_BulletsAmount, m_Time, m_Enemies;
	sf::Sprite m_livesIcon, m_bulletsIcon, m_timeIcon, m_enemiesIcon;

	std::vector<sf::IntRect> livesFrames;
};