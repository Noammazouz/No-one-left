#pragma once

//-----include section-----
#include "Const.h"
#include "ResourcesManager.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cstdlib>
#include <string>
#include <cctype>
#include <fstream>
#include <memory>
#include <vector>

//-----class section-----
class Button
{
public:
	Button() = default;	
	Button(std::string buttonType, sf::Vector2f pos);
	~Button() = default;

	sf::FloatRect getBounds() const;
	void draw(sf::RenderWindow& window);
  
private:
	void setSprite(sf::Vector2f pos);
	std::string m_buttonType;
	sf::Sprite m_buttonSprite;
	sf::Vector2f m_position;
	sf::Vector2f m_size;
};