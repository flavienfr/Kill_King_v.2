#include "Entity.hpp"

Entity::Entity(EntityManager &manager) : manager(manager)
{
	this->isActive = true;
}

Entity::Entity(EntityManager &manager,std::string name) : manager(manager), name(name)
{
	this->isActive = true;
}

Entity::~Entity()
{
}

void Entity::Update(float deltaTime)
{
	for (auto &component: this->components)
	 component->Update(deltaTime);
}

void Entity::Render()
{
	for (auto &component: this->components)
		component->Render();
}

void Entity::Destroy()
{
	this->isActive = false;
}

bool Entity::IsActive() const
{
	return (this->isActive);
}
