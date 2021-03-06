#pragma once

enum ShipType
{
	SHIP_NONE,
	AIRCRAFT,
	BATTLESHIP,
	CRUSIER,
	DESTROYER,
};

enum ShipLength
{
	AIRCRAFT_LENGTH = 5,
	BATTLESHIP_LENGTH = 4,
	CRUSIER_LENGTH = 3,
	DESTROYER_LENGTH = 2,

	MAX_SHIP_LENGTH = 5,
	TOTAL_SHIP_LENGTH = 16,
};

enum ShipCount
{
	AIRCRAFT_COUNT = 1,
	BATTLESHIP_COUNT = 1,
	CRUSIER_COUNT = 1,
	DESTROYER_COUNT = 2,

	TOTAL_SHIP_COUNT = 5,
};

enum HitResult
{
	HIT,
	MISS,
	DESTROY,

	DESTROY_AIRCRAFT,
	DESTROY_BATTLESHIP,
	DESTROY_CRUSIER,
	DESTROY_DESTROYER,
};

enum Direction
{
	DIRECTION_NONE,
	EAST,
	WEST,
	SOUTH,
	NORTH,
};

enum MapSize
{
	WIDTH = 8,
	HEIGHT = 8,
};

enum MapData
{
	MAP_EMPTY,
	MAP_SHIP,
	MAP_HIT,
	MAP_MISS,
	MAP_DESTROY,
};

enum Probability
{
	PROBABILITY_INCREMENT = 50, //Just a big enough value.
};

class Enum
{
public:
	Enum();
	~Enum();
};

