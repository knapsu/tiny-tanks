#ifndef _BULLET_HPP_
#include "Bullet.hpp"
#endif



CBullet::CBullet(SDL_Surface* _image, Uint8 _movement_speed, int _x, int _y, Direction _movement_direction)
{
	image = _image;
	
	moving = true;
	movement_speed = _movement_speed;
	movement_direction = _movement_direction;
	
	x = _x;
	y = _y;
	
	collision_x = _x;
	collision_y = _y;
	collision_width = image->w / 4;
	collision_height = image->h;
}


/*CBullet::~CBullet(void)
{
}*/



void CBullet::Render(SDL_Surface* destination)
{
    SDL_Rect source_rectangle;
    
	switch (movement_direction)
	{
	case UP:
		source_rectangle.x = 0;
		break;
	case DOWN:
		source_rectangle.x = 6;
		break;
	case RIGHT:
		source_rectangle.x = 12;
		break;
	case LEFT:
		source_rectangle.x = 18;
		break;
	}
    source_rectangle.y = 0;
    source_rectangle.w = 6;
    source_rectangle.h = 6;
    
    SDL_Rect destination_rectangle;
    destination_rectangle.x = x;
    destination_rectangle.y = y;
    
    SDL_BlitSurface(image, &source_rectangle, destination, &destination_rectangle);
}


void CBullet::OnCollisionActive(Uint8& collision_flags)
{
	if (collision_flags & SHOOT_THROUGH)
	{
		return;
	}
	else
	{
		SetDestroy(true);
	}
}


void CBullet::OnCollisionPassive(Uint8& collision_flags)
{
	if (collision_flags & (BULLET_PLAYER | BULLET_COMPUTER))
	{
		SetDestroy(true);
	}
}


int CBullet::OnDestroy(void)
{
    return 4; // identyfikator pocisku
}


void CBullet::Move(void)
{
	switch (movement_direction)
	{
	case UP:
		y -= movement_speed;
		collision_y -= movement_speed;
		break;
	case DOWN:
		y += movement_speed;
		collision_y += movement_speed;
		break;
	case RIGHT:
		x += movement_speed;
		collision_x += movement_speed;
		break;
	case LEFT:
		x -= movement_speed;
		collision_x -= movement_speed;
		break;
	default:
		break;
	}
}


