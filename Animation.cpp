#ifndef _ANIMATION_HPP_
#include "Animation.hpp"
#endif



CAnimation::CAnimation(void)
{
    image = 0;
    x = 0;
    y = 0;
    frame = 0;
    number_of_frames = 0;
    render_loop = false;
}


CAnimation::CAnimation(SDL_Surface* _image, int _x, int _y, unsigned short _number_of_frames, bool _render_loop)
{
    image = _image;
    x = _x;
    y = _y;
    number_of_frames = _number_of_frames;
    render_loop = _render_loop;
}


/*CAnimation::~CAnimation(void)
{
}*/



void CAnimation::SetImage(SDL_Surface* _image)
{
    image = _image;
}


void CAnimation::Render(SDL_Surface* destination)
{
    if(frame == number_of_frames)
    {
        frame = 0;
        if (render_loop == false)
        {
			SetDestroy(true);
		}
        return;
    }
    
    SDL_Rect src_rect;
    src_rect.x = 40 * frame;
    src_rect.y = 0;
    src_rect.w = 40;
    src_rect.h = 40;
    
    SDL_Rect dest_rect;
    dest_rect.x = x;
    dest_rect.y = y;
    
    ++frame;
    
    SDL_BlitSurface(image, &src_rect, destination, &dest_rect);
}


