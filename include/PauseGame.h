#pragma once

#include "Menu.h"

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