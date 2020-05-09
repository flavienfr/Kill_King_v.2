#ifndef COLLIDERCOMPONENT_HPP
# define COLLIDERCOMPONENT_HPP

# include <SDL2/SDL.h>
# include "Game.hpp"
# include "TransformComponent.hpp"

class ColliderComponent : public Component
{
private:


public:
	ColliderComponent(std::string colliderTag, int x, int y, int width, int height);
	~ColliderComponent();

	std::string			colliderTag;
	SDL_Rect			collider;
	SDL_Rect			srcRect;
	SDL_Rect			dstRect;
	TransformComponent	*transform;

	void Initialize() override;
	void Update(float deltaTime) override;
};

#endif
