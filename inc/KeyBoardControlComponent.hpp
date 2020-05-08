#ifndef KEYBOARDCONTROLCOMPONENT_HPP
# define KEYBOARDCONTROLCOMPONENT_HPP

# include <string>
# include "Game.hpp"
# include "Component.hpp"
# include "TransformComponent.hpp"
# include "SpriteComponent.hpp"

class SpriteComponent;//why

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
