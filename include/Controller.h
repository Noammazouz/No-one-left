#pragma once

//-----include section-----
#include <vector> 
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Screen.h"
#include "StartScreen.h"
#include "HelpScreen.h"
#include "GamePlay.h"
#include "WinScreen.h"
#include "LoseScreen.h"

//-----class section-----
class Controller
{
public:
	Controller();
	~Controller() = default;

	void run();
	
private:
	void initScreen();

	sf::RenderWindow m_window;;
	std::vector<std::unique_ptr<Screen>> m_screens;
	int m_currentScreen;
};
