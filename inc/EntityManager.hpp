#ifndef ENTITYMANAGER_HPP
# define ENTITYMANAGER_HPP

# include "Entity.hpp"
# include "Component.hpp"
# include <vector>

class Entity;

class EntityManager
{
private:
	std::vector<Entity *> entities;

public:
	EntityManager();
	~EntityManager();

	void 					ClearData();
	void 					Update(float deltaTime);
	void 					Render();
	bool 					HasNoEntities();
	Entity					&AddEntity(std::string entityName);
	std::vector<Entity *>	GetEntities() const;//return ref is better ?
	unsigned int			GetEntityCount();

	//Debug
	void	PrintEntityComponent() const;
};

#endif
