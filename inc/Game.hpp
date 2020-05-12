#ifndef GAME_H
# define GAME_H

# include <SDL2/SDL.h>
# include <SDL2/SDL_image.h>
# include <SDL2/SDL_ttf.h>
# include <iostream>
# include "glm.hpp"

# include "Entity.hpp"
# include "Component.hpp"
# include "EntityManager.hpp"
# include "Constants.hpp"
# include "Game.hpp"
# include "AssetManager.hpp"
# include "Map.hpp"
# include "TransformComponent.hpp"
# include "SpriteComponent.hpp"
# include "ColliderComponent.hpp"
# include "KeyBoardControlComponent.hpp"
# include "TextLabelComponent.hpp"
# include "ProjectileEmitterComponent.hpp"

class AssetManager;

class Game
{
private:
	bool isRunning;
	SDL_Window *window;
public:
	Game();
	~Game();

	static SDL_Renderer *renderer;
	static AssetManager *assetManager;
	static SDL_Event	event;
	static SDL_Rect		camera;
	int	ticksLastFrame;

	bool IsRunning() const;
	void Initialize(int width, int height);
	void ProcessInput();
	void Update();
	void Render();
	void Destroy();

	void LoadLevel(int levelNumber);
	void HandleCameraMovement();
	void CheckCollisions();

	void ProcessNextLevel();
	void ProcessGameOver();

};

#endif
