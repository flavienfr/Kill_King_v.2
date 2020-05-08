#ifndef ENTITY_HPP
# define ENTITY_HPP

# include <vector>
# include <string>
# include <iostream>
# include <map>
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
	std::map<const std::type_info *, Component *> componentTypeMap;

public:
	Entity(EntityManager &manager);
	Entity(EntityManager &manager,std::string name);
	virtual ~Entity();

	std::string	name;//put it private ?

	void Update(float deltaTime);
	void Render();
	void Destroy();
	bool IsActive() const;

	void PrintComponents() const;

	template <typename T, typename ...Targs>
	T &AddComponent(Targs&&... args);
	template <typename T>
	T* GetComponent();
	template <typename T>
	bool HasComponent() const;
};

template <typename T, typename ...Targs>
T	&Entity::AddComponent(Targs&&... args)
{
	T *newComponent(new T(std::forward<Targs>(args)...));

	components.emplace_back(newComponent);
	componentTypeMap[&typeid(*newComponent)] = newComponent;
	newComponent->owner = this;
	newComponent->Initialize();

	return (*newComponent);
}

template <typename T>
T	*Entity::GetComponent()
{
	return (static_cast<T *>(componentTypeMap[&typeid(T)]));
}

template <typename T>
bool Entity::HasComponent() const
{
	for (auto &componentType: componentTypeMap)
		if (componentType.first == &typeid(T))
			return (true);
	return (false);
}

#endif
