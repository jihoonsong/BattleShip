#pragma once

class Board
{
public:
	Board();
	~Board();

	void	Init();

	bool	IsWithinMap(Position head, Direction direction, int shipLength);
	bool	IsOverlap(Position head, Direction direction, int shipLength);

	void	SetMapData(Position head);
	void	SetMapData(char x, char y);
	
	void	SetMapData(Position attackPos, HitResult hitResult, bool* destroyList);

	int		GetMapData(Position pos);
	int		GetMapData(char posX, char posY);

private:
	int		m_MapData[WIDTH][HEIGHT];
};