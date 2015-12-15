#ifndef _TILE_HPP_
#include "Tile.hpp"
#endif



CTile::CTile(SDL_Surface* _image, int _x, int _y, Uint8 _flags, int _duration, bool _base)
{
	image = _image;
	x = _x;
	y = _y;
	
	collision_x = _x;
	collision_y = _y;
	collision_width = image->w;
	collision_height = image->h;
	
	duration = _duration;
	flags = _flags;
	
	base = _base;
}


/*CTile::~CTile(void)
{
}*/



SDL_Surface* CTile::GetImage(void)
{
    return image;
}


void CTile::SetImage(SDL_Surface* _image)
{
    image = _image;
    
	collision_width = image->w;
	collision_height = image->h;
}


void CTile::Render(SDL_Surface* destination)
{
    SDL_Rect destination_rectangle;
    destination_rectangle.x = x;
    destination_rectangle.y = y;
    
    SDL_BlitSurface(image, 0, destination, &destination_rectangle);
}


/*void CTile::OnCollisionActive(Uint8& collision_flags)
{
}*/


void CTile::OnCollisionPassive(Uint8& collision_flags)
{
	if (collision_flags & (BULLET_PLAYER | BULLET_COMPUTER))
	{
		if (flags & NO_SHOOT_THROUGH)
		{
			if (flags & NOT_DESTRUCTABLE)
			{
				return;
			}
			
			duration -= 1;
			if (duration == 0)
			{
				SetDestroy(true);
			}
		}

	}
}


int CTile::OnDestroy(void)
{
    if (IsBase() == true)
    {
        return 10;
    }
    
	return 0; // identyfikator muru
}


bool CTile::IsBase(void)
{
	return base;
}

