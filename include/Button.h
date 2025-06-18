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

	/*sf::Vector2f getPosition() const;
	void setPosition(int place);*/

	/*sf::Vector2f getSize() const;*/
	//void setSprite(int size, sf::Vector2f pos);
	sf::FloatRect getBounds() const;
	/*const std::string getButtonType() const;
	sf::RectangleShape makeButtonRectangle() const;*/
	void draw(sf::RenderWindow& window);
  
private:
	void setSprite(sf::Vector2f pos);
	std::string m_buttonType;
	sf::Sprite m_buttonSprite;
	sf::Vector2f m_position;
	sf::Vector2f m_size;
};