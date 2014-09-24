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
	system("cls");

	for (int i = 0; i < HEIGHT; ++i)
	{
		for (int j = 0; j < WIDTH; ++j)
		{
			Position pos = { i + 'a', j + '1' };
			switch (m_User.GetEnemyMapData(pos))
			{
			case MAP_EMPTY:
				printf_s("- ");
				break;
			case MAP_HIT:
				printf_s("X ");
				break;
			case MAP_MISS:
				printf_s("* ");
				break;
			case MAP_DESTROY:
				printf_s("X ");
				break;
			}
		}

		printf_s("\n");
	}
	
// 	printf_s("Destroyed list: ");
// 	for (int i = 0; i < TOTAL_SHIP_COUNT; ++i)
// 	{
// 		if (m_User.GetDestroyList(i))
// 		{
// 			if (i < AIRCRAFT_COUNT)
// 			{
// 				printf_s("AIRCRAFT ");
// 			}
// 			else if (i < AIRCRAFT_COUNT + BATTLESHIP_COUNT)
// 			{
// 				printf_s("BATTLESHIP ");
// 			}
// 			else if (i < AIRCRAFT_COUNT + BATTLESHIP_COUNT + CRUSIER_COUNT)
// 			{
// 				printf_s("CRUSIER ");
// 			}
// 			else
// 			{
// 				printf_s("DESTROYER ");
// 			}
// 		}
// 	}

	for (int i = 0; i < HEIGHT; ++i)
	{
		for (int j = 0; j < WIDTH; ++j)
		{
			printf_s("%d\t", m_User.GetProbabilityBoard(i, j));
		}

		printf_s("\n");
	}

	printf_s("Destroyed list: ");
	for (int i = 0; i < TOTAL_SHIP_COUNT; ++i)
	{
		if (m_User.GetDestroyList(i))
		{
			if (i < AIRCRAFT_COUNT)
			{
				printf_s("AIRCRAFT ");
			}
			else if (i < AIRCRAFT_COUNT + BATTLESHIP_COUNT)
			{
				printf_s("BATTLESHIP ");
			}
			else if (i < AIRCRAFT_COUNT + BATTLESHIP_COUNT + CRUSIER_COUNT)
			{
				printf_s("CRUSIER ");
			}
			else
			{
				printf_s("DESTROYER ");
			}
		}
	}
}
void GameManager::SetupShips()
{
	m_User.SetupShips();
	m_AI.SetupShips();
}

void GameManager::Run()
{
	int i = 0;
	int turnCount = 0;
	for (int i = 0; i < 1000; ++i)
	{
		int turnOver = 0;
		Init();
		//Draw();
		do
		{
			++turnOver;
			GetAttackPos();
			GetHitResult();
			InformHitResult(m_HitResult);
			//Draw();
		} while (!IsGameOver());
		turnCount += m_Attacker->GetAttackCount();
		printf_s("%d번째 턴의 턴 오버 수: %d, 평균 턴 오버 수: %f\n", i + 1, turnOver, (float)turnCount / (i + 1));
	}
	printf_s("\nThe average count is %d", turnCount / 1000);
}
void GameManager::GetAttackPos()
{
	do
	{
		m_AttackPos = m_Attacker->SetAttackPos();
	} while (!(	'a' <= m_AttackPos.m_X && m_AttackPos.m_X < 'a' + HEIGHT &&
				'1' <= m_AttackPos.m_Y && m_AttackPos.m_Y < '1' + WIDTH));
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