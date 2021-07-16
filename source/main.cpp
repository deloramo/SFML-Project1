#include "Game.h"

int main() 
{
	Game game;
	//Game loop
	while (game.isRunning()) 
	{
		game.updateActivity();

		game.render();
	}

	return 0;
}