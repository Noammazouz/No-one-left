#pragma once

//-----include section-----
#include "Menu.h"

//-----class section-----
class PauseGame : public Menu
{
public:
	PauseGame() = default;
	~PauseGame() = default;

	// Initialize the game
	void initialize();

	// Run the game loop
	void run();
};