#ifndef COMPONENT_HPP
# define COMPONENT_HPP

class Entity;

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
