#include <iostream>
#include "Game.hpp"



int main(int argc, char* argv[])
{
	CGame game;
	
	try
	{
		game.Run();
	}
	catch(std::bad_alloc)
	{
		std::cerr << "Ran out of memory. Exiting." << std::endl;
	}
	catch (...)
	{
		std::cerr << "Unhandled exception. Exiting." << std::endl;
	}
	
	return 0;
}


