#ifndef TEXTLABELCOMPONENT_HPP
# define TEXTLABELCOMPONENT_HPP

# include <SDL2/SDL.h>
# include <SDL2/SDL_ttf.h>
# include "EntityManager.hpp"
# include "AssetManager.hpp"
# include "Game.hpp"

class TextLabelComponent : public Component
{
private:
	SDL_Rect	position;
	std::string	text;
	std::string	fontFamily;
	SDL_Color	color;
	SDL_Texture *texture;

public:
	TextLabelComponent(int x, int y, std::string text, std::string fontFamily, const SDL_Color &color);
	~TextLabelComponent();

	void Render() override;

	void SetLabelText(std::string text, std::string fontFamily);
};

#endif
