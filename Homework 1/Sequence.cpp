#include "Sequence.h"
#include <iostream>

Sequence::Sequence()
{
	counter = 0;
}

bool Sequence::empty() const
{  
	// Return true if the sequence is empty, otherwise false.
	return (counter == 0);
}

int Sequence::size() const
{
	// Return the number of items in the sequence.
	return counter;
}

int Sequence::insert(int pos, const ItemType& value)
{
// Insert value into the sequence so that it becomes the item at
// position pos.  The original item at position pos and those that
// follow it end up at positions one higher than they were at before.
// Return pos if 0 <= pos <= size() and the value could be
// inserted.  (It might not be, if the sequence has a fixed capacity,
// e.g., because it's implemented using a fixed-size array.)  Otherwise,
// leave the sequence unchanged and return -1.  Notice that
// if pos is equal to size(), the value is inserted at the end.

	if (pos >= 250 || pos < 0)
	{
		return false;
	}

	else
	{ 
		for (int i = counter - 1; i >= pos; i--)
		{
			sequence[i+1] = sequence[i];
		}

		counter++;
		sequence[pos] = value;

		return pos;
	}
}


int Sequence::insert(const ItemType& value)
{
	// Let p be the smallest integer such that value <= the item at
	// position p in the sequence; if no such item exists (i.e.,
	// value > all items in the sequence), let p be size().  Insert
	// value into the sequence so that it becomes the item at position
	// p.  The original item at position p and those that follow it end
	// up at positions one higher than before.  Return p if the value
	// was actually inserted.  Return -1 if the value was not inserted
	// (perhaps because the sequence has a fixed capacity and is full).

	if (counter >= 250)
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
				return counter-1;
			}
			i++;
		}

		for (int j = counter; j >= i; j--)
		{
			sequence[j+1] = sequence[j];
		}

		sequence[i] = value;
		counter++;
		return i;

	}
}

bool Sequence::erase(int pos) 
{
	// If 0 <= pos < size(), remove the item at position pos from
	// the sequence (so that all items that followed that item end up at
	// positions one lower than they were at before), and return true.
	// Otherwise, leave the sequence unchanged and return false.
	if (pos >= counter)
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
	// If 0 <= pos < size(), copy into value the item at position pos
	// of the sequence and return true.  Otherwise, leave value unchanged
	// and return false.

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
	// If 0 <= pos < size(), replace the item at position pos in the
	// sequence with value and return true.  Otherwise, leave the sequence
	// unchanged and return false.
	if (pos > counter)
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
	// Let p be the smallest integer such that value == the item at
	// position p in the sequence; if no such item exists, let p be -1.
	// Return p.

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
	// Exchange the contents of this sequence with the other one.

	Sequence swapsequence;

	for (int i = 0; i < DEFAULT_MAX_ITEMS; i++)
	{
		swapsequence.sequence[i] = sequence[i];
	}
	swapsequence.counter = counter;
	
	for (int j = 0; j < DEFAULT_MAX_ITEMS; j++)
	{
		sequence[j] = other.sequence[j];
	}

	counter = other.counter;

	for (int k = 0; k < DEFAULT_MAX_ITEMS; k++)
	{
		other.sequence[k] = swapsequence.sequence[k];
		//other.sequence[k] = swapsequence[k];
	}
	other.counter = swapsequence.counter;
}

void Sequence::dump() const
{
	for (int i = 0; i < counter; i++)
	{
		cerr << sequence[i] << endl;
	}
}