#include "KeyBoardControlComponent.hpp"

KeyBoardControlComponent::KeyBoardControlComponent()
{
}

KeyBoardControlComponent::KeyBoardControlComponent(std::string upKey, std::string downKey, std::string rightKey, std::string leftKey, std::string shootKey)
{
	this->upKey = GetSDLKeyCode(upKey);
	this->downKey = GetSDLKeyCode(downKey);
	this->rightKey = GetSDLKeyCode(rightKey);
	this->leftKey = GetSDLKeyCode(leftKey);
	this->shootKey = GetSDLKeyCode(shootKey);
}

KeyBoardControlComponent::~KeyBoardControlComponent()
{
}

std::string KeyBoardControlComponent::GetSDLKeyCode(std::string key)//pourquoi cette fonction 
{
	if (key == "up") return (std::to_string(SDLK_UP));
	if (key == "down") return (std::to_string(SDLK_DOWN));
	if (key == "right") return (std::to_string(SDLK_RIGHT));
	if (key == "left") return (std::to_string(SDLK_LEFT));
	if (key == "space") return (std::to_string(SDLK_SPACE));;
	return (std::to_string(static_cast<int>(key[0])));//return assci table char
}

void KeyBoardControlComponent::Initialize()
{
	transform = owner->GetComponent<TransformComponent>();
	sprite = owner->GetComponent<SpriteComponent>();
}

void KeyBoardControlComponent::Update(float deltaTime)
{
	if (Game::event.type == SDL_KEYDOWN)
	{
		std::string keyCode = std::to_string(Game::event.key.keysym.sym);

		if (keyCode == upKey)
		{
			transform->velocity.y = -100;
			transform->velocity.x = 0;
			sprite->Play("upAnimation");
		}
		if (keyCode == downKey)
		{
			transform->velocity.y = 100;
			transform->velocity.x = 0;
			sprite->Play("downAnimation");
		}
		if (keyCode == rightKey)
		{
			transform->velocity.y = 0;
			transform->velocity.x = 100;
			sprite->Play("rightAnimation");
		}
		if (keyCode == leftKey)
		{
			transform->velocity.y = 0;
			transform->velocity.x = -100;
			sprite->Play("leftAnimation");
		}
		if (keyCode == shootKey)
		{
		}
	}
	if (Game::event.type == SDL_KEYUP)
	{
		std::string keyCode = std::to_string(Game::event.key.keysym.sym);

		if (keyCode == upKey)
		{
			transform->velocity.y = 0;
		}
		if (keyCode == downKey)
		{
			transform->velocity.y = 0;
		}
		if (keyCode == rightKey)
		{
			transform->velocity.x = 0;
		}
		if (keyCode == leftKey)
		{
			transform->velocity.x = 0;
		}
	}
}
