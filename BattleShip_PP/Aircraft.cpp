#include "stdafx.h"
#include "Aircraft.h"


Aircraft::Aircraft()
{
	m_Name = "AIRCRAFT";
	m_Type = AIRCRAFT;
	m_MaxHP = 5;
	m_CurHP = m_MaxHP;
}


Aircraft::~Aircraft()
{
}

HitResult Aircraft::HitCheck(Position hitPos)
{
	HitResult result = Ship::HitCheck(hitPos);

	return (result == DESTROY) ? DESTROY_AIRCRAFT : result;
}