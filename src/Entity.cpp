#include "Entity.hpp"

Entity::Entity(EntityManager &manager) : manager(manager)
{
	this->isActive = true;
}

Entity::Entity(EntityManager &manager, std::string name, LayerType layer) :
manager(manager), name(name), layer(layer)
{
	this->isActive = true;
}

Entity::~Entity()
{
	//std::cout << "destructor Entity" << std::endl;
	for (auto &component: components)
		delete component;
	components.clear();
	componentTypeMap.clear();//type info is delete ?
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

void Entity::PrintComponents() const
{
    for (auto mapElement: componentTypeMap)
        std::cout << "    Component<" << mapElement.first->name() << ">" << std::endl;
}
