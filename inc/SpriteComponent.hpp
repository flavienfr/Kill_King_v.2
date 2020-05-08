#ifndef SPRITECOMPONENT_HPP
# define SPRITECOMPONENT_HPP

# include <SDL2/SDL.h>
# include <map>
# include "Game.hpp"
# include "TextureManager.hpp"
# include "AssetManager.hpp"
# include "Component.hpp"
# include "TransformComponent.hpp"
# include "Animation.hpp"

class TransformComponent;

class SpriteComponent : public Component
{
private:
	TransformComponent					*transform;
	SDL_Texture							*texture;
	SDL_Rect							srcRectangle;
	SDL_Rect							dstRectangle;
	bool								isAnimated;
	int									numFrames;
	int									animationSpeed;
	int									isFixed;
	std::map<std::string, Animation>	animations;
	std::string							currentAnimationName;
	unsigned int						animationIndex;

public:
	SpriteComponent(const char *filePath);
	SpriteComponent(const char *filePath, int frames, int animationSpeed, bool hasDirection, bool fixed);
	~SpriteComponent();

	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

	void SetTexture(std::string assetTextureId);
	void Play(std::string animationName);
	void Initialize() override;
	void Update(float deltaTime) override;
	void Render() override;


};

#endif
