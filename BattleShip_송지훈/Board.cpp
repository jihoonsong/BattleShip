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

bool Board::IsWithinMap(Position head, Direction direction, int shipLength)
{
	switch (direction)
	{
	case EAST:
		return (head.m_Y + (shipLength - 1) <= '1' + (WIDTH - 1));
	case WEST:
		return (head.m_Y - (shipLength - 1) >= '1');
	case SOUTH:
		return (head.m_X + (shipLength - 1) <= 'a' + (HEIGHT - 1));
	case NORTH:
		return (head.m_X - (shipLength - 1) >= 'a');
	default:
		printf_s("IsWithinMap error!\n");
		return false;
	}
}
bool Board::IsOverlap(Position head, Direction direction, int shipLength)
{
	for (int i = 0; i < shipLength; ++i)
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
			return true;
		}
	}

	return false;
}

void Board::SetMapData(Position head)
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
void Board::SetMapData(char x, char y)
{
	Position pos = { x, y };
	SetMapData(pos);
}

void Board::SetMapData(Position attackPos, HitResult hitResult, bool* destroyList)
{
	if (hitResult == HIT)
	{
		m_MapData[attackPos.m_X - 'a'][attackPos.m_Y - '1'] = MAP_HIT;
	}
	else if (hitResult == MISS)
	{
		m_MapData[attackPos.m_X - 'a'][attackPos.m_Y - '1'] = MAP_MISS;
	}
	else
	{
		int shipLength = 0;
		switch (hitResult)
		{
		case DESTROY_AIRCRAFT:
			shipLength = AIRCRAFT_LENGTH;
			break;
		case DESTROY_BATTLESHIP:
			shipLength = BATTLESHIP_LENGTH;
			break;
		case DESTROY_CRUSIER:
			shipLength = CRUSIER_LENGTH;
			break;
		case DESTROY_DESTROYER:
			shipLength = DESTROYER_LENGTH;
			break;
		}

		int directionX = 0;
		int directionY = 0;
		int deltaX[4] = { 0, 0, -1, 1 };
		int deltaY[4] = { 1, -1, 0, 0 };
		int checkDeadlock = 0;
		for (int i = 0; i < 4; ++i)
		{
			int posX = attackPos.m_X - 'a';
			int posY = attackPos.m_Y - '1';
			bool isDirection = true;
			for (int j = 1; j < shipLength; ++j)
			{
				posX += deltaX[i];
				posY += deltaY[i];
				if (m_MapData[posX][posY] != MAP_HIT)
				{
					isDirection = false;
					break;
				}
			}
			
			if (isDirection)
			{
				directionX = deltaX[i];
				directionY = deltaY[i];
				++checkDeadlock;
			}
		}

		if (checkDeadlock > 1)
		{
			return;
		}

		int posX = attackPos.m_X - 'a';
		int posY = attackPos.m_Y - '1';
		for (int i = 0; i < shipLength; ++i)
		{
			m_MapData[posX][posY] = MAP_DESTROY;
			posX += directionX;
			posY += directionY;
		}
	}
}

int Board::GetMapData(Position pos)
{
	if (!( ('a' <= pos.m_X && pos.m_X < 'a' + HEIGHT) &&
			'1' <= pos.m_Y && pos.m_Y < '1' + WIDTH))
	{
		printf_s("GetMapData Error!!\n");
		return -1;
	}

	return m_MapData[pos.m_X - 'a'][pos.m_Y - '1'];
}
int Board::GetMapData(char posX, char posY)
{
	Position pos = { posX, posY};
	
	return GetMapData(pos);
}