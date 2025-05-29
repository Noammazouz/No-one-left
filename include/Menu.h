#pragma once 
#include <vector>
#include <SFML/Graphics.hpp>

class Menu
{
public:
	Menu() = default;
	void draw();

private:
	bool m_help_window = false;
	std::vector<sf::Sprite> m_buttons;

	void drawWindow(sf::RenderWindow& window);
	void handleMouseEvents(sf::RenderWindow& window, const sf::Event::MouseButtonEvent& event);
	void drawHelp(sf::RenderWindow& window);
	void handleMuting();
};