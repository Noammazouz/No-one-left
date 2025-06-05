//-----include section-----
#include <cstdlib>
#include <iostream>
#include "Controller.h"

//-----main section-----
int main()
{
	try
	{
		Controller Controller;
		Controller.run();
	}
	catch (const std::exception& generalError)
	{
		std::cerr << "Exception: " << generalError.what() << std::endl;
		return EXIT_FAILURE;
	}
	
	return EXIT_SUCCESS;
}
