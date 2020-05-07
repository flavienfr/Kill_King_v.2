#ifndef GAME_H
# define GAME_H

# include <SDL2/SDL.h>
# include <SDL2/SDL_image.h>
# include <SDL2/SDL_ttf.h>
# include <iostream>
# include "Constants.hpp"
# include "Entity.hpp"
# include "EntityManager.hpp"
# include "TransformComponent.hpp"

class Game
{
private:
	bool isRunning;
	SDL_Window *window;
public:
	Game();
	~Game();

	static SDL_Renderer *renderer;
	int	ticksLastFrame;

	bool IsRunning() const;
	void Initialize(int width, int height);
	void LoadLevel(int levelNumber);
	void ProcessInput();
	void Update();
	void Render();
	void Destroy();
};

#endif
