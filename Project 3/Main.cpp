#include "Board.h"
#include "Side.h"
#include "Game.h"
#include "Player.h"
#include <iostream>
#include <cassert>
using namespace std;

#if defined(_MSC_VER)  &&  !defined(_DEBUG)
#include <iostream>
#include <windows.h>
#include <conio.h>

struct KeepWindowOpenUntilDismissed
{
	~KeepWindowOpenUntilDismissed()
	{
		DWORD pids[1];
		if (GetConsoleProcessList(pids, 1) == 1)
		{
			std::cout << "Press any key to continue . . . ";
			_getch();
		}
	}
} keepWindowOpenUntilDismissed;
#endif

void doBoardTests()
{
	Board b(3, 2);
	assert(b.holes() == 3); 
	assert(b.totalBeans() == 12);
	assert(b.beans(SOUTH, POT) == 0);
	assert(b.beansInPlay(SOUTH) == 6);
	b.setBeans(SOUTH, 1, 1);
	b.moveToPot(SOUTH, 2, SOUTH);
	assert(b.totalBeans() == 11);
	assert(b.beans(SOUTH, 1) == 1);
	assert(b.beans(SOUTH, 2) == 0);
	assert(b.beans(SOUTH, POT) == 2);
	assert(b.beansInPlay(SOUTH) == 3);
	Side es;
	int eh;
	b.sow(SOUTH, 3, es, eh);
	assert(es == NORTH);
	assert(eh == 3);
	assert(b.beans(SOUTH, 3) == 0);
	assert(b.beans(NORTH, 3) == 3);
	assert(b.beans(SOUTH, POT) == 3);
	assert(b.beansInPlay(SOUTH) == 1);
	assert(b.beansInPlay(NORTH) == 7);

	Board b1(3,2);
	assert(b1.beansInPlay(SOUTH) == 6);
	assert(b1.beansInPlay(NORTH) == 6);
	assert(b1.holes() == 3);
	assert(b1.setBeans(SOUTH,2,3));
	assert(!b1.setBeans(SOUTH, 0, 4));
	assert(b1.totalBeans() == 13);
	assert(b1.beans(SOUTH,1) == 2);
	assert(b1.beans(SOUTH, 0) == 0);

	Side endside = NORTH;
	int endhole = 0;
	assert(b1.sow(SOUTH, 1, endside, endhole));
	assert(endside == SOUTH);
	assert(endhole == 3);
	assert(b1.beans(SOUTH, 1) == 0);
	assert(b1.beans(SOUTH,2) == 4);
	assert(b1.beans(SOUTH, 3) == 3);
	assert(b1.sow(SOUTH, 3, endside, endhole));
	assert(endside == NORTH);
	assert(endhole == 2);
	assert(b1.beans(SOUTH, 3) == 0);
	assert(b1.beans(SOUTH,0) == 1);
	assert(b1.beans(NORTH, 3) == 3 && b1.beans(NORTH, 2) == 3);
	assert(b1.beans(NORTH, 0) == 0);

}

int mainx()
{
	doBoardTests();
	cout << "Passed all tests" << endl;
	return 0;
}

int badPlayersPlaying()
{
	BadPlayer hp("Marge");
	BadPlayer bp("Homer");
	Board b(3, 2);
	Game g(b, &hp, &bp);
	g.play();
	
	return 0;
}

///////////////////////////////////////

void doPlayerTests()
{
	HumanPlayer hp("Marge");
	assert(hp.name() == "Marge"  &&  hp.isInteractive());
	BadPlayer bp("Homer");
	assert(bp.name() == "Homer" && !bp.isInteractive());
	SmartPlayer sp("Lisa");
	assert(sp.name() == "Lisa" && !sp.isInteractive());
	Board b(3, 2);
	b.setBeans(SOUTH, 2, 0);
	cout << "=========" << endl;
	int n = hp.chooseMove(b, SOUTH);
	cout << "=========" << endl;
	assert(n == 1 || n == 3);
	n = bp.chooseMove(b, SOUTH);
	assert(n == 1 || n == 3);
	n = sp.chooseMove(b, SOUTH);
	assert(n == 1 || n == 3);
}

int mainxxx()
{
	doPlayerTests();
	cout << "Passed all tests" << endl;
	return 0;
}

//////////////////////////////////////////

void doGameTests()
{
	BadPlayer bp1("Bart");
	BadPlayer bp2("Homer");
	Board b(3, 0);
	b.setBeans(SOUTH, 1, 2);
	b.setBeans(NORTH, 2, 1);
	b.setBeans(NORTH, 3, 2);
	Game g(b, &bp1, &bp2);
	bool over;
	bool hasWinner;
	Side winner;
	//    Homer
	//   0  1  2
	// 0         0
	//   2  0  0
	//    Bart
	g.display();
	g.status(over, hasWinner, winner);
	assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 0 &&
		g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 1 && g.beans(NORTH, 3) == 2 &&
		g.beans(SOUTH, 1) == 2 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 0);

	g.move();
	//   0  1  0
	// 0         3
	//   0  1  0
	g.display();
	g.status(over, hasWinner, winner);
	assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 3 &&
		g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 1 && g.beans(NORTH, 3) == 0 &&
		g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 1 && g.beans(SOUTH, 3) == 0);

	g.move();
	//   1  0  0
	// 0         3
	//   0  1  0
	g.display();
	g.status(over, hasWinner, winner);
	assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 3 &&
		g.beans(NORTH, 1) == 1 && g.beans(NORTH, 2) == 0 && g.beans(NORTH, 3) == 0 &&
		g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 1 && g.beans(SOUTH, 3) == 0);

	g.move();
	//   1  0  0
	// 0         3
	//   0  0  1
	g.display();
	g.status(over, hasWinner, winner);
	assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 3 &&
		g.beans(NORTH, 1) == 1 && g.beans(NORTH, 2) == 0 && g.beans(NORTH, 3) == 0 &&
		g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 1);

	g.move();
	//   0  0  0
	// 1         4
	//   0  0  0
	g.display();
	g.status(over, hasWinner, winner);
	assert(over && g.beans(NORTH, POT) == 1 && g.beans(SOUTH, POT) == 4 &&
		g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 0 && g.beans(NORTH, 3) == 0 &&
		g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 0);
	assert(hasWinner && winner == SOUTH);
}

int mainXX()
{
	doGameTests();
	cout << "Passed all tests" << endl;
	return 0;
}

///////////////////////////////////

void playAgainstSmartPlayer()
{
	SmartPlayer SM("Smart");
	BadPlayer BP("Bad Player");

	Board b(5, 3);
	Game g(b, &SM, &BP);

	g.play();
}

int main()
{
	playAgainstSmartPlayer();
	return 0;
}

////////////////////////////////

int mainYY()
{
	HumanPlayer HP("Human");
	BadPlayer BP("Bad");

	Board B(3, 2);

	Game g(B, &HP, &BP);
	g.play();

	return 0;
}
