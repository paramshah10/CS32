#ifndef BOARD_H
#define BOARD_H

#include "Side.h"

class Board
{
public:
	Board(int nHoles, int nInitialBeansPerHole);
	Board(const Board& other);
	Board& operator=(const Board& other);
	~Board();
	int holes() const;
	int beans(Side s, int hole) const;
	int beansInPlay(Side s) const;
	int totalBeans() const;
	bool sow(Side s, int hole, Side& endSide, int& endHole);
	bool moveToPot(Side s, int hole, Side potOwner);
	bool setBeans(Side s, int hole, int beans);
	void swap(Board& other);

private:
	int m_holes;
	int m_nInitialBeansPerHole;
	struct Hole
	{
		int holeNumber;
		int m_beans;
		Hole* next;
		Side s;
	};

	Hole* Npot;
	Hole* Spot;
};


#endif // !BOARD_H