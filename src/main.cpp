//-----include section-----
#include <cstdlib>
#include <iostream>

//-----main section-----
int main()
{
	try
	{
		std::cout << "Hello, World!" << std::endl;
	}
	catch (const std::exception& generalError)
	{
		std::cerr << "Exception: " << generalError.what() << std::endl;
		return EXIT_FAILURE;
	}
	
	return EXIT_SUCCESS;
}
