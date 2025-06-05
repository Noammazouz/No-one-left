//-----include section-----
#include <cstdlib>
#include <iostream>
#include "GameController.h"

//-----main section-----
int main()
{
	try
	{
		GameController gameController;
		gameController.newGame();
	}
	catch (const std::exception& generalError)
	{
		std::cerr << "Exception: " << generalError.what() << std::endl;
		return EXIT_FAILURE;
	}
	
	return EXIT_SUCCESS;
}
