#pragma once

//-----include section-----
#include <SFML/Graphics.hpp>

//-----class section-----
class Button
{
public:
	Button(sf::RenderWindow& window, const sf::Font& font);

	void draw();
	void update(sf::Time deltaTime);
	void handleInput();

	bool isButtonPressed(int buttonIndex) const;

private:
	static const int BUTTON_WIDTH = 200;
	static const int BUTTON_HEIGHT = 50;

	static const int BUTTON_SPACING = 10;

	static const int BUTTON_X = 100;
	static const int BUTTON_Y = 100;

	static const int BUTTON_TEXT_SIZE = 24;

	static const sf::Color BUTTON_COLOR;
	static const sf::Color BUTTON_HOVER_COLOR;
	static const sf::Color BUTTON_PRESSED_COLOR;
};