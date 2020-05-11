#include "TextLabelComponent.hpp"

TextLabelComponent::TextLabelComponent(int x, int y, std::string text, std::string fontFamily, const SDL_Color &color) :
position({x, y}), text(text), fontFamily(fontFamily), color(color)
{
	SetLabelText(text, fontFamily);
}

TextLabelComponent::~TextLabelComponent()
{
}

void TextLabelComponent::SetLabelText(std::string text, std::string fontFamily)
{
	SDL_Surface *surface;

	if (!(surface = TTF_RenderText_Blended(Game::assetManager->GetFont(fontFamily), text.c_str(), color)))
        std::cerr << "error creating font surface" << std::endl;
	if (!(texture = SDL_CreateTextureFromSurface(Game::renderer, surface)))
		std::cerr << "error creating texture: " << SDL_GetError() << std::endl;
	SDL_QueryTexture(texture, NULL, NULL, &position.w, &position.h);
	SDL_FreeSurface(surface);
}

void TextLabelComponent::Render()
{
	FontManager::Draw(texture, position);
}