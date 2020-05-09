#include "ColliderComponent.hpp"

ColliderComponent::ColliderComponent(std::string colliderTag, int x, int y, int width, int height) :
colliderTag(colliderTag), collider({x, y, width, height})
{
}

ColliderComponent::~ColliderComponent()
{
}

void ColliderComponent::Initialize()
{
	if (owner->hasComponent<TransformComponent>())
	{
		transform = owner->GetComponent<TransformComponent>();
		srcRect = {0, 0, transform->widht, transform->height};
		dstRect = {collider.x, collider.y, collider.w, collider.y};
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
		dstRect.x = collider.x - Game::camera.x;//what need to understand
		dstRect.y = collider.y - Game::camera.y;//what need to understand
	}
}
