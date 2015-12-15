#ifndef _TEXT_HPP_
#include "Text.hpp"
#endif



CText::CText(void)
{
    x = 0;
    y = 0;
    text = 0;
	color.r = 0;
	color.g = 0;
	color.b = 0;
}


CText::CText(TTF_Font* font, int style, Uint8 r, Uint8 g, Uint8 b, std::string _text, int _x, int _y)
{
    TTF_SetFontStyle(font, style); 
    color.r = r;
	color.g = g;
	color.b = b;
	text = TTF_RenderUTF8_Solid(font, _text.c_str(), color);
	x = _x;
	y = _y;
}


/*CText::~CText(void)
{
}*/



void CText::SetInscription(TTF_Font* font, std::string _text, int _x, int _y)
{
    text = TTF_RenderUTF8_Solid(font, _text.c_str(), color);
    x = _x;
    y = _y;
}


void CText::SetStyle(TTF_Font* font, int style)
{
    TTF_SetFontStyle(font, style); 
}


void CText::Render(SDL_Surface* destination)
{
    SDL_Rect destination_rectangle;

	destination_rectangle.x = x;
	destination_rectangle.y = y;
	
	destination_rectangle.w = text->w;
	destination_rectangle.h = text->h;
    SDL_BlitSurface(text, 0, destination, &destination_rectangle);
}


