#include "stdafx.h"
#include "GameManager.h"


GameManager::GameManager()
{
	m_Attacker = &m_User;
	m_Defender = &m_AI;
}


GameManager::~GameManager()
{
}

void GameManager::Init()
{
	m_User.Init();
	m_AI.Init();
	SetupShips();
}
void GameManager::Draw()
{
}
void GameManager::SetupShips()
{
	m_User.SetupShips();
	m_AI.SetupShips();
}

void GameManager::Run()
{
	int turnCount = 0;
	for (int i = 0; i < 10; ++i)
	{
		Init();
		do
		{
			//Draw()
			GetAttackPos();
			GetHitResult();
			InformHitResult(m_HitResult);
		} while (!IsGameOver());
		turnCount += m_Attacker->GetAttackCount();
	}
	printf_s("%d", turnCount / 10);

	//DrawEnding//
}
void GameManager::GetAttackPos()
{
	do 
	{
		m_AttackPos = m_Attacker->SetAttackPos();
	} while (!(	'a' <= m_AttackPos.m_X && m_AttackPos.m_X <= 'a' + (HEIGHT - 1) &&
				'1' <= m_AttackPos.m_Y && m_AttackPos.m_Y <= '1' + (WIDTH - 1)		));
}
void GameManager::GetHitResult()
{
	m_HitResult = m_Defender->GetHitResult(m_AttackPos);
}
void GameManager::InformHitResult(HitResult m_HitResult)
{
	m_Attacker->InformHitResult(m_HitResult);
}
bool GameManager::IsGameOver()
{
	return	m_User.GetDestroyCount() == TOTAL_SHIP_COUNT ||
			m_AI.GetDestroyCount() == TOTAL_SHIP_COUNT;
}