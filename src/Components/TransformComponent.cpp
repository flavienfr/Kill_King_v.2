#include "TransformComponent.hpp"

TransformComponent::TransformComponent(int poxX, int posY, int velX, int velY, int w, int h, int s) :
position(glm::vec2(poxX, posY)), velocity(glm::vec2(velX, velY)), widht(w), height(h), scale(s)
{//Is that better to aplli scale here ?
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
}
