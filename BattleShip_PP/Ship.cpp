#include "stdafx.h"
#include "Ship.h"

Ship::Ship()
{
	m_Name = "";
	m_Type = SHIP_NONE;
	memset(m_Pos, 0, sizeof(Position) * MAX_SHIP_LENGTH);
	m_MaxHP = 0;

	Init();
}


Ship::~Ship()
{
}


void Ship::Init()
{	
	m_CurHP = m_MaxHP;
}

void Ship::AddPosition(Position pos)
{
	for (int index = 0; index < m_MaxHP; ++index)
	{
		if (m_Pos[index].m_X == 0)
		{
			m_Pos[index] = pos;

			break;
		}
	}
}
void Ship::AddPosition(char x, char y)
{
	Position m_tempPos;
	m_tempPos.m_X = x;
	m_tempPos.m_Y = y;

	Ship::AddPosition(m_tempPos);
}
HitResult Ship::HitCheck(Position hitPos)
{
	for (int index = 0; index < m_MaxHP; ++index)
	{
		if (m_Pos[index].m_X == hitPos.m_X && m_Pos[index].m_Y == hitPos.m_Y)
		{
			m_CurHP--;
			m_Pos[index].m_X = 0;
			m_Pos[index].m_Y = 0;
		
			if (m_CurHP <= 0)
			{
				return DESTROY;
			}
			else
			{
				return HIT;
			}
		}
	}

	return MISS;
}
void Ship::Print()
{
	printf_s("%s: ", Ship::GetName().c_str());
	for (int i = 0; i < Ship::GetMaxHP(); ++i)
	{
		printf_s("%c%c ", m_Pos[i].m_X, m_Pos[i].m_Y);
	}
	printf_s("\n");
}