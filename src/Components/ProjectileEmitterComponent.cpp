#include "ProjectileEmitterComponent.hpp"

ProjectileEmitterComponent::ProjectileEmitterComponent(int speed, int angleDeg, int range, bool shoulLoop) :
speed(speed), angleRad(glm::radians(static_cast<float>(angleDeg))), range(range), shoulLoop(shoulLoop)
{
}

ProjectileEmitterComponent::~ProjectileEmitterComponent()
{
}

void ProjectileEmitterComponent::Initialize()
{
	transform = owner->GetComponent<TransformComponent>();
	origin = glm::vec2(transform->position.x, transform->position.y);
	transform->velocity = glm::vec2(glm::cos(angleRad) * speed, glm::sin(angleRad) *speed);
}

void ProjectileEmitterComponent::Update(float deltaTime)
{
	if (glm::distance(transform->position, origin) > range)
	{
		if (shoulLoop)
		{
			transform->position.x = origin.x;
			transform->position.y = origin.y;
		}
		else
		{
			owner->Destroy();
		}
		
	}
}