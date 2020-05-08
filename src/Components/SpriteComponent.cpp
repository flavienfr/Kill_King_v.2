#include "SpriteComponent.hpp"

SpriteComponent::SpriteComponent(const char *filePath) :
isAnimated(false), animationSpeed(0), animationIndex(0)
{
	SetTexture(filePath);
}

SpriteComponent::SpriteComponent(const char *filePath,int numFrames, int animationSpeed, bool hasDirection, bool fixed) :
isAnimated(true), animationSpeed(animationSpeed), isFixed(fixed), animationIndex(0)
{
	if (hasDirection)
	{
		Animation down = Animation(0, numFrames, animationSpeed);
		Animation right = Animation(1, numFrames, animationSpeed);
		Animation left = Animation(2, numFrames, animationSpeed);
		Animation up = Animation(3, numFrames, animationSpeed);

		animations.emplace("downAnimation", down);
		animations.emplace("rightAnimation", right);
		animations.emplace("leftAnimation", left);
		animations.emplace("upAnimation", up);

		animationIndex = 0;//DEFAULT
		currentAnimationName = "downAnimation";//DEFAULT
	}
	else
	{
		Animation singleAnimation = Animation(0, numFrames, animationSpeed);
		animations.emplace("SingleAnimation", singleAnimation);
		currentAnimationName = "SingleAnimation";
		animationIndex = 0;
	}
	Play(currentAnimationName);

	SetTexture(filePath);
}

SpriteComponent::~SpriteComponent()
{
}

void SpriteComponent::Play(std::string animationName)
{
	numFrames = animations[animationName].numFrames;
	animationIndex = animations[animationName].index;
	animationSpeed = animations[animationName].animationSpeed;
	currentAnimationName = animationName;
}

void SpriteComponent::SetTexture(std::string assetTextureId)
{
	texture = Game::assetManager->GetTexture(assetTextureId);
}

void SpriteComponent::Initialize()
{
	transform = owner->GetComponent<TransformComponent>();
	srcRectangle.x = 0;
	srcRectangle.y = 0;
	srcRectangle.w = transform->widht;
	srcRectangle.h = transform->height;
}

void SpriteComponent::Update(float deltaTime)
{
	if (isAnimated)
		srcRectangle.x = srcRectangle.w * static_cast<int>((SDL_GetTicks() / animationSpeed) % numFrames);
	srcRectangle.y = animationIndex * srcRectangle.h;//gustavo put transform->height
	
	dstRectangle.x = static_cast<int>(transform->position.x) - (isFixed ? 0 : Game::camera.x);
	dstRectangle.y = static_cast<int>(transform->position.y) - (isFixed ? 0 : Game::camera.y);
	dstRectangle.w = transform->widht * transform->scale;
	dstRectangle.h = transform->height * transform->scale;
}

void SpriteComponent::Render()
{
	TextureManager::Draw(texture, srcRectangle, dstRectangle, spriteFlip);
}
