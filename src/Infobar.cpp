#include "Infobar.h"
#include <iostream>


Infobar::Infobar()
{
	initializeLives();
	initializeBullets();
	initializeTime();
}

//-----------------------------------------------------------------------------
void Infobar::updateLives(int numberOfLives)
{
	std::string temp = std::to_string(numberOfLives) + "%";
	m_lifePercentages.setString(":" + temp);
	decreaseLifeLevel(numberOfLives);
}

//-----------------------------------------------------------------------------
void Infobar::updateNumOfBullets(int BulletsAmount)
{
	std::string temp = std::to_string(BulletsAmount);
	m_BulletsAmount.setString(":" + temp);
}

//-----------------------------------------------------------------------------
void Infobar::updateTime(sf::Time deltaTime)
{
	int minutes = deltaTime.asSeconds() / 60,
		seconds = int(deltaTime.asSeconds()) % 60;

	std::string temp = std::to_string(minutes) + ":" + std::to_string(seconds);

	m_Time.setString(":" + temp);
	
}

//-----------------------------------------------------------------------------
//void Infobar::initializeBattery() {
//	if (!batteryTexture.loadFromFile("path/to/spritesheet.png")) {
//		// Handle error
//	}
//	batterySprite.setTexture(batteryTexture);
//
//	int frameWidth = 50; // Example width
//	int frameHeight = 100; // Example height
//	for (int i = 0; i < 6; ++i) {
//		batteryFrames.push_back(sf::IntRect(i * frameWidth, 0, frameWidth, frameHeight));
//	}
//	batterySprite.setTextureRect(batteryFrames[0]);
//}
//
//void Infobar::decreaseBatteryLevel() {
//	if (currentFrame > 0) {
//		currentFrame--;
//		batterySprite.setTextureRect(batteryFrames[currentFrame]);
//	}
//}

void Infobar::initializeLives()
{
	int frameWidth = 33; 
	int frameHeight = 80; 
	for (int i = 0; i < 6; ++i) 
	{
		livesFrames.push_back(sf::IntRect(i * frameWidth, 0, frameWidth, frameHeight));
	}

	m_livesIcon.setTexture(ResourcesManager::getInstance().getTexture("life"));
	m_livesIcon.setTextureRect(livesFrames[5]);
	m_livesIcon.setOrigin(m_livesIcon.getGlobalBounds().width / 2, m_livesIcon.getGlobalBounds().height / 2);
	m_livesIcon.setScale(0.9f, 0.9f); // Adjust scale as needed
	m_livesIcon.setPosition(sf::Vector2f(9, 100));

	m_lifePercentages.setCharacterSize(20);
	m_lifePercentages.setFont(ResourcesManager::getInstance().getFont());
	m_lifePercentages.setFillColor(sf::Color(128, 0, 128));
	m_lifePercentages.setOutlineColor(sf::Color::Black);
	m_lifePercentages.setOutlineThickness(1);
	m_lifePercentages.setPosition(sf::Vector2f(25, 100));
}
void Infobar::initializeBullets()
{
	m_bulletsIcon.setTexture(ResourcesManager::getInstance().getTexture("bulletIcon"));
	m_bulletsIcon.setOrigin(m_bulletsIcon.getGlobalBounds().width / 2, m_bulletsIcon.getGlobalBounds().height / 2);
	m_bulletsIcon.setScale(0.1f, 0.1f); // Adjust scale as needed
	m_bulletsIcon.setPosition(sf::Vector2f(19, 175));

	m_BulletsAmount.setCharacterSize(20);
	m_BulletsAmount.setFont(ResourcesManager::getInstance().getFont());
	m_BulletsAmount.setFillColor(FONT_COLOR);
	m_BulletsAmount.setOutlineColor(sf::Color::Black);
	m_BulletsAmount.setOutlineThickness(1);
	m_BulletsAmount.setPosition(sf::Vector2f(34, 170));
}

void Infobar::initializeTime()
{
	m_timeIcon.setTexture(ResourcesManager::getInstance().getTexture("clock"));
	m_timeIcon.setOrigin(m_timeIcon.getGlobalBounds().width / 2, m_timeIcon.getGlobalBounds().height / 2);
	m_timeIcon.setPosition(sf::Vector2f(15, 57));


	m_Time.setCharacterSize(20);
	m_Time.setFont(ResourcesManager::getInstance().getFont());
	m_Time.setFillColor(sf::Color(128, 0, 128));
	m_Time.setOutlineColor(sf::Color::Black);
	m_Time.setOutlineThickness(1);
	m_Time.setPosition(sf::Vector2f(30, 50));
}

//-----------------------------------------------------------------------------
void Infobar::draw(sf::RenderWindow& window)
{
	window.draw(m_timeIcon);
	window.draw(m_Time);
	window.draw(m_livesIcon);
	window.draw(m_lifePercentages);
	window.draw(m_bulletsIcon);
	window.draw(m_BulletsAmount);
     // Draw the infobar elements on the window
	// This could include drawing text for lives, bullets, level, and time
	// Example:
	// window.draw(livesText);
	// window.draw(bulletsText);
	// window.draw(levelText);
	// window.draw(timeText);
}

void Infobar::decreaseLifeLevel(float lifePercentage) 
{
    // Assuming batteryFrames.size() is the total number of frames
    int totalFrames = livesFrames.size();
    
    // Calculate the frame index based on the life percentage
    int frameIndex = static_cast<int>((lifePercentage / 100.0f) * totalFrames);

    // Ensure the frame index is within bounds
    frameIndex = std::max(0, std::min(frameIndex, totalFrames - 1));

    // Set the texture rectangle to the calculated frame
    m_livesIcon.setTextureRect(livesFrames[frameIndex]);
}