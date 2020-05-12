#ifndef PROJECTILEEMITTERCOMPONENT_HPP
# define PROJECTILEEMITTERCOMPONENT_HPP

# include "glm.hpp"
# include "EntityManager.hpp"
# include "TransformComponent.hpp"

class ProjectileEmitterComponent : public Component
{
private:
	TransformComponent	*transform;
	glm::vec2			origin;
	int					speed;
	int					range;
	float				angleRad;
	bool				shoulLoop;

public:
	ProjectileEmitterComponent(int speed, int angleDeg, int range, bool shoulLoop);
	~ProjectileEmitterComponent();

	void Initialize() override;
	void Update(float deltaTime) override;
};

#endif
