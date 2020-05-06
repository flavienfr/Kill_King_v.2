#include "EntityManager.hpp"

EntityManager::EntityManager()
{
}

EntityManager::~EntityManager()
{
}

void EntityManager::ClearData()
{
	for (auto &entity: this->entities)
		entity->Destroy();
}

void EntityManager::Update(float deltaTime)
{
	for (auto &entity: this->entities)
		entity->Update(deltaTime);
}

void EntityManager::Render()
{
	for (auto &entity: this->entities)
		entity->Render();
}

bool EntityManager::HasNoEntities()
{
	return (this->entities.size() == 0);
}

Entity &EntityManager::AddEntity(std::string entityName)
{
	Entity *entity = new Entity(*this, entityName);
	this->entities.emplace_back(entity);
	return (*entity);
}

std::vector<Entity *> EntityManager::GetEntities() const
{
	return (entities);
}

unsigned int EntityManager::GetEntityCount()
{
	return (entities.size());
}
