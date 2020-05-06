#ifndef ENTITY_HPP
# define ENTITY_HPP

# include <vector>
# include <string>
# include "Component.hpp"
# include "EntityManager.hpp"

class Component;
class EntityManager;

class Entity
{
private:
	bool						isActive;
	EntityManager				&manager;
	std::vector<Component *>	components;

public:
	Entity(EntityManager &manager);
	Entity(EntityManager &manager,std::string name);
	virtual ~Entity();

	std::string	name;

	void Update(float deltaTime);
	void Render();
	void Destroy();
	bool IsActive() const;
};

#endif
