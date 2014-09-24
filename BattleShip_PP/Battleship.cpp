#include "stdafx.h"
#include "Battleship.h"


Battleship::Battleship()
{
	m_Name = "BATTLESHIP";
	m_Type = BATTLESHIP;
	m_MaxHP = 4;
	m_CurHP = m_MaxHP;
}


Battleship::~Battleship()
{
}

HitResult Battleship::HitCheck(Position hitPos)
{
	HitResult result = Ship::HitCheck(hitPos);

	return (result == DESTROY) ? DESTROY_BATTLESHIP : result;
}