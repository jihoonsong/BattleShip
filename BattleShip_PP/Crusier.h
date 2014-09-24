#pragma once
#include "Ship.h"
class Crusier :
	public Ship
{
public:
	Crusier();
	~Crusier();

	HitResult	HitCheck(Position hitPos);
};

