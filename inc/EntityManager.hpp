#ifndef ENTITYMANAGER_HPP
# define ENTITYMANAGER_HPP

# include "Entity.hpp"
# include "Component.hpp"
#include "EntityManager.hpp"
# include "Collision.hpp"
# include "ColliderComponent.hpp"
# include <vector>

class Entity;

class EntityManager
{
private:
	std::vector<Entity *> entities;//may be slown when deleting entities

public:
	EntityManager();
	~EntityManager();

	void 					ClearData();
	void 					Update(float deltaTime);
	void 					Render();
	bool 					HasNoEntities();
	Entity					&AddEntity(std::string entityName, LayerType layer);
	std::vector<Entity *>	GetEntities() const;//return ref is better ?
	Entity					*GetEntityByName(std::string entityName) const;//for loop again
	std::vector<Entity *>	GetEntitiesByLayer(LayerType layer) const;//return ref is better ?
	unsigned int			GetEntityCount();
	CollisionType			CheckEntityCollisions() const;

	//Debug
	void	PrintEntityComponent(bool noTile) const;
};

#endif
