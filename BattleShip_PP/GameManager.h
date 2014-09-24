#pragma once
#include "Player.h"

class GameManager
{
public:
	GameManager();
	~GameManager();

	void	Init();
	void	Draw();
	void	SetupShips();
	void	SetRole();

	void	Run();
	void	GetAttackPos();
	void	GetHitResult();
	void	InformHitResult(HitResult m_HitResult);
	bool	IsGameOver();
	

private:
	Player		m_User;
	Player		m_AI;
	Player*		m_Attacker;
	Player*		m_Defender;

	Position	m_AttackPos;
	HitResult	m_HitResult;
};