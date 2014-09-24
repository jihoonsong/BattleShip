// BattleShip_PP.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Aircraft.h"
#include "Battleship.h"
#include "Crusier.h"
#include "Destroyer.h"
#include "Player.h"
#include "GameManager.h"

int _tmain(int argc, _TCHAR* argv[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	srand((unsigned int)time(NULL));
	
	GameManager gameManager;
	gameManager.Run();
	
	_getch();

	return 0;
}