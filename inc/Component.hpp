#ifndef COMPONENT_HPP
# define COMPONENT_HPP

# include "Entity.hpp"

class Entity;
//Make it has an interface ?
class Component
{
private:
	
public:
	Component();
	virtual ~Component();

	Entity *owner;

	virtual	void Initialize();
	virtual	void Update(float deltaTime);
	virtual	void Render();
};

#endif
