#pragma once

//-----include section-----
#include <vector> 
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Screen.h"
#include "StartScreen.h"
#include "HelpScreen.h"
#include "PauseGame.h"
#include "GameScreen.h"

//-----class section-----
class Controller
{
public:
	Controller();
	void run();
	
private:
	void initScreen();

	sf::RenderWindow m_window;;
	std::vector<std::unique_ptr<Screen>> m_screens;
	int m_currentScreen;
};
