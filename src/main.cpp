#include <iostream>
#include "Constants.hpp"
#include "Game.hpp"

int main(int ac, char *av[])
{
    Game *game = new Game();

    game->Initialize(WINDOW_WIDTH, WINDOW_HEIGHT);

    while (game->IsRunning())
	{
        game->ProcessInput();
        game->Update();
        game->Render();
    }

    //game->Destroy();
	delete game;

    return (0); 
}
