//-----include section-----
#include "InfoBar.h"
#include "Enemy.h"

//-----functions section------
//-----------------------------------------------------------------------------
InfoBar::InfoBar()
{
	initializeLives();
	initializeBullets();
	initializeTime();
	initializeNumOfEnemies();
	initializeBombs();
}

//-----------------------------------------------------------------------------
void InfoBar::updateLives(int numberOfLives)
{
	if (numberOfLives < 0) return;
	std::string temp = std::to_string(numberOfLives) + "%";
	m_lifePercentages.setString(":" + temp);
	decreaseLifeLevel(numberOfLives);
}

//-----------------------------------------------------------------------------
void InfoBar::updateNumOfBullets(int BulletsAmount)
{
	std::string temp = std::to_string(BulletsAmount) + "/" + std::to_string(NUM_OF_BULLETS);
	m_amountOfBullets.setString(":" + temp);
}

//-----------------------------------------------------------------------------
void InfoBar::updateNumOfBombs(int AmountOfBombs)
{
	std::string temp = std::to_string(AmountOfBombs) + "/" + std::to_string(NUM_OF_BOMBS);
	m_amountOfBombs.setString(":" + temp);
}

//-----------------------------------------------------------------------------
void InfoBar::updateTime(sf::Time deltaTime)
{
	int minutes = deltaTime.asSeconds() / 60,
		seconds = int(deltaTime.asSeconds()) % 60;
	if (seconds < 0 && minutes < 0)
	{
		minutes = 0;
		seconds = 0;
	}

	std::string temp = std::to_string(minutes) + ":" + std::to_string(seconds);

	m_time.setString(":" + temp);
	
}

//-----------------------------------------------------------------------------
void InfoBar::updateNumOfEnemiesAlive()
{
	std::string temp = std::to_string(Enemy::getNumOfEnemiesAlive()) + "/" + std::to_string(Enemy::getNumOfEnemiesAtTheStart());
	m_enemies.setString(":" + temp);
}

//-----------------------------------------------------------------------------
void InfoBar::initializeLives()
{
	int frameWidth = 33; 
	int frameHeight = 80; 
	for (int i = 0; i < 6; ++i) 
	{
		livesFrames.push_back(sf::IntRect(i * frameWidth, 0, frameWidth, frameHeight));
	}

	m_livesIcon.setTexture(ResourcesManager::getInstance().getTexture(LIFE_ICON));
	m_livesIcon.setTextureRect(livesFrames[5]);
	m_livesIcon.setOrigin(m_livesIcon.getGlobalBounds().width / 2, m_livesIcon.getGlobalBounds().height / 2);
	m_livesIcon.setScale(0.9f, 0.9f); // Adjust scale as needed
	m_livesIcon.setPosition(sf::Vector2f(9, 110));

	m_lifePercentages.setCharacterSize(20);
	m_lifePercentages.setFont(ResourcesManager::getInstance().getFont());
	m_lifePercentages.setFillColor(FONT_COLOR);
	m_lifePercentages.setOutlineColor(sf::Color::Black);
	m_lifePercentages.setOutlineThickness(1);
	m_lifePercentages.setPosition(sf::Vector2f(25, 110));
}

//-----------------------------------------------------------------------------
void InfoBar::initializeBullets()
{
	m_bulletsIcon.setTexture(ResourcesManager::getInstance().getTexture(BULLETS_ICON));
	m_bulletsIcon.setOrigin(m_bulletsIcon.getGlobalBounds().width / 2, m_bulletsIcon.getGlobalBounds().height / 2);
	m_bulletsIcon.setScale(0.1f, 0.1f); // Adjust scale as needed
	m_bulletsIcon.setPosition(sf::Vector2f(19, 175));

	m_amountOfBullets.setCharacterSize(20);
	m_amountOfBullets.setFont(ResourcesManager::getInstance().getFont());
	m_amountOfBullets.setFillColor(FONT_COLOR);
	m_amountOfBullets.setOutlineColor(sf::Color::Black);
	m_amountOfBullets.setOutlineThickness(1);
	m_amountOfBullets.setPosition(sf::Vector2f(34, 170));
}

//-----------------------------------------------------------------------------
void InfoBar::initializeBombs()
{
	m_bombsIcon.setTexture(ResourcesManager::getInstance().getTexture(BOMBS_ICON));
	m_bombsIcon.setOrigin(m_bombsIcon.getGlobalBounds().width / 2, m_bombsIcon.getGlobalBounds().height / 2);
	m_bombsIcon.setPosition(sf::Vector2f(19, 280));

	m_amountOfBombs.setCharacterSize(20);
	m_amountOfBombs.setFont(ResourcesManager::getInstance().getFont());
	m_amountOfBombs.setFillColor(FONT_COLOR);
	m_amountOfBombs.setOutlineColor(sf::Color::Black);
	m_amountOfBombs.setOutlineThickness(1);
	m_amountOfBombs.setPosition(sf::Vector2f(38, 278));
}

//-----------------------------------------------------------------------------
void InfoBar::initializeTime()
{
	m_timeIcon.setTexture(ResourcesManager::getInstance().getTexture(CLOCK_ICON));
	m_timeIcon.setOrigin(m_timeIcon.getGlobalBounds().width / 2, m_timeIcon.getGlobalBounds().height / 2);
	m_timeIcon.setPosition(sf::Vector2f(15, 57));

	m_time.setCharacterSize(20);
	m_time.setFont(ResourcesManager::getInstance().getFont());
	m_time.setFillColor(sf::Color(128, 0, 128));
	m_time.setOutlineColor(sf::Color::Black);
	m_time.setOutlineThickness(1);
	m_time.setPosition(sf::Vector2f(30, 50));
}

//-----------------------------------------------------------------------------
void InfoBar::initializeNumOfEnemies()
{
	m_enemiesIcon.setTexture(ResourcesManager::getInstance().getTexture(ENEMIES_ICON));
	m_enemiesIcon.setOrigin(m_bulletsIcon.getGlobalBounds().width / 2, m_bulletsIcon.getGlobalBounds().height / 2);
	m_enemiesIcon.setScale(0.1f, 0.1f); //Adjust scale as needed
	m_enemiesIcon.setPosition(sf::Vector2f(3, 200));

	m_enemies.setCharacterSize(20);
	m_enemies.setFont(ResourcesManager::getInstance().getFont());
	m_enemies.setFillColor(FONT_COLOR);
	m_enemies.setOutlineColor(sf::Color::Black);
	m_enemies.setOutlineThickness(1);
	m_enemies.setPosition(sf::Vector2f(50, 225));
}

//-----------------------------------------------------------------------------
void InfoBar::draw(sf::RenderWindow& window)
{
	window.draw(m_timeIcon);
	window.draw(m_time);
	window.draw(m_livesIcon);
	window.draw(m_lifePercentages);
	window.draw(m_bulletsIcon);
	window.draw(m_amountOfBullets);
	window.draw(m_enemiesIcon);
	window.draw(m_enemies);
	window.draw(m_amountOfBombs);
	window.draw(m_bombsIcon);
}

//-----------------------------------------------------------------------------
void InfoBar::decreaseLifeLevel(float lifePercentage)
{
    //Assuming batteryFrames.size() is the total number of frames
    int totalFrames = livesFrames.size();
    
    //Calculate the frame index based on the life percentage
    int frameIndex = static_cast<int>((lifePercentage / 100.0f) * totalFrames);

    //Ensure the frame index is within bounds
    frameIndex = std::max(0, std::min(frameIndex, totalFrames - 1));

    //Set the texture rectangle to the calculated frame
    m_livesIcon.setTextureRect(livesFrames[frameIndex]);
}