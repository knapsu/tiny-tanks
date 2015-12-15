#ifndef _LEVEL_HPP_
#include "Level.hpp"
#endif



CPoint::CPoint(void)
{
	x = 0;
	y = 0;
}


CPoint::CPoint(int _x, int _y)
{
	x = _x;
	y = _y;
}


/*CPoint::~CPoint(void)
{
}*/



CLevel::CLevel(void)
{
	base_alive = false;
	enemies_active = 0;
	enemies_to_deploy = 0;
	level_number = 0;
}


void CLevel::SetPlayerStartingPoint(unsigned short player_number, int _x, int _y)
{
	switch (player_number)
	{
	case 1:
		player_1_starting_point.x = _x;
		player_1_starting_point.y = _y;
		break;
	case 2:
		player_2_starting_point.x = _x;
		player_2_starting_point.y = _y;
		break;
	default:
		break;
	}
}


/*CLevel::~CLevel(void)
{
}*/



int CLevel::GetPlayerStartingPointX(unsigned short player_number)
{
	switch (player_number)
	{
	case 1:
		return player_1_starting_point.x;
	case 2:
		return player_2_starting_point.x;
	default:
		return -1;
	}
}


int CLevel::GetPlayerStartingPointY(unsigned short player_number)
{
	switch (player_number)
	{
	case 1:
		return player_1_starting_point.y;
	case 2:
		return player_2_starting_point.y;
	default:
		return -1;
	}
}


void CLevel::AddEnemyStartingPoint(int _x, int _y)
{
	enemy_starting_points.push_back(new CPoint(_x, _y));
}


void CLevel::RemoveEnemyStartingPoints()
{
	for (std::vector<CPoint*>::iterator i = enemy_starting_points.begin(); i != enemy_starting_points.end(); ++i)
    {
		delete (*i);
	}
	enemy_starting_points.clear();
}


int CLevel::GetEnemyStartingPointX(unsigned int position)
{
	if (position > enemy_starting_points.size())
	{
		return 0;
	}
	else
	{
		return enemy_starting_points.at(position)->x;
	}
}


int CLevel::GetEnemyStartingPointY(unsigned int position)
{
	if (position > enemy_starting_points.size())
	{
		return 0;
	}
	else
	{
		return enemy_starting_points.at(position)->y;
	}
}
	

int CLevel::EnemyStartingPoints(void)
{
	return enemy_starting_points.size();
}


unsigned short CLevel::GetLevelNumber(void)
{
	return level_number;
}


void CLevel::SetLevelNumber(unsigned short _level_number)
{
	level_number = _level_number;
}


