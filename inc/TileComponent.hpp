#ifndef TILECOMPONENT_HPP
# define TILECOMPONENT_HPP

# include <SDL2/SDL.h>
# include "glm.hpp"
# include "Component.hpp"
# include "TextureManager.hpp"

class TileComponent : public Component
{
private:
	SDL_Texture	*texture;
	SDL_Rect	srcRect;
	SDL_Rect	dstRect;
	glm::vec2	position;

public:
	TileComponent(int srcRectX, int srcRectY, int x, int y, int tileSize, int tileScale, std::string assetTextureId);
	~TileComponent();

	void Update(float deltaItme) override;
	void Render() override;
};

#endif
