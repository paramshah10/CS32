#define MAX_DEPTH 4

#include "Player.h"
#include <chrono>
#include <future>
#include <atomic>
#include <new>
#include <iostream>
#include <algorithm>
#include <climits>

using namespace std;

class AlarmClock
{
public:
	AlarmClock(int ms)
	{
		m_timedOut = false;
		m_isRunning = true;
		m_alarmClockFuture = std::async([=]() {
			for (int k = 0; k < ms && m_isRunning; k++)
				std::this_thread::sleep_for(std::chrono::milliseconds(1));
			if (m_isRunning)
				m_timedOut = true;
		});
	}

	~AlarmClock()
	{
		m_isRunning = false;
		m_alarmClockFuture.get();
	}

	bool timedOut() const
	{
		return m_timedOut;
	}

	AlarmClock(const AlarmClock&) = delete;
	AlarmClock& operator=(const AlarmClock&) = delete;
private:
	std::atomic<bool> m_isRunning;
	std::atomic<bool> m_timedOut;
	std::future<void> m_alarmClockFuture;
};

void minimax(const Board& b, Side s, int& bestHole, int& value, AlarmClock& ac, int depth, const Side initSide);
int evaluate(const Board& b, Side s, int hole, const Side initSide);
//void status(bool& over, bool& hasWinner, Side& winner);


Player::Player(std::string name)
{
	m_name = name;
}

std::string Player::name() const
{
	return m_name;
}

bool Player::isInteractive() const
{
	return false;
}

Player::~Player()
{
}

/////////////////////////// HUMAN PLAYER

HumanPlayer::HumanPlayer(std::string name) : Player(name)
{
}

bool HumanPlayer::isInteractive() const
{
	return true;
}

int HumanPlayer::chooseMove(const Board& b, Side s) const
{
	if (b.beansInPlay(s) == 0)
		return -1;
	int choosenHole;
	std::cout << "Choose a hole " << name() << " : ";
	std::cin >> choosenHole;

	if (b.beans(s, choosenHole) == 0)
	{
		std::cout << "No beans remaining in the hole" << std::endl;
		return chooseMove(b,s);
	}

	return choosenHole;
}

HumanPlayer::~HumanPlayer()
{
}

///////////////////// BAD PLAYER

BadPlayer::BadPlayer(std::string name) : Player(name)
{
}

bool BadPlayer::isInteractive() const
{
	return false;
}

int BadPlayer::chooseMove(const Board& b, Side s) const
{
	if (b.beansInPlay(s) == 0)
		return -1;

	else
	{
		if (s == NORTH)
		{
			for (int i = 1; i <= b.holes(); i++)
			{
				if (b.beans(s, i) != 0)
					return i;
				else
					continue;
			}
			return -1;
		}
		else
		{
			for (int i = b.holes(); i > 0; i--)
			{
				if (b.beans(s, i) != 0)
					return i;
				else
					continue;
			}
			return -1;
		}
	}
}

BadPlayer::~BadPlayer()
{
}

////////////////// SMART PLAYER

SmartPlayer::SmartPlayer(std::string name) : Player(name)
{
}

bool SmartPlayer::isInteractive() const
{
	return false;
}

int SmartPlayer::chooseMove(const Board& b, Side s) const
{
	int bestHole = 2;
	int value = 0;
	int depth = 7;
	AlarmClock ac(4900);
	minimax(b, s, bestHole, value, ac, depth, s);

	if (bestHole == -1)
	{
		bestHole = rand() % 1 + b.holes();
	}
	return bestHole;
}

SmartPlayer::~SmartPlayer()
{
}

void minimax(const Board& b, Side s, int& bestHole, int& value, AlarmClock& ac, int depth, const Side initSide)
{
	if (b.beansInPlay(s) == 0)
	{
		bestHole = -1;
		
		if (s == initSide)
		{
			if (b.beans(s, 0) > b.beans(opponent(s), 0))
				value = 99999;
			else if (b.beans(s, 0) < b.beans(opponent(s), 0))
				value = -99999;
			else
				value = 0;
			return;
		}
		else
		{
			if (b.beans(s, 0) > b.beans(opponent(s), 0))
				value = -99999;
			else if (b.beans(s, 0) < b.beans(opponent(s), 0))
				value = 99999;
			else
				value = 0;
			return;
		}
		// side parameter // if opponent negative of the value return
	}

	/////ADD DEPTH PARAMETER

	if (ac.timedOut() || depth == 0)
	{
		bestHole = -1;

		if (s == initSide)
		{
			if (b.beans(s, 0) > b.beans(opponent(s), 0))
				value = 99999;
			else if (b.beans(s, 0) < b.beans(opponent(s), 0))
				value = -99999;
			else
				value = 0;
			return;
		}
		else
		{
			if (b.beans(s, 0) > b.beans(opponent(s), 0))
				value = -99999;
			else if (b.beans(s, 0) < b.beans(opponent(s), 0))
				value = 99999;
			else
				value = 0;
			return;
		}
	}

	if (s == SOUTH)
	{
		if (b.beans(s, b.holes()) == 1)
		{
			bestHole = b.holes();
			value = evaluate(b, SOUTH, b.holes(), initSide);
			return;
		}
	}

	else if (s == NORTH)
	{
		if (b.beans(s, 1) == 1)
		{
			bestHole = 1;
			value = evaluate(b, NORTH, 1, initSide);
			return;
		}
	}

	int counter = 0;
	for (int i = 1; i <= b.holes(); i++)
	{
		if (b.beans(s, i) != 0 && !ac.timedOut())
		{
			counter++;
			Board temp = b;
			Side ES;
			int EH = 1;
			int v1 = -99999;
			int v2;
			int rand;

			temp.sow(s, i, ES, EH);

			if (EH == 0 && ES == s)
			{
				minimax(temp, s, rand, v2, ac, depth, initSide);
			}
			// conditions of game_play copy 
			// 
			if (b.beansInPlay(s) == 0)
			{
				if (b.beans(initSide, 0) > b.beans(opponent(initSide), 0))
				{
					value = 9999;
					bestHole = i;
				}
				else
				{
					value = -9999;
					bestHole = -1;
				}
			}
			else
			{
				minimax(temp, opponent(s), rand, v2, ac, depth - 1, initSide);
			}

			if (counter == 1)
			{
				value = evaluate(b, s, rand, initSide);
			}
			// counter 

			if (s == initSide)
			{
				if (v2 >= value)
				{
					bestHole = i;
					value = v2;
				}
			}
			// if opponent...return the minimum value
			else
			{
				if (v2 >= value)
				{
					bestHole = i;
					value = v2;
				}
			}
		}
	}
	return;
	
	//////////////////////////////
	/*
	if (s == side)
	{
		int score = b.beans(s, 0);
		int smartpits = 0;
		int val = INT_MIN; ////////check
		for (int i = 1; i <= b.holes(); i++)
		{
			int moveValue = score;
			Board copy = b;
			if (b.beans(s, i) != 0)
			{
				Side endside;
				int endhole = 0;
				copy.sow(s, i, endside, endhole);
				moveValue = b.beans(s, 0) - score;

				if (endhole == 0 && endside == s)
				{
					a[smartpits] = moveValue + minimax(copy, s, bestHole, val, depth + 1);
				} ///////check if you have to put val or something else;
				else
				{
					if (depth <= MAX_DEPTH)
					{
						a[smartpits] = moveValue - minimax(copy, opponent(side), bestHole, val, depth + 1);
					}
					else
					{
						a[smartpits] = moveValue;
					}
				}
			}
			else
			{
				a[smartpits] = -100000;
			}
			smartpits++;
			copy = b;
		}
	}
	else
	{
		int score = b.beans(s, 0);
		Board copy = b;
		for (int i = 1; i < b.holes(); i++)
		{
			int moveValue = score;
			if (b.beans(s, 0) != 0)
			{
				int endhole;
				Side endside;
				int val = INT_MIN;
				copy.sow(s, i, endside, endhole);
				moveValue = copy.beans(s, 0) - score;
				if (endhole == 0 && endside == s)
				{
					a[i] = moveValue + minimax(copy, s, bestHole, val, depth + 1);
				}
				else
				{
					if (depth <= MAX_DEPTH)
						a[i] = moveValue - minimax(copy, opponent(s), bestHole, val, depth + 1);
					else
						a[i] = moveValue;
				}
			}
			else
				a[i] = -100000;
			copy = b;
		}
	}*/

	////////////
	/*
	int score = b.beans(s, 0);
	int smartpits = 0;
	for (int i = 1; i <= b.holes(); i++)
	{
		Board temp = b;
		int moveValue = score;
		if (b.beans(s, i) != 0)
		{
			int endhole;
			Side endside;
			temp.sow(s, i, endside, endhole);
			moveValue = temp.beans(s, 0) - score;

			if (endhole == 0 && endside == s)
				a[smartpits] = moveValue + minimax(temp, s, bestHole, value, depth + 1);
			else
				a[smartpits] = moveValue;
		}
		else
			a[smartpits] = -100000;
		smartpits++;
		temp = b;
	}
	/////////////////////

	int max = INT_MIN;
	for (int i = 1; i <= b.holes(); i++)
	{
		if (a[i] > max)
		{
			max = a[i];
			bestHole = i;
		}
	}

	if (max == -100000)
	{
		if (side == s)
		{
			if (b.beans(s, 0) > b.beans(opponent(s), 0))
				max = 10000;
			else if (b.beans(s, 0) == b.beans(opponent(s), 0))
				max = -5000;
			else
				max = -10000;
		}
		else
		{
			if (b.beans(s, 0) > b.beans(opponent(s), 0))
				max = 10000;
			else if (b.beans(s, 0) == b.beans(opponent(s), 0))
				max = 5000;
			else
				max = -10000;
		}
	}

	depth--;
	delete [] a;
	return max;*/
}

int evaluate(const Board& b, Side s, int hole, const Side initSide)
{
	int diff = b.beans(s, 0) - b.beans(opponent(s), 0);

	if (s == initSide)
	{
		if (diff >= 0)
		{
			if (diff == 0)
				return 0;
			else if (diff < 2)
				return 10;
			else if (diff < 4)
				return 100;
			else if (diff < 7)
				return 1000;
			else
				return 10000;
		}
		else
		{
			if (diff < -7)
				return -10000;
			else if (diff < -4)
				return -1000;
			else if (diff < -2)
				return -100;
			else
				return -10;
		}
	}

	else
	{
		if (diff >= 0)
		{
			if (diff == 0)
				return 0;
			else if (diff < 2)
				return -10;
			else if (diff < 4)
				return -100;
			else if (diff < 7)
				return -1000;
			else
				return -10000;
		}
		else
		{
			if (diff < -7)
				return 10000;
			else if (diff < -4)
				return 1000;
			else if (diff < -2)
				return 100;
			else
				return 10;
		}
	}

	/*int difference = b.beans(s, 0) - b.beans(opponent(s), 0);

	Board temp = b;
	int endhole;
	Side endside;
	temp.sow(s, hole, endside, endhole);

	int newDifference = temp.beans(s, 0) - b.beans(opponent(s), 0);

	int theDiff = newDifference - difference;

	if (theDiff >= 0)
	{
		if (theDiff == 0)
			return 0;
		else if (theDiff >= 1)
			return 10;
		else if (theDiff > 3)
			return 100;
		else if (theDiff > 5)
			return 1000;
		else
			return 10000;
	}
	else
	{
		if (theDiff < 5)
			return -1000;
		else if (theDiff < 3)
			return -100;
		else if (theDiff < 0)
			return -10;
		else
			return -10000;
	}*/
}
