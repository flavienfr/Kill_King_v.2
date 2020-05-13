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
	for (auto it = entities.begin(); it != entities.end(); )
	{
		(*it)->Update(deltaTime);
		if (!(*it)->IsActive())
		  it = entities.erase(it);
		else
			it++;
	}
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

Entity *EntityManager::GetEntityByName(std::string entityName) const//for loop again
{
	for (auto *entity: entities)
		if (entity->name == entityName)
			return (entity);
	return (NULL);
}

unsigned int EntityManager::GetEntityCount()
{
	return (entities.size());
}

void EntityManager::PrintEntityComponent(bool noTile) const
{
	for (int i = 0; i < entities.size(); i++)
	{
		if (noTile && entities[i]->name == "Tile")
		 continue ;
		std::cout << "Entity "<< i <<": \"" << entities[i]->name << "\"" << std::endl;
		entities[i]->PrintComponents();
	}
}

CollisionType EntityManager::CheckEntityCollisions() const
{//esquiver: entity->name == "Tile" / attention odre des entity pour collision 

    for (int i = 0; i < entities.size() - 1; i++)
	{
		auto& thisEntity = entities[i];
        if (thisEntity->HasComponent<ColliderComponent>())
		{
            ColliderComponent* thisCollider = thisEntity->GetComponent<ColliderComponent>();
            for (int j = i + 1; j < entities.size(); j++)
			{
                auto& thatEntity = entities[j];
				if (thisEntity->name != thatEntity->name && thatEntity->hasComponent<ColliderComponent>())
				{
					ColliderComponent *thatCollider = thatEntity->GetComponent<ColliderComponent>();
					if (Collision::CheckRectCollision(thisCollider->collider, thatCollider->collider))
					{
						if (thisCollider->colliderTag == "PLAYER" && thatCollider->colliderTag == "ENEMY")
							return (PLAYER_ENEMY_COLLISION);
						if (thisCollider->colliderTag == "PLAYER" && thatCollider->colliderTag == "PROJECTILE")
							return (PLAYER_PROJECTILE_COLLISION);
						if (thisCollider->colliderTag == "PLAYER" && thatCollider->colliderTag == "VEGETATION")
							return (PLAYER_VEGETATION_COLLISION);
						if (thisCollider->colliderTag == "ENEMY" && thatCollider->colliderTag == "FRIENDLY_PROJECTILE")
							return (ENEMY_PROJECTILE_COLLISION);
						if (thisCollider->colliderTag == "PLAYER" && thatCollider->colliderTag == "LEVEL_COMPLETE")
							return (PLAYER_LEVEL_COMPLETE_COLLISION);
					}
				}
			}
		}

	}
	return (NO_COLLISION);
}
