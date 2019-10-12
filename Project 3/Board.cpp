#include "Board.h"
#include <iostream>

Board::Board(int nHoles, int nInitialBeansPerHole)
{
	if (nHoles < 0)
		nHoles = 1;
	if (nInitialBeansPerHole < 0)
		nInitialBeansPerHole = 0;
	m_holes = nHoles;
	m_nInitialBeansPerHole = nInitialBeansPerHole;

	Npot = new Hole;
	Npot->m_beans = 0;
	Npot->holeNumber = 0;
	Npot->s = NORTH;

	Spot = new Hole;
	Spot->m_beans = 0;
	Spot->holeNumber = 0;
	Spot->s = SOUTH;
	
	Npot->next = Spot;
	Spot->next = Npot;
	
	Hole* p1 = Npot;
	Hole* p2 = Spot;

	for (int i = 1; i <= nHoles; i++)
	{
		Hole* nHole = new Hole;
		nHole->m_beans = nInitialBeansPerHole;
		nHole->holeNumber = i;
		nHole->s = NORTH;
		nHole->next = p2->next;
		p2->next = nHole;

		Hole* sHole = new Hole;
		sHole->m_beans = nInitialBeansPerHole;
		sHole->holeNumber = nHoles - i + 1;
		sHole->s = SOUTH;
		sHole->next = p1->next;
		p1->next = sHole;
	}
}

Board::Board(const Board& other)
{
	Npot = new Hole;
	Spot = new Hole;

	Npot->s = NORTH;
	Spot->s = SOUTH;
	Npot->next = Spot;
	Spot->next = Npot;
	Npot->holeNumber = 0;
	Spot->holeNumber = 0;
	Npot->m_beans = other.Npot->m_beans;
	Spot->m_beans = other.Spot->m_beans;

	this->m_holes = other.m_holes;
	this->m_nInitialBeansPerHole = other.m_nInitialBeansPerHole;

	Hole* p = other.Npot;
	Hole* q = other.Spot;
	int i = 1;
	for (; p->next != other.Spot;)
	{
		Hole* northGuy = new Hole;
		northGuy->holeNumber = i;
		northGuy->next = Spot->next;
		northGuy->s = NORTH;
		northGuy->m_beans = other.beans(NORTH, i);
		Spot->next = northGuy;
		q = q->next;


		Hole* southGuy = new Hole;
		southGuy->holeNumber = other.m_holes - i + 1;
		southGuy->next = Npot->next;
		southGuy->s = SOUTH;
		southGuy->m_beans = other.beans(SOUTH, southGuy->holeNumber);
		Npot->next = southGuy;
		p = p->next;

		i++;
	}
}

Board& Board::operator=(const Board& other)  //assignment operator
{
	if (this != &other)
	{
		Board temp(other);		//create a new temp board that enables all the elements to be copied
		swap(temp);					//swap with the temp sequence
	}
	return *this;
}

Board::~Board()
{
	while (Npot != Npot->next)
	{
		Hole* p = Npot->next;
		Npot->next = p->next;
		delete p;
	}

	delete Npot;
}

int Board::holes() const
{
	return m_holes;
}

int Board::beans(Side s, int hole) const
{
	if (0 < hole && hole > m_holes)
		return -1;

	if (s == SOUTH && hole == 0)
		return Spot->m_beans;
	else if (s == NORTH && hole == 0)
		return Npot->m_beans;

	Hole* p = nullptr;
	if (s == NORTH)
		p = Spot->next;
	else
		p = Npot->next;

	while (p->holeNumber != hole)
	{
		p = p->next;
	}

	return p->m_beans;
}

int Board::beansInPlay(Side s) const
{
	Hole* p = nullptr;
	int count = 0;

	if (s == SOUTH)
	{
		p = Npot->next;
		for (; p != Spot; p = p->next)
		{
			count += p->m_beans;
		}
	}
	else
	{ 
		p = Spot->next;
		for (; p != Npot; p = p->next)
		{
			count += p->m_beans;
		}
	}
	return count;
}

int Board::totalBeans() const
{
	Hole* p = Spot;
	int count = 0;
	
	do {
		count += p->m_beans;
		p = p->next;

	} while (p != Spot);
	
	return count;
}

bool Board::sow(Side s, int hole, Side& endSide, int& endHole)
{
	if (hole <= 0 || hole > m_holes)
		return false;

	Hole* p;
	int BEANS = 0;
	if (s == SOUTH)
	{
		p = Npot->next;
		for (; p->holeNumber != hole; p = p->next)
			;
	}

	else
	{
		p = Spot->next;
		for (; p->holeNumber != hole; p = p->next)
			;
	}

	if (p->m_beans == 0)
		return false;

	BEANS = p->m_beans;
	p->m_beans = 0;

	for (; BEANS != 0; BEANS--)
	{
		if (p->holeNumber == 0 && p->s != s)
		{
			p = p->next;
		}

		if (BEANS == 1 && p->next->s == s && p->next->holeNumber != 0 && p->next->m_beans == 0)    /////CODE FOR CAPTURE
		{
			if (beans(opponent(s), p->next->holeNumber) != 0)
			{
				moveToPot(opponent(s), p->next->holeNumber, s);
				Spot->m_beans++;
			}
			else
			{
				p->next->m_beans++;
				p = p->next;
			}
		}
			
		else
		{
			p = p->next;
			p->m_beans += 1;
		}
	}

	endSide = p->s;
	endHole = p->holeNumber;

	if (beansInPlay(s) == 0)
	{
		for (int i = 1; i <= m_holes; i++)
			moveToPot(opponent(s), i, opponent(s));
	}
	return true;
}

bool Board::moveToPot(Side s, int hole, Side potOwner)
{
	if (hole <= 0)
		return false;

	Hole* p;
	if (s == SOUTH)
		p = Npot;
	else
		p = Spot;

	for (; p->holeNumber != hole; p = p->next)
		;

	if (potOwner == SOUTH)
		Spot->m_beans += p->m_beans;
	else
		Npot->m_beans += p->m_beans;

	p->m_beans = 0;
	return true;
}

bool Board::setBeans(Side s, int hole, int beans)
{
	if (hole <= 0 || beans < 0)
		return false;

	Hole* p;
	if (s == SOUTH)
		p = Npot;
	else
		p = Spot;

	for (; p->holeNumber != hole; p = p->next)
		;

	p->m_beans = beans;

	return true;
}

void Board::swap(Board& other)
{
	Hole* p = Npot;			
	Hole* q = Spot;
	int holes = m_holes;		
	int initialBeans = m_nInitialBeansPerHole;

	Npot = other.Npot;		
	m_holes = other.m_holes;
	m_nInitialBeansPerHole = other.m_nInitialBeansPerHole;

	other.Npot = p;			
	other.Spot = q;
	other.m_holes = holes;
	other.m_nInitialBeansPerHole = initialBeans;
}
