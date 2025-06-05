#pragma once

//-----include section-----
#include "Screen.h"

//-----class section-----
class PauseGame : public Screen
{
public:
	PauseGame() = default;
	~PauseGame() = default;

	// Initialize the game
	void initialize();

	// Run the game loop
	void run();
};