#pragma once

class Ship
{
public:
	Ship();
	~Ship();

	void				Init();

	void				AddPosition(Position pos);
	void				AddPosition(char x, char y);
	virtual HitResult	HitCheck(Position hitPos);
	void				Print();

	std::string			GetName()	{ return m_Name; }
	ShipType			GetType()	{ return m_Type; }
	int					GetCurHP()	{ return m_CurHP; }
	int					GetMaxHP()	{ return m_MaxHP; }
	Position			GetPos(int index)	{ return m_Pos[index]; }

protected:
	std::string			m_Name;
	ShipType			m_Type;
	Position			m_Pos[MAX_SHIP_LENGTH];
	int					m_MaxHP;
	int					m_CurHP;
};