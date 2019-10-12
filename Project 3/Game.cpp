#include "Game.h"
#include <iostream>

using namespace std;

Game::Game(const Board& b, Player* south, Player* north) : m_board(b), m_south(south), m_north(north), whoseMoveIsIt(SOUTH)
{ }

void Game::display() const
{
	cout << "                   " << m_north->name() << "              " << endl;
	cout << "              ";

	for (int i = 0; i < m_board.holes(); i++)
	{
		cout << "  " << i + 1 << ".";
	}

	cout << endl << "                ";
	for (int i = 0; i < m_board.holes(); i++)
	{
		cout << "----";
	}
	cout << endl << "              ";

	for (int i = 1; i <= m_board.holes(); i++)
	{
		cout << "   " << beans(NORTH, i);
	}

	cout << endl;

	cout << m_north->name() << "'s pot " << beans(NORTH, 0); 
	for (int i = 0; i < m_board.holes(); i++)
	{
		cout << "     ";
	}
	cout << "  " << beans(SOUTH, 0) << " " << m_south->name() << "'s pot" << endl;

	cout << "              ";

	for (int i = 1; i <= m_board.holes(); i++)
	{
		cout << "   " << beans(SOUTH, i);
	}

	cout << endl <<  "                ";
	for (int i = 0; i < m_board.holes(); i++)
	{
		cout << "----";
	}
	cout << endl << "              ";
	for (int i = 0; i < m_board.holes(); i++)
	{
		cout << "  " << i + 1 << ".";
	}
	cout << endl << "                   " << m_south->name() << "              " << endl << endl;
}

void Game::status(bool& over, bool& hasWinner, Side& winner) const
{
	if (m_board.beansInPlay(SOUTH) != 0 && m_board.beansInPlay(NORTH) != 0)
		over = false;
	
	else
	{
		over = true;
		if (beans(SOUTH, 0) != beans(NORTH, 0))
		{
			hasWinner = true;
			if (beans(SOUTH, 0) > beans(NORTH, 0))
				winner = SOUTH;
			else
				winner = NORTH;
		}

		else
			hasWinner = false;
	}
}

bool Game::move()
{
	bool over;
	bool winner;
	Side side;
	status(over, winner, side);

	if (over)
		return false;
	else
	{
		if (whoseMoveIsIt == SOUTH)
		{
			if (m_board.beansInPlay(SOUTH) == 0)
			{
				over = true;
				return false;
			}

			int play = m_south->chooseMove(m_board, whoseMoveIsIt);
			int endhole;

			if (!(m_south->isInteractive()))
				cout << m_south->name() << " chose hole " << play << endl;
			
			if (!m_board.sow(whoseMoveIsIt, play, side, endhole))
				move();
			
			if (side == whoseMoveIsIt && endhole == 0)
			{
				display();
				move();
			}
			else
				whoseMoveIsIt = opponent(whoseMoveIsIt);
		}
		else
		{
			if (m_board.beansInPlay(NORTH) == 0)
			{
				over = true;
				return false;
			}

			int play = m_north->chooseMove(m_board, whoseMoveIsIt);
			int endhole;

			if (!(m_north->isInteractive()))
				cout << m_north->name() << " chose hole " << play << endl;

			if (!m_board.sow(whoseMoveIsIt, play, side, endhole))
				move();

			if (side == whoseMoveIsIt && endhole == 0)
			{
				display();
				move();
			}

			else
				whoseMoveIsIt = opponent(whoseMoveIsIt);
		}
		return true;
	}
}

void Game::play()
{
	bool Status = false;
	bool win;
	Side winner;

	display();
	status(Status, win, winner);
	while (!Status)
	{
		move();
		display();
		status(Status, win, winner);
	}

	if (win)
	{
		if (winner == SOUTH)
			cout << m_south->name() << " wins!" << endl;
		else
			cout << m_north->name() << " wins!" << endl;
	}

	else
		cout << "It was a tie";		
}

int Game::beans(Side s, int hole) const
{
	return m_board.beans(s, hole);
}