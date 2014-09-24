#include "stdafx.h"
#include "Board.h"


Board::Board()
{
	Init();
}


Board::~Board()
{
}

void Board::Init()
{
	memset(m_MapData, MAP_EMPTY, sizeof(int) * (WIDTH * HEIGHT));
}

bool Board::IsWithinMap(Position head, Direction direction, ShipType shipType)
{
	int length = GetShipLength(shipType);
	
	switch (direction)
	{
	case EAST:
		if (head.m_Y + (length - 1) <= '1' + (WIDTH - 1))
		{
			return true;
		}
		else
		{
			return false;
		}
	case WEST:
		if (head.m_Y - (length - 1) >= '1')
		{
			return true;
		}
		else
		{
			return false;
		}
	case SOUTH:
		if (head.m_X + (length - 1) <= 'a' + (HEIGHT - 1))
		{
			return true;
		}
		else
		{
			return false;
		}
	case NORTH:
		if (head.m_X - (length - 1) >= 'a')
		{
			return true;
		}
		else
		{
			return false;
		}
	default:
		printf_s("IsWithinMap error!\n");
		return false;
	}
}
bool Board::IsNotOverlap(Position head, Direction direction, ShipType shipType)
{
	for (int i = 0; i < GetShipLength(shipType); ++i)
	{
		switch (direction)
		{
		case EAST:
			i == 0 ? head.m_Y += 0 : head.m_Y += 1;
			break;
		case WEST:
			i == 0 ? head.m_Y -= 0 : head.m_Y -= 1;
			break;
		case SOUTH:
			i == 0 ? head.m_X += 0 : head.m_X += 1;
			break;
		case NORTH:
			i == 0 ? head.m_X -= 0 : head.m_X -= 1;
			break;
		default:
			printf_s("IsNotOverlap error!!\n");
			break;
		}

		if (m_MapData[head.m_X - 'a'][head.m_Y - '1'] == MAP_SHIP)
		{
			return false;
		}
	}

	return true;
}

void Board::AddMapData(Position head)
{
	if (m_MapData[head.m_X - 'a'][head.m_Y - '1'] == MAP_EMPTY)
	{
		m_MapData[head.m_X - 'a'][head.m_Y - '1'] = MAP_SHIP;
	}
	else
	{
		printf_s("AddMapData error!!\n");
	}
}
void Board::AddMapData(char x, char y)
{
	if (m_MapData[x - 'a'][y - '1'] == MAP_EMPTY)
	{
		m_MapData[x - 'a'][y - '1'] = MAP_SHIP;
	}
	else
	{
		printf_s("AddMapData error!\n");
	}
}

int Board::GetShipLength(ShipType shipType)
{
	int length = 0;
	switch (shipType)
	{
	case AIRCRAFT:
		length = AIRCRAFT_LENGTH;
		break;
	case BATTLESHIP:
		length = BATTLESHIP_LENGTH;
		break;
	case CRUSIER:
		length = CRUSIER_LENGTH;
		break;
	case DESTROYER:
		length = DESTROYER_LENGTH;
		break;
	default:
		printf_s("GetShipLength Error!!\n");
		return false;
	}

	return length;
}

void Board::SetMapData(Position attackPos, HitResult hitResult)
{
	if (hitResult == MISS)
	{
		m_MapData[attackPos.m_X - 'a'][attackPos.m_Y - '1'] = MAP_MISS;
	}
	else
	{
		m_MapData[attackPos.m_X - 'a'][attackPos.m_Y - '1'] = MAP_HIT;
	}
}
