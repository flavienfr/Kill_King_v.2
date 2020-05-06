#include "TransformComponent.hpp"

TransformComponent::TransformComponent(int poxX, int posY, int velX, int velY, int w, int h, int s) :
position(glm::vec2(poxX, posY)), velocity(glm::vec2(velX, velY)), widht(w), height(h), scale(s)
{
}

TransformComponent::~TransformComponent()
{
}

void TransformComponent::Initialize()
{

}

void TransformComponent::Update(float deltaTime)
{
	position.x += velocity.x * deltaTime;
	position.y += velocity.y * deltaTime;
}

void TransformComponent::Render()
{
    SDL_Rect TransformRectangle =
	{
        (int) position.x,
        (int) position.y,
        widht,
        height
    };
    SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(Game::renderer, &TransformRectangle);
}
