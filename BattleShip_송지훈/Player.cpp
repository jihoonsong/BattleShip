#include "stdafx.h"
#include "Player.h"
#include "Board.h"
#include "Aircraft.h"
#include "Battleship.h"
#include "Crusier.h"
#include "Destroyer.h"

Player::Player()
{
	m_ShipList[0] = new Aircraft();
	m_ShipList[1] = new Battleship();
	m_ShipList[2] = new Crusier();
	m_ShipList[3] = new Destroyer();
	m_ShipList[4] = new Destroyer();

	Init();
}


Player::~Player()
{
	for (int i = 0; i < _countof(m_ShipList); ++i)
	{
		if (m_ShipList[i])
		{
			delete m_ShipList[i];
			m_ShipList[i] = nullptr;
		}		
	}
}


void Player::Init()
{
	for (int i = 0; i < TOTAL_SHIP_COUNT; ++i)
	{
		m_ShipList[i]->Init();
	}
	m_MyBoard.Init();
	m_EnemyBoard.Init();
	memset(m_ProbabilityBoard, MAP_EMPTY, sizeof(int) * (WIDTH * HEIGHT));
	
	m_AttackPos = { 0, };
	m_AttackCount = 0;
	m_DefendCount = 0;
	m_HitCount = 0;
	m_MissCount = 0;
	m_DestroyCount = 0;
	memset(m_DestroyList, false, sizeof(bool) * (TOTAL_SHIP_COUNT));	
}

void Player::SetupShips()
{
	for (int i = 0; i < _countof(m_ShipList); ++i)
	{
		Position head;
		Direction direction;

		do
		{
			head = PlaceHead();

			do
			{
				direction = SetDirection(head);
			} while (!m_MyBoard.IsWithinMap(head, direction, m_ShipList[i]->GetMaxHP()));

		} while (m_MyBoard.IsOverlap(head, direction, m_ShipList[i]->GetMaxHP()));

		PlaceShip(*m_ShipList[i], m_MyBoard, head, direction);
	}
}
Position Player::PlaceHead()
{
	Position head;
	head.m_X = rand() % 8 + 'a';
	head.m_Y = rand() % 8 + '1';

	return head;
}
Direction Player::SetDirection(Position head)
{
	Direction direction;
	switch (rand() % 4)
	{
	case 0:
		direction = EAST;
		break;
	case 1:
		direction = WEST;
		break;
	case 2:
		direction = SOUTH;
		break;
	case 3:
		direction = NORTH;
		break;
	default:
		direction = DIRECTION_NONE;
		break;
	}

	return direction;
}
void Player::PlaceShip(Ship& ship, Board& m_MyBoard, Position head, Direction direction)
{
	for (int i = 0; i < ship.GetMaxHP(); ++i)
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
			printf_s("PlaceShip error!!\n");
			break;
		}

		ship.AddPosition(head.m_X, head.m_Y);
		m_MyBoard.SetMapData(head.m_X, head.m_Y);
	}
}
void Player::PrintShips()
{
	for (int i = 0; i < _countof(m_ShipList); i++)
	{
		m_ShipList[i]->Print();
	}
}
Position Player::GetShipPosition(int shipIndex, int posIndex)
{
	return m_ShipList[shipIndex]->GetPos(posIndex);
}

Position Player::SetAttackPos()
{
	RaiseAttackCount();

	do
	{
		GetProbabilityOfBoard();
		m_AttackPos = FindMaxProbabilityPosition();
	} while (IsAttackPosRepeated());

	return m_AttackPos;
}
void Player::GetProbabilityOfBoard()
{
	for (int i = 0; i < HEIGHT; ++i)
	{
		for (int j = 0; j < WIDTH; ++j)
		{
			m_ProbabilityBoard[i][j] = 0;
		}
	}

	for (int i = 0; i < HEIGHT; ++i)
	{
		for (int j = 0; j < WIDTH; ++j)
		{
			Position pos = { i + 'a', j + '1' };
			if (m_EnemyBoard.GetMapData(pos) == MAP_MISS)
			{
				m_ProbabilityBoard[i][j] = 0;
			}
			else if (m_EnemyBoard.GetMapData(pos) == MAP_DESTROY)
			{
				m_ProbabilityBoard[i][j] = 0;
			}
			else if (m_EnemyBoard.GetMapData(pos) == MAP_EMPTY)
			{
				m_ProbabilityBoard[i][j] += GetProbabilityOfPosition(pos);
			}
			else if (m_EnemyBoard.GetMapData(pos) == MAP_HIT)
			{
				m_ProbabilityBoard[i][j] = 0;
				IncreaseProbabilityOfAdjcentPosition(pos);
			}
		}
	}
}
int Player::GetProbabilityOfPosition(Position pos)
{
	//Check the number of cases which ship can exist at the position.
	int probability = 0;
	for (int i = 0; i < TOTAL_SHIP_COUNT; ++i)
	{
		if (!m_DestroyList[i])
		{
			int shipLength = m_ShipList[i]->GetMaxHP();
			for (int j = 0; j <= shipLength - 1; ++j)
			{
				int headX = pos.m_X - 'a' - j;
				int tailX = headX + shipLength - 1;
				bool isShipCanExist = true;
				for (int k = headX; k <= tailX; ++k)
				{
					if (!((0 <= k && k < HEIGHT) && m_EnemyBoard.GetMapData(k + 'a', pos.m_Y) == MAP_EMPTY))
					{
						isShipCanExist = false;
					}
				}
				if (isShipCanExist)
				{
					++probability;
				}

				int headY = pos.m_Y - '1' - j;
				int tailY = headY + shipLength - 1;
				isShipCanExist = true;
				for (int k = headY; k <= tailY; ++k)
				{
					if (!((0 <= k && k < WIDTH) && m_EnemyBoard.GetMapData(pos.m_X, k + '1') == MAP_EMPTY))
					{
						isShipCanExist = false;
					}
				}
				if (isShipCanExist)
				{
					++probability;
				}
			}
		}
	}
	
	return probability;
}
void Player::IncreaseProbabilityOfAdjcentPosition(Position pos)
{	
	int deltaX[4] = { 0, 0, -1, 1 };
	int deltaY[4] = { 1, -1, 0, 0 };
	for (int i = 0; i < 4; ++i)
	{
		int posX = pos.m_X - 'a' + deltaX[i];
		int posY = pos.m_Y - '1' + deltaY[i];
		//East, West, South and North in sequence.
		if ((0 <= posX && posX < HEIGHT) && (0 <= posY && posY < WIDTH))
		{
			if (m_EnemyBoard.GetMapData(posX + 'a', posY + '1') == MAP_EMPTY)
			{
				m_ProbabilityBoard[posX][posY] += PROBABILITY_INCREMENT;
			}
			
			if (m_EnemyBoard.GetMapData(posX + 'a', posY + '1') == MAP_HIT)
			{
				posX = pos.m_X - 'a' - deltaX[i];
				posY = pos.m_Y - '1' - deltaY[i];
				if ((0 <= posX && posX < HEIGHT) &&
					(0 <= posY && posY < WIDTH) &&
					m_EnemyBoard.GetMapData(posX + 'a', posY + '1') == MAP_EMPTY)
				{
					m_ProbabilityBoard[posX][posY] += 3 * PROBABILITY_INCREMENT;
				}
			}			
		}
	}
}
Position Player::FindMaxProbabilityPosition()
{
	Position pos = { 0, };
	int maxProbability = 0;
	for (int i = 0; i < HEIGHT; ++i)
	{
		for (int j = 0; j < WIDTH; ++j)
		{
			if (maxProbability < m_ProbabilityBoard[i][j])
			{
				maxProbability = m_ProbabilityBoard[i][j];
				pos.m_X = i + 'a';
				pos.m_Y = j + '1';
			}
			else if (maxProbability == m_ProbabilityBoard[i][j])
			{
				int CurSum = 0;	//Current sum of probability of adjacent positions.
				int NewSum = 0;	//New sum of probability of adjacent positions.
				int deltaX[4] = { 0, 0, 1, -1 };
				int deltaY[4] = { 1, -1, 0, 0 };

				for (int k = 0; k < 4; ++k)
				{
					if ((0 <= pos.m_X - 'a' + deltaX[k] && pos.m_X - 'a' + deltaX[k] < HEIGHT) &&
						(0 <= pos.m_Y - '1' + deltaY[k] && pos.m_Y - '1' + deltaY[k] < WIDTH))
					{
						CurSum += m_ProbabilityBoard[pos.m_X - 'a' + deltaX[k]][pos.m_Y - '1' + deltaY[k]];
					}
					if ((0 <= i + deltaX[k] && i + deltaX[k] < HEIGHT) &&
						(0 <= j + deltaY[k] && j + deltaY[k] < WIDTH))
					{
						NewSum += m_ProbabilityBoard[i + deltaX[k]][j + deltaY[k]];
					}
				}

				if (CurSum < NewSum)
				{
					pos.m_X = i + 'a';
					pos.m_Y = j + '1';
				}
			}
		}
	}

	if (!(	('a' <= pos.m_X && pos.m_X < 'a' + HEIGHT) &&
			('1' <= pos.m_Y && pos.m_Y < '1' + WIDTH)))
	{
		printf_s("FindMaxProbabilityPosition Error!!\n");
		return pos;
	}
	return pos;
}
bool Player::IsAttackPosRepeated()
{
	if (m_EnemyBoard.GetMapData(m_AttackPos) == MAP_EMPTY)
	{
		return false;
	}
	else
	{
		printf_s("Attack Position repeated!!\n");
		return true;
	}
}
HitResult Player::GetHitResult(Position attackPos)
{
	RaiseDefendCount();

	for (int i = 0; i < _countof(m_ShipList); ++i)
	{
		HitResult hitResult = m_ShipList[i]->HitCheck(attackPos);

		if (hitResult != MISS)
		{
			return hitResult;
		}
	}

	return MISS;
}
void Player::InformHitResult(HitResult hitResult)
{
	switch (hitResult)
	{
	case HIT:
		RaiseHitCount();
		break;
	case MISS:
		RaiseMissCount();
		break;
	case DESTROY_AIRCRAFT:
		RaiseDestroyCount();
		SetDestroyList(AIRCRAFT);
		break;
	case DESTROY_BATTLESHIP:
		RaiseDestroyCount();
		SetDestroyList(BATTLESHIP);
		break;
	case DESTROY_CRUSIER:
		RaiseDestroyCount();
		SetDestroyList(CRUSIER);
		break;
	case DESTROY_DESTROYER:
		RaiseDestroyCount();
		SetDestroyList(DESTROYER);
		break;
	default:
		printf_s("InformHitResult error!!\n");
		return;
	}

	m_EnemyBoard.SetMapData(m_AttackPos, hitResult, m_DestroyList);
}
void Player::SetDestroyList(ShipType ship)
{
	int index = 0;
	int count = 0;
	switch (ship)
	{
	case AIRCRAFT:
		index = 0;
		count = AIRCRAFT_COUNT;
		break;
	case BATTLESHIP:
		index += AIRCRAFT_COUNT;
		count = BATTLESHIP_COUNT;
		break;
	case CRUSIER:
		index += (AIRCRAFT_COUNT + BATTLESHIP_COUNT);
		count = CRUSIER_COUNT;
		break;
	case DESTROYER:
		index += (AIRCRAFT_COUNT + BATTLESHIP_COUNT + CRUSIER_COUNT);
		count = DESTROYER_COUNT;
		break;
	case SHIP_NONE:
		printf_s("SetDestroyList error!!\n");
		break;
	}

	for (int i = 0; i < count; ++i)
	{
		if (!m_DestroyList[index + i])
		{
			m_DestroyList[index + i] = true;
			break;
		}
	}
}