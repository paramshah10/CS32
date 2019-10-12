#include "ScoreList.h"

ScoreList::ScoreList() 
{
	// Create an empty score list.
	m_len = 0;
}

bool ScoreList::add(unsigned long score) 
{
	// If the score is valid (a value from 0 to 100) and the score list
	// has room for it, add it to the score list and return true.
	// Otherwise, leave the score list unchanged and return false.
	if (score > 100 || list.size() > 250)
	{
		return false;
	}

	else
	{
		list.insert(score);
		m_len++;
		return true;
	}
}

bool ScoreList::remove(unsigned long score) 
{
	// Remove one instance of the specified score from the score list.
	// Return true if a score was removed; otherwise false.

	int pos = 0;
	pos = list.find(score);

	if (pos == -1)
	{
		return false;
	}
	else
	{
		list.erase(pos);
		m_len--;
		return true;
	}
}

int ScoreList::size() const 
{
	// Return the number of scores in the list.
	return m_len;
}

unsigned long ScoreList::minimum() const 
{
	// Return the lowest score in the score list.  If the list is
	// empty, return NO_SCORE.

	if (m_len == 0)
	{
		return NO_SCORE;
	}
	else
	{	
		unsigned long lowest1 = 101;
		unsigned long lowest2;

		for (int i = 0; i < m_len; i++)
		{
			list.get(i, lowest2);
			if (lowest2 < lowest1)
			{
				lowest1 = lowest2;
			}
		}
		return lowest1;
	}
}

unsigned long ScoreList::maximum() const
{
	// Return the highest score in the score list.  If the list is
	// empty, return NO_SCORE.
	if (m_len == 0)
	{
		return NO_SCORE;
	}

	else
	{
		unsigned long lowest3 = 0;
		unsigned long lowest4;

		for (int i = 0; i < m_len; i++)
		{
			list.get(i, lowest4);
			if (lowest4 > lowest3)
			{
				lowest3 = lowest4;
			}
		}
		return lowest3;
	}
}