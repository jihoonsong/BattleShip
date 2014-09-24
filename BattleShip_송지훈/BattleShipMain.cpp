


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

// 	//Initialize Network.
// 	try
// 	{
// 		Network::Initialize();
// 	}
// 	catch (Network::Exception)
// 	{
// 		puts("초기화 도중 문제가 발생했습니다.");
// 		return 0;
// 	}
// 	Network	network;
// 	Player	player;
// 
// 	//Connect to network.
// 	const char ip[16] = "10.73.42.117";
// 	const unsigned short port = 9001;
// 	
// 	try
// 	{
// 		network.Connect(ip, port);
// 	}
// 	catch (Network::Exception ex)
// 	{
// 		switch (ex)
// 		{
// 		case Network::NETWORK_ERROR:
// 			puts("서버와 연결에 실패했습니다.");
// 			break;
// 		case Network::PARAMETER_ERROR:
// 			puts("함수의 인수가 잘못되었습니다.");
// 			break;
// 		}
// 		return 0;
// 	}
// 	puts("접속 성공!");
// 	
// 	//Login and start game.
// 	try
// 	{
// 
// 		//Send my name.
// 		const wchar_t name[MAX_NAME_LEN] = L"문익";
// 		ErrorType error = network.SubmitName(name, 131061);
// 		if (error == ET_DUPLICATED_NAME)
// 		{
// 			puts("이미 존재하는 이름입니다.");
// 			return 0;
// 		}
// 		puts("게임 시작 대기중");
// 		Network::GameStartData gameStartData;
// 		network.WaitForStart(&gameStartData);
// 		puts("게임 시작");
// 
// 		
// 		bool allOver = false;
// 		while (!allOver)
// 		{
// 			player.Init();
// 			player.SetupShips();
// 
// 			//Network::MapData mapData;
// 			char mapdata[MAP_SIZE] = { 0, };
// 
// 			while (true)
// 			{
// 				int index = 0;
// 				
// 				for (int i = 0; i < AIRCRAFT_LENGTH; ++i)
// 				{
// 					Position pos = player.GetShipPosition(0, i);
// 					index = pos.m_X - 'a' + (pos.m_Y - '1') * MAP_WIDTH;
// 					mapdata[index] = MD_AIRCRAFT;
// 				}
// 				for (int i = 0; i < BATTLESHIP_LENGTH; ++i)
// 				{
// 					Position pos = player.GetShipPosition(1, i);
// 					index = pos.m_X - 'a' + (pos.m_Y - '1') * MAP_WIDTH;
// 					mapdata[index] = MD_BATTLESHIP;
// 				}
// 				for (int i = 0; i < CRUISER_LENGTH; ++i)
// 				{
// 					Position pos = player.GetShipPosition(2, i);
// 					index = pos.m_X - 'a' + (pos.m_Y - '1') * MAP_WIDTH;
// 					mapdata[index] = MD_CRUISER;
// 				}
// 				for (int i = 0; i < DESTROYER_LENGTH; ++i)
// 				{
// 					Position pos = player.GetShipPosition(3, i);
// 					index = pos.m_X - 'a' + (pos.m_Y - '1') * MAP_WIDTH;
// 					mapdata[index] = MD_DESTROYER1;
// 				}
// 				for (int i = 0; i < DESTROYER_LENGTH; ++i)
// 				{
// 					Position pos = player.GetShipPosition(4, i);
// 					index = pos.m_X - 'a' + (pos.m_Y - '1') * MAP_WIDTH;
// 					mapdata[index] = MD_DESTROYER2;
// 				}
// 				
// 				error = network.SubmitMap(mapdata);
// 				
// 				if (error == ET_INVALID_MAP)
// 					puts("유효하지 않은 맵 데이터입니다.");
// 				else
// 				{
// 					puts("유효 맵 데이터입니다.");
// 					break;
// 				}
// 			}
// 
// 			bool gameOver = false;
// 			while (!gameOver)
// 			{
// 				PacketType packetType;
// 				error = network.GetPacketType(&packetType);
// 
// 				switch (packetType)
// 				{
// 				case PKT_SC_ERROR:				// 에러가 발생하는 경우(상대방의 접속 종료)
// 				{
// 					if (error == ET_OPPOSITION_DISCONNECTED)
// 					{
// 						puts("상대방의 접속이 끊어졌습니다.");
// 					}
// 					else
// 					{
// 						puts("알 수 없는 에러입니다.");
// 					}
// 					return 0;
// 				}
// 				case PKT_SC_MY_TURN:			// 공격을 함.
// 				{
// 					while (true)
// 					{
// 						Position attackPos = player.SetAttackPos();
// 						Coord pos;
// 						pos.mX = attackPos.m_X;
// 						pos.mY = attackPos.m_Y;
// 						error = network.SubmitAttack(pos);
// 						if (error == ET_INVALID_ATTACK)
// 							puts("유효하지 않은 공격 위치입니다.");
// 						else
// 							break;
// 					}
// 					break;
// 				}
// 				case PKT_SC_ATTACK_RESULT:		// 공격 결과를 받음.
// 				{
// 					Network::AttackResultData attackResult;
// 					attackResult = network.GetAttackResult();
// 					if (attackResult.isMine)
// 					{
// 						puts("공격 결과:");
// 
// 						HitResult hitResult;
// 						switch (attackResult.attackResult)
// 						{
// 						case AR_MISS:
// 							hitResult = MISS;
// 							break;
// 						case AR_HIT:
// 							hitResult = HIT;
// 							break;
// 						case AR_DESTROY_AIRCRAFT:
// 							hitResult = DESTROY_AIRCRAFT;
// 							break;
// 						case AR_DESTROY_BATTLESHIP:
// 							hitResult = DESTROY_BATTLESHIP;
// 							break;
// 						case AR_DESTROY_CRUISER:
// 							hitResult = DESTROY_CRUSIER;
// 							break;
// 						case  AR_DESTROY_DESTROYER:
// 							hitResult = DESTROY_DESTROYER;
// 							break;
// 						}
// 						player.InformHitResult(hitResult);
// 					}
// 
// 					std::string result;
// 					switch (attackResult.attackResult)
// 					{
// 					case AR_MISS:
// 						result = "MISS";
// 						break;
// 					case AR_HIT:
// 						result = "HIT";
// 						break;
// 					case AR_DESTROY_AIRCRAFT:
// 						result = "DESTROY_AIRCRAFT";
// 						break;
// 					case AR_DESTROY_BATTLESHIP:
// 						result = "DESTROY_BATTLESHIP";
// 						break;
// 					case AR_DESTROY_CRUISER:
// 						result = "DESTROY_CRUISER";
// 						break;
// 					case  AR_DESTROY_DESTROYER:
// 						result = "DESTROY_DESTORYER";
// 						break;
// 					}
// 					printf_s("X: %d , Y: %d , RESULT: %s\n", attackResult.pos.mX, attackResult.pos.mY, result.c_str());
// 					break;
// 				}
// 				case PKT_SC_GAME_OVER:			// 게임 종료
// 				{
// 					Network::GameResultData gameResult;
// 					gameResult = network.GetGameResult();
// 					if (gameResult.isWinner)
// 						puts("승리!!!");
// 					else
// 						puts("패배...");
// 					printf_s("턴 수: %d\n", gameResult.turns);
// 					gameOver = true;
// 					break;
// 				}default:
// 					throw Network::UNEXPECTED_PACKET;
// 					break;
// 				}
// 			}
// 
// 			PacketType packetType;
// 			network.GetPacketType(&packetType);
// 
// 			if (packetType == PKT_SC_NEXT_GAME)
// 			{
// 				puts("다음 게임을 준비해주세요.");
// 				allOver = false;
// 			}
// 			else if (packetType == PKT_SC_ALL_OVER)
// 			{
// 				Network::FinalResultData finalResult;
// 				finalResult = network.GetFinalResult();
// 				puts("게임이 모두 종료되었습니다.");
// 				printf_s("승리 횟수: %d, 평균 턴 수: %.1f", finalResult.winCount, finalResult.avgTurns);
// 
// 				allOver = true;
// 			}
// 			else
// 			{
// 				throw Network::UNEXPECTED_PACKET;
// 			}
// 		}
// 	}
// 	catch (Network::Exception ex)
// 	{
// 		switch (ex)
// 		{
// 		case Network::NETWORK_ERROR:
// 			puts("네트워크에 문제가 발생했습니다.");
// 			break;
// 		case Network::SERVER_CLOSED:
// 			puts("서버와의 연결이 끊어졌습니다.");
// 			break;
// 		case Network::PARAMETER_ERROR:
// 			puts("함수의 인수가 잘못되었습니다.");
// 			break;
// 		case Network::UNEXPECTED_PACKET:
// 			puts("서버에서 잘못된 정보가 전송되었습니다.");
// 			break;
// 		default:
// 			puts("????????????????");
// 			break;
// 		}
// 	}
// 
// 	//Disconnect network connection.
// 	network.Disconnect();
		
 	GameManager gameManager;
 	gameManager.Run();
	
	_getch();

	return 0;
}