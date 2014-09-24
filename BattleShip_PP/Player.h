#pragma once
#include "Board.h"
class Ship;

class Player
{
public:
	Player();
	~Player();

	void		Init();

	void		SetupShips();
	Position	PlaceHead();
	Direction	SetDirection(Position head);
	void		PlaceShip(Ship& ship, Board& m_MyBoard, Position head, Direction direction);
	void		PrintShips();

	Position	SetAttackPos();
	bool		IsAttackPosNotRepeated();
	HitResult	GetHitResult(Position attackPos);
	void		InformHitResult(HitResult hitResult);

	int			GetAttackCount()				{ return m_AttackCount; }
	void		RaiseAttackCount()				{ ++m_AttackCount; }
	void		RaiseDefendCount()				{ ++m_DefendCount; }
	void		RaiseHitCount()					{ ++m_HitCount; }
	void		RaiseMissCount()				{ ++m_MissCount; }
	void		RaiseDestroyCount()				{ ++m_DestroyCount; }
	int			GetDestroyCount()				{ return m_DestroyCount; }
	void		SetDestroyList(ShipType ship);	

private:
	Ship*		m_ShipList[TOTAL_SHIP_COUNT];
	Board		m_MyBoard;
	Board		m_EnemyBoard;

	Position	m_AttackPos;
	int			m_AttackCount;
	int			m_DefendCount;
	int			m_HitCount;
	int			m_MissCount;
	int			m_DestroyCount;
	bool		m_DestoryList[TOTAL_SHIP_COUNT];
};