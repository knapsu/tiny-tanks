#ifndef _COLLIDABLE_HPP_
#include "Collidable.hpp"
#endif



CCollidable::CCollidable(void)
{
	flags = 0;
	destroy = false;
}



bool CCollidable::IsColliding(CCollidable* object)
{
	if (object == this)
	{
		return false;
	}
	
	bool collision_on_x_axis = false;
	
	if (object->collision_x < collision_x)
	{
		if (collision_x <= (object->collision_x + object->collision_width - 1))
		{
			collision_on_x_axis = true;
		}
	}
	else if(object->collision_x <= (collision_x + collision_width - 1))
	{
		collision_on_x_axis = true;
	}
	
	if (collision_on_x_axis == true)
	{
		if (object->collision_y < collision_y)
		{
			if (collision_y <= (object->collision_y + object->collision_height - 1))
			{
				return true;
			}
		}
		else if(object->collision_y <= (collision_y + collision_height - 1))
		{
			return true;
		}
	}
	
	return false;
}


/*CCollidable::~CCollidable(void)
{
}*/



bool CCollidable::IsMoving(void)
{
	return moving;
}


void CCollidable::OnCollisionActive(Uint8& collision_flags)
{
}


void CCollidable::OnCollisionPassive(Uint8& collision_flags)
{
}


void CCollidable::Move(void)
{
}


void CCollidable::SetFlags(Uint8 _flags)
{
    flags = _flags;
}


Uint8 CCollidable::GetFlags(void)
{
    return flags;
}


bool CCollidable::ToDestroy(void)
{
	return destroy;
}


void CCollidable::SetDestroy(bool _destroy)
{
	destroy = _destroy;
}


int CCollidable::OnDestroy(void)
{
    return 0;
}


int CCollidable::GetX(void)
{
    return x;
}


int CCollidable::GetY(void)
{
    return y;
}


void CCollidable::SetX(int _x)
{
	collision_x = _x + (collision_x - x);
    x = _x;
}


void CCollidable::SetY(int _y)
{
	collision_y = _y + (collision_y - y);
    y = _y;
}



bool CCollidable::IsShooting(void)
{
	return false;
}


Uint32 CCollidable::GetShootTimer(void)
{
	return 0;
}


void CCollidable::SetShootTimer(Uint32 _shoot_timer)
{
}


Uint32 CCollidable::GetShootFrequency(void)
{
	return 0;
}


Direction CCollidable::GetMovementDirection(void)
{
	return UP;
}


