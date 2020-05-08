#include "TileComponent.hpp"

TileComponent::TileComponent(int srcRectX, int srcRectY, int x, int y, int tileSize, int tileScale, std::string assetTextureId)
{
	this->texture = Game::assetManager->GetTexture(assetTextureId);
	this->srcRect.x = srcRectX;
	this->srcRect.y = srcRectY;
	this->srcRect.w = tileSize;
	this->srcRect.h = tileSize;

	this->dstRect.x = x;
	this->dstRect.y = y;
	this->dstRect.w = tileSize *tileScale;
	this->dstRect.h = tileSize *tileScale;

	this->position.x = x;
	this->position.y = y;
}

TileComponent::~TileComponent()
{
	SDL_DestroyTexture(texture);
}

void TileComponent::Update(float deltaItme)
{
	dstRect.x = position.x - Game::camera.x;
	dstRect.y = position.y - Game::camera.y;
}

void TileComponent::Render()
{//Do no draw if ouside the screean area
	TextureManager::Draw(texture, srcRect, dstRect, SDL_FLIP_NONE);
}
