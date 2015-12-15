#ifndef _PLAYER_HPP_
#include "Player.hpp"
#endif



CPlayer::CPlayer(void)
{
	score = 0;
	lifes = 0;
}


/*CPlayer::~CPlayer(void)
{
}*/



/*bool CPlayer::HandleKeyDown_Menu(int key)
{
}*/


bool CPlayer::HandleKeyDown_Game(int key)
{
	if (key == controls.GetKeyUp())
	{
		tank.SetMovementDirection(UP);
		tank.StartMoving();
	}
	else if (key == controls.GetKeyDown())
	{
		tank.SetMovementDirection(DOWN);
		tank.StartMoving();
	}
	else if (key == controls.GetKeyRight())
	{
		tank.SetMovementDirection(RIGHT);
		tank.StartMoving();
	}
	else if (key == controls.GetKeyLeft())
	{
		tank.SetMovementDirection(LEFT);
		tank.StartMoving();
	}
	else if (key == controls.GetKeyFire())
	{
		tank.SetShooting(true);
	}
	else if (key == controls.GetKeyStart())
	{
		// ...
	}
	else if (key == controls.GetKeySelect())
	{
		// ...
	}
	else
	{
		return false;
	}
	
	return true;
}


bool CPlayer::HandleKeyUp_Game(int key)
{
	if (key == controls.GetKeyUp())
	{
		if (tank.GetMovementDirection() == UP)
		{
			tank.StopMoving();
		}
	}
	else if (key == controls.GetKeyDown())
	{
		if (tank.GetMovementDirection() == DOWN)
		{
			tank.StopMoving();
		}
	}
	else if (key == controls.GetKeyRight())
	{
		if (tank.GetMovementDirection() == RIGHT)
		{
			tank.StopMoving();
		}
	}
	else if (key == controls.GetKeyLeft())
	{
		if (tank.GetMovementDirection() == LEFT)
		{
			tank.StopMoving();
		}
	}
	else if (key == controls.GetKeyFire())
	{
		tank.SetShooting(false);
	}
	else if (key == controls.GetKeyStart())
	{
		// ...
	}
	else if (key == controls.GetKeySelect())
	{
		// ...
	}
	else
	{
		return false;
	}
	
	return true;
}


unsigned long CPlayer::GetScore(void)
{
	return score;
}


void CPlayer::ResetScore(void)
{
	score = 0;
}


void CPlayer::IncreaseScore(unsigned long points)
{
	score += points;
}


unsigned short CPlayer::GetLifes(void)
{
	return lifes;
}


void CPlayer::ResetLifes(unsigned short _lifes)
{
	lifes = _lifes;
}


void CPlayer::IncreaseLifes(void)
{
	++lifes;
}


void CPlayer::DecreaseLifes(void)
{
	--lifes;
}


