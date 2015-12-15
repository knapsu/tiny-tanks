#ifndef _TANK_HPP_
#include "Tank.hpp"
#endif



CTank::CTank(void)
{
	image = 0;
	armour = 0;
	movement_speed = 0;
	
	moving = false;
	
	x = 0;
	y = 0;
	collision_x = 0;
	collision_y = 0;
	collision_width = 0;
	collision_height = 0;
	shoot_speed = 10;
	shoot_frequency = 50;
	shoot_timer = 0;
	
	shooting = false;
	movement_direction = UP;
}


CTank::CTank(SDL_Surface* _image, short _armour, Uint8 _movement_speed, int _x, int _y, Direction _movement_direction)
{
	image = _image;
	armour = _armour;
	movement_speed = _movement_speed;
	
	x = _x;
	y = _y;
	movement_direction = _movement_direction;
	
	//tymczasowo
	collision_x = _x;
	collision_y = _y;
	collision_width = image->w / 4;
	collision_height = image->h;
	
	shooting = false;
	shoot_speed = 10;
	shoot_frequency = 50;
	shoot_timer = 0;
}


/*CTank::~CTank(void)
{
}*/



bool CTank::IsShooting(void)
{
	return shooting;
}


void CTank::SetShooting(bool _shooting)
{
	shooting = _shooting;
}


void CTank::ResetShootTimer(void)
{
	shoot_timer = 0;
}


void CTank::Render(SDL_Surface* destination)
{
    SDL_Rect source_rectangle;
    
	switch (movement_direction)
	{
	case UP:
		source_rectangle.x = 0;
		break;
	case DOWN:
		source_rectangle.x = 40;
		break;
	case RIGHT:
		source_rectangle.x = 80;
		break;
	case LEFT:
		source_rectangle.x = 120;
		break;
	}
    source_rectangle.y = 0;
    source_rectangle.w = 40;
    source_rectangle.h = 40;
    
    SDL_Rect destination_rectangle;
    destination_rectangle.x = x;
    destination_rectangle.y = y;
    
    SDL_BlitSurface(image, &source_rectangle, destination, &destination_rectangle);
}


void CTank::OnCollisionActive(Uint8& collision_flags)
{
	if (collision_flags & MOVE_THROUGH)
	{
		return;
	}
	else if (collision_flags & (BULLET_PLAYER | BULLET_COMPUTER))
	{
        // pocisk obsłuży to zdarzenie
        return;
	}
	else
	{
		MoveBack();
	}
}


void CTank::OnCollisionPassive(Uint8& collision_flags)
{
	if (collision_flags & BULLET_COMPUTER)
	{
		armour -= 1;
		if (armour == 0)
		{
			SetDestroy(true);
		}
	}
}


void CTank::Move(void)
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


void CTank::MoveBack(void)
{
	switch (movement_direction)
	{
	case UP:
		y += movement_speed;
		collision_y += movement_speed;
		break;
	case DOWN:
		y -= movement_speed;
		collision_y -= movement_speed;
		break;
	case RIGHT:
		x -= movement_speed;
		collision_x -= movement_speed;
		break;
	case LEFT:
		x += movement_speed;
		collision_x += movement_speed;
		break;
	default:
		break;
	}
}


short CTank::GetArmour(void)
{
    return armour;
}


void CTank::SetArmour(short _armour)
{
	armour = _armour;
}


SDL_Surface* CTank::GetImage(void)
{
    return image;
}


void CTank::SetImage(SDL_Surface* _image)
{
    image = _image;
    
	collision_width = image->w / 4;
	collision_height = image->h;
}



void CTank::ResetPosition(int _x, int _y, Direction _movement_direction)
{
	SetX(_x);
	SetY(_y);
	SetMovementDirection(_movement_direction);
}



Direction CTank::GetMovementDirection(void)
{
	return movement_direction;
}


void CTank::SetMovementDirection(Direction _movement_direction)
{
	movement_direction = _movement_direction;
}


Uint8 CTank::GetMovementSpeed(void)
{
    return movement_speed;
}


void CTank::SetMovementSpeed(Uint8 _movement_speed)
{
    movement_speed = _movement_speed;
}


void CTank::StartMoving(void)
{
	moving = true;
}


void CTank::StopMoving(void)
{
	moving = false;
}


Uint32 CTank::GetShootTimer(void)
{
    return shoot_timer;
}


void CTank::SetShootTimer(Uint32 _shoot_timer)
{
    shoot_timer = _shoot_timer;
}


Uint32 CTank::GetShootFrequency(void)
{
    return shoot_frequency;
}

void CTank::SetShootFrequency(Uint32 _frequency)
{
    shoot_frequency = _frequency;
}


int CTank::OnDestroy(void)
{
    return 1; // identyfikator czołgu gracza
}



CEnemyTank::CEnemyTank(void)
{
	shoot_timer = 0;
	shoot_frequency = 1500;
}


CEnemyTank::CEnemyTank(SDL_Surface* _image, short _armour, Uint8 _movement_speed, int _x, int _y, Direction _movement_direction)
{
	image = _image;
	armour = _armour;
	movement_speed = _movement_speed;
	
	x = _x;
	y = _y;
	movement_direction = _movement_direction;
	
	collision_x = _x;
	collision_y = _y;
	collision_width = image->w / 4;
	collision_height = image->h;
	
	shooting = true;
	shoot_timer = 0;
	shoot_frequency = 1500;
}



void CEnemyTank::Move(void)
{
    if ( ((GetX() - 15) % 40 == 0) && ((GetY() - 15) % 40 == 0) )
    {
        Think();
    }
    
    CTank::Move();
}


void CEnemyTank::OnCollisionActive(Uint8& flags)
{
	if (flags & MOVE_THROUGH)
	{
		return;
	}
	else if (flags & (BULLET_PLAYER | BULLET_COMPUTER))
	{
        // zdarzenie to obsłuży obiekt pocisku
        return;
	}
	else
	{
		MoveBack();
		Think(true);
	}
}


void CEnemyTank::OnCollisionPassive(Uint8& flags)
{
	if (flags & BULLET_PLAYER)
	{
		armour -= 1;
		if (armour == 0)
		{
			SetDestroy(true);
		}
	}
}


void CEnemyTank::Think(bool colliding)
{
    int r;

    switch (colliding)
    {
    case false:
        r = rand() % 10;
        
        if (r >= 8)
        {
            switch (movement_direction)
            {
            case UP:
                movement_direction = LEFT;
                break;
            case DOWN:
                movement_direction = RIGHT;
                break;
            case RIGHT:
                movement_direction = UP;
                break;
            case LEFT:
                movement_direction = DOWN;
                break;
            }
        }
        else if (r >= 6)
        {
            switch (movement_direction)
            {
            case UP:
                movement_direction = RIGHT;
                break;
            case DOWN:
                movement_direction = LEFT;
                break;
            case RIGHT:
                movement_direction = DOWN;
                break;
            case LEFT:
                movement_direction = UP;
                break;
            }
        }
        break;
        
    case true:
        r = rand() % 6;
        
        if (r  < 2)
        {
            switch (movement_direction)
            {
            case UP:
                movement_direction = LEFT;
                break;
            case DOWN:
                movement_direction = RIGHT;
                break;
            case RIGHT:
                movement_direction = UP;
                break;
            case LEFT:
                movement_direction = DOWN;
                break;
            }
        }
        else if (r < 4)
        {
            switch (movement_direction)
            {
            case UP:
                movement_direction = RIGHT;
                break;
            case DOWN:
                movement_direction = LEFT;
                break;
            case RIGHT:
                movement_direction = DOWN;
                break;
            case LEFT:
                movement_direction = UP;
                break;
            }
        }
        else
        {
            switch (movement_direction)
            {
            case UP:
                movement_direction = DOWN;
                break;
            case DOWN:
                movement_direction = UP;
                break;
            case RIGHT:
                movement_direction = LEFT;
                break;
            case LEFT:
                movement_direction = RIGHT;
                break;
            }
        }
        
        break;
    }
}


int CEnemyTank::OnDestroy(void)
{
    return 3; // identyfikator czołgu wroga
}


