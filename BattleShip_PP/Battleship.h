#pragma once
#include "Ship.h"
class Battleship :
	public Ship
{
public:
	Battleship();
	~Battleship();

	HitResult	HitCheck(Position hitPos);
};
