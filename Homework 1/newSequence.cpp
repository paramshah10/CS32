#include "newSequence.h"

Sequence::Sequence(int a)
{
	if (a < 0)
	{
		exit(1);
	}

	sequence = new ItemType[a];
	len = a;
}


Sequence::Sequence(const Sequence& other)
{
	len = other.len;
	counter = other.counter;
	sequence = new ItemType[other.counter];
	for (int i = 0; i < counter; i++) {
		*(sequence + i) = *(other.sequence + i);
	}
}


Sequence& Sequence::operator=(const Sequence& other)
{
	Sequence temp(other);
	swap(temp);
	return *this;
}

Sequence::~Sequence()
{
	delete []sequence;
}


bool Sequence::empty() const
{
	return (counter == 0);
}


int Sequence::size() const 
{
	return counter;
}


int Sequence::insert(int pos, const ItemType& value)
{
	if (pos >= len || pos < 0)
	{
		return false;
	}

	else if (counter == len)
	{
		return false;
	}

	else
	{
		for (int i = counter - 1; i >= pos; i--)
		{
			sequence[i + 1] = sequence[i];
		}

		counter++;
		sequence[pos] = value;

		return pos;
	}
}


int Sequence::insert(const ItemType& value)
{
	if (counter >= len)
	{
		return -1;
	}

	else if (counter == 0)
	{
		sequence[0] = value;
		counter++;

		return 0;
	}

	else
	{
		int i = 0;

		while (sequence[i] <= value)
		{
			if (i == counter - 1)
			{
				sequence[counter] = value;
				counter++;
				return counter - 1;
			}
			i++;
		}

		for (int j = counter; j >= i; j--)
		{
			sequence[j + 1] = sequence[j];
		}

		sequence[i] = value;
		counter++;
		return i;

	}
}


bool Sequence::erase(int pos)
{
	if (pos >= len)
	{
		return false;
	}
	else
	{
		for (int i = pos - 1; i < counter; i++)
		{
			sequence[i] = sequence[i + 1];
		}
		return true;
	}
}


int Sequence::remove(const ItemType& value)
{
	int removed = 0;
	// Erase all items from the sequence that == value.  Return the
	// number of items removed (which will be 0 if no item == value).
	for (int i = 0; i < counter; i++)
	{
		if (sequence[i] == value)
		{
			for (int j = i; j < counter; j++)
			{
				sequence[j] = sequence[j + 1];
			}
			removed++;
			counter--;
		}
	}
	return removed;
}


bool Sequence::get(int pos, ItemType& value) const
{
	if (pos > counter)
	{
		return false;
	}

	else
	{
		value = sequence[pos];
		return true;
	}
}


bool Sequence::set(int pos, const ItemType& value)
{
	if (pos > len)
	{
		return false;
	}

	else
	{
		sequence[pos] = value;
		return true;
	}
}


int Sequence::find(const ItemType& value) const
{
	int Find = -1;
	for (int i = 0; i < counter; i++)
	{
		if (sequence[i] == value)
		{
			Find = i;
			break;
		}
	}

	return Find;
}


void Sequence::swap(Sequence& other)
{
	ItemType* ptr = sequence;
	sequence = other.sequence;
	other.sequence = ptr;

	int m_counter = counter;
	counter = other.counter;
	other.counter = m_counter;

	int m_len = len;
	len = other.len;
	other.len = m_len;
}