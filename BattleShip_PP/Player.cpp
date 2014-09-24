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
		delete m_ShipList[i];
		m_ShipList[i] = nullptr;
	}
}


void Player::Init()
{
	m_AttackCount = 0;
	m_DefendCount = 0;
	m_HitCount = 0;
	m_MissCount = 0;
	m_DestroyCount = 0;
	memset(m_DestoryList, false, sizeof(bool) * (TOTAL_SHIP_COUNT));
	m_MyBoard.Init();
	m_EnemyBoard.Init();
	for (int i = 0; i < TOTAL_SHIP_COUNT; ++i)
	{
		m_ShipList[i]->Init();
	}
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
			} while (!m_MyBoard.IsWithinMap(head, direction, m_ShipList[i]->GetType()));
			
		} while (!m_MyBoard.IsNotOverlap(head, direction, m_ShipList[i]->GetType()));
		
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
		m_MyBoard.AddMapData(head.m_X, head.m_Y);
	}
}
void Player::PrintShips()
{
	for (int i = 0; i < _countof(m_ShipList); i++)
	{
		m_ShipList[i]->Print();
	}
}

Position Player::SetAttackPos()
{
	RaiseAttackCount();
	
	do 
	{
		m_AttackPos.m_X = rand() % HEIGHT + 'a';
		m_AttackPos.m_Y = rand() % WIDTH + '1';
	} while (!IsAttackPosNotRepeated());

	return m_AttackPos;
}
bool Player::IsAttackPosNotRepeated()
{
	if (m_EnemyBoard.GetMapData(m_AttackPos) == MAP_EMPTY)
	{
		return true;
	}
	else
	{
		return false;
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
		break;
	}

	m_EnemyBoard.SetMapData(m_AttackPos, hitResult);
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
		if (!m_DestoryList[index + i])
		{
			m_DestoryList[index + i] = true;
			break;
		}
	}
}