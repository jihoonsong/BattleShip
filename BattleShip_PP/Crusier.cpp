#include "stdafx.h"
#include "Crusier.h"


Crusier::Crusier()
{
	m_Name = "CRUSIER";
	m_Type = CRUSIER;
	m_MaxHP = 3;
	m_CurHP = m_MaxHP;
}


Crusier::~Crusier()
{
}

HitResult Crusier::HitCheck(Position hitPos)
{
	HitResult result = Ship::HitCheck(hitPos);

	return (result == DESTROY) ? DESTROY_CRUSIER : result;
}