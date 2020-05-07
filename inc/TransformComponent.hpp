#ifndef TRANSFORMCOMPONENT_HPP
# define TRANSFORMCOMPONENT_HPP

# include "EntityManager.hpp"
# include "glm.hpp"
# include <SDL2/SDL.h>
# include "Game.hpp"
# include "Component.hpp"

class TransformComponent : public Component
{
private:
	
public:
	TransformComponent(int poxX, int posY, int velX, int velY, int w, int h, int s);
	~TransformComponent();

	glm::vec2	position;
	glm::vec2	velocity;
	int			widht;
	int			height;
	int			scale;

	void Initialize() override;
	void Update(float deltaTime) override;
	void Render() override;
};

#endif
