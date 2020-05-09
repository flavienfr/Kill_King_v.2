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

void EntityManager::Render()//optimise with data structure
{
	for (int layerNumber = 0; layerNumber < NUM_LAYER; layerNumber++)
	{
		for (auto &entity: GetEntitiesByLayer(static_cast<LayerType>(layerNumber)))
		{
			entity->Render();
		}
	}
}

bool EntityManager::HasNoEntities()
{
	return (this->entities.size() == 0);
}

Entity &EntityManager::AddEntity(std::string entityName, LayerType layer)
{
	Entity *entity = new Entity(*this, entityName, layer);
	this->entities.emplace_back(entity);
	return (*entity);
}

std::vector<Entity *> EntityManager::GetEntities() const
{
	return (entities);
}

std::vector<Entity *>  EntityManager::GetEntitiesByLayer(LayerType layer) const
{//need optimisation
	std::vector<Entity *> selectedEntities;

	for (auto &entity: entities)
	{
		if (entity->layer == layer)
		{
			selectedEntities.emplace_back(entity);
		}
	}

	return (selectedEntities);
}

unsigned int EntityManager::GetEntityCount()
{
	return (entities.size());
}

void EntityManager::PrintEntityComponent() const
{
	for (int i = 0; i < entities.size(); i++)
	{
		std::cout << "Entity "<< i <<": \"" << entities[i]->name << "\"" << std::endl;
		entities[i]->PrintComponents();
	}
}

std::string EntityManager::CheckEntityCollisions(Entity &myEntity) const
{//not opti
	ColliderComponent *myCollider = myEntity.GetComponent<ColliderComponent>();

	for (auto &entity: entities)
	{
		if (entity->name == myEntity.name || entity->name == "Tile")
			continue ;
		if (entity->hasComponent<ColliderComponent>())
		{
			ColliderComponent *otherCollider = entity->GetComponent<ColliderComponent>();
			if (Collision::CheckRectCollision(myCollider->collider, otherCollider->collider))
				return (otherCollider->colliderTag);
		}
	}
	return (std::string());
}
