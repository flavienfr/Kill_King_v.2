#ifndef KEYBOARDCONTROLCOMPONENT_HPP
# define KEYBOARDCONTROLCOMPONENT_HPP

# include "Game.hpp"
# include "EntityManager.hpp"
# include "TransformComponent.hpp"
# include "SpriteComponent.hpp"

class SpriteComponent;//erase that ?

class KeyBoardControlComponent : public Component
{
private:
	std::string upKey;
	std::string downKey;
	std::string rightKey;
	std::string leftKey;
	std::string shootKey;
	TransformComponent	*transform;
	SpriteComponent		*sprite;

public:
	KeyBoardControlComponent();
	KeyBoardControlComponent(std::string upKey, std::string downKey, std::string rightKey, std::string leftKey, std::string shootKey);
	~KeyBoardControlComponent();

	void Initialize() override;
	void Update(float deltaTime) override;

	std::string GetSDLKeyCode(std::string key);
};

#endif
