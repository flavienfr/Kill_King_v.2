#include "ColliderComponent.hpp"

ColliderComponent::ColliderComponent(std::string colliderTag, int x, int y, int width, int height) :
colliderTag(colliderTag), collider({x, y, width, height})
{
	//my collion paint debug
	texture = Game::assetManager->GetTexture("collider-texture");
	srcRect = {0, 0, 32, 32};
}

ColliderComponent::~ColliderComponent()
{
}

void ColliderComponent::Initialize()
{
	if (owner->hasComponent<TransformComponent>())//mettre des protection 
	{
		transform = owner->GetComponent<TransformComponent>();
		//srcRect = {0, 0, transform->widht, transform->height}; Why init src?
		dstRect = {collider.x, collider.y, collider.w, collider.h};
	}
}

void ColliderComponent::Update(float deltaTime)
{
	if (owner->hasComponent<TransformComponent>())
	{
		collider.x = static_cast<int>(transform->position.x);
		collider.y = static_cast<int>(transform->position.y);
		collider.w = transform->widht * transform->scale;
		collider.h = transform->height * transform->scale;
		dstRect.x = collider.x - Game::camera.x;
		dstRect.y = collider.y - Game::camera.y;
		dstRect.w = collider.w;//dst for camera
		dstRect.h = collider.h;//dst for camera
	}
}

void ColliderComponent::Render()
{
	TextureManager::Draw(texture, srcRect, dstRect, SDL_FLIP_NONE);
}
