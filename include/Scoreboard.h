#pragma once
#include "ResourcesManager.h"

#include <SFML/Graphics.hpp>


class Scoreboard
{
public:
	Scoreboard();
	void updateLives(int numberOfLives);
	sf::Text getLives() const;
	void updateScore(int Score);
	sf::Text getScore() const;
	void updateLevel(int numberOfLevel);
	sf::Text getLevel() const;
	void updateTime(sf::Time Timer);
	sf::Text getTime() const;

private:
	sf::Text m_numberOfLives, m_numberOfCheeses, m_Score, m_numberOfKeys, m_Level, m_Time;
};