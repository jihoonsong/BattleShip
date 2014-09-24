#pragma once

class Board
{
public:
	Board();
	~Board();

	void	Init();

	bool	IsWithinMap(Position head, Direction direction, ShipType shipType);
	bool	IsNotOverlap(Position head, Direction direction, ShipType shipType);

	void	AddMapData(Position head);
	void	AddMapData(char x, char y);

	int		GetMapData(Position attackPos)	{ return m_MapData[attackPos.m_X - 'a'][attackPos.m_Y - '1']; }
	
	void	SetMapData(Position attackPos, HitResult hitResult);

private:
	int		GetShipLength(ShipType shipType);
	int		m_MapData[WIDTH][HEIGHT];
};