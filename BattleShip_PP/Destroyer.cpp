#include "stdafx.h"
#include "Destroyer.h"


Destroyer::Destroyer()
{
	m_Name = "DESTROYER";
	m_Type = DESTROYER;
	m_MaxHP = 2;
	m_CurHP = m_MaxHP;
}


Destroyer::~Destroyer()
{
}

HitResult Destroyer::HitCheck(Position hitPos)
{
	HitResult result = Ship::HitCheck(hitPos);

	return (result == DESTROY) ? DESTROY_DESTROYER : result;
}