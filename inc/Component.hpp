#ifndef COMPONENT_HPP
# define COMPONENT_HPP

# include "Entity.hpp"

class Entity;

class Component
{
private:
	
public:
	virtual ~Component(){};

	Entity *owner;

	virtual	void Initialize(){};
	virtual	void Update(float deltaTime){};
	virtual	void Render(){};
};

#endif
