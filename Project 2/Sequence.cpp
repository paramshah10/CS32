#include "Sequence.h"
#include <iostream>

using namespace std;

Sequence::Sequence()
{
	head = new Node;	//we create a head node (dummy node) to initialise the pointers
	head->next = head;
	head->prev = head;
	m_size = 0;
}


Sequence::Sequence(const Sequence& other) //copy constructor
{
	head = new Node;		//create a dummy node
	head->next = head;
	head->prev = head;
	this->m_size = 0;
	
	int i = 0;
	for (Node* temp = other.head->next; temp != other.head; temp = temp->next)		//iterate through the list
	{
		this->insert(i,temp->data);		//insert elements into the 'other sequence'
		i++;
	}
}


Sequence& Sequence::operator=(const Sequence& other)  //assignment operator
{
	if (this != &other)
	{
		Sequence temp(other);		//create a new temp sequence that enables all the elements to be copied
		swap(temp);					//swap with the temp sequence
	}
	return *this;
}


Sequence::~Sequence() //Destructor
{
	while (head != head->next) {              // delete all nodes until left with the head node
		Node* del = head->next;
		head->next = del->next;
		del->next->prev = head;
		delete del;       // delete the current entry
	}

	delete head;	//delete the head node
}


bool Sequence::empty() const	//function to determine if the list is empty
{
	return (m_size == 0);
}


int Sequence::size() const		//function to determine the size of the list
{
	return m_size;
}


int Sequence::insert(int pos, const ItemType& value)		//function for adding a new node at a position in the linked list
{
	if (pos > m_size)			//if trying to add beyond the size of the list
	{
		return -1;
	}

	else if (pos == m_size)		//edge case when trying to add at the end of the list
	{
		Node*m;
		for (m = head->next; m->next != head; m = m->next)
		{}

		Node* newGuy = new Node;
		newGuy->data = value;
		newGuy->prev = m;
		newGuy->next = m->next;
		m->next = newGuy;
		m_size++;
		return pos;

	}

	else			//for adding anywhere in the list except at the end
	{
		Node* m;
		int i = 0;
		for (m = head->next; m->next != head && i < pos; m = m->next)		//loop to reach the position where the new value needs to be added
		{
			i++;
		}

		Node* newGuy = new Node;		//create a new node that needs to be added
		newGuy->data = value;
		newGuy->prev = m->prev;
		m->prev->next = newGuy;
		newGuy->next = m;
		m->prev = newGuy;

		m_size++;			//increase the size since new element was added
		return pos;
	}
}


int Sequence::insert(const ItemType& value)		//function to add an element whereever the value <= the value the a position in the list
{

	if (m_size == 0)		//handle the case when the list is empty
	{
		head->next = new Node;
		head->next->data = value;
		head->next->next = head;
		head->next->prev = head;
		m_size++;
		return 0;
	}

	else		//case if the list is not empty
	{
		Node* m;		//create a temporary pointer to iterate through the linked list
		int i = 0;
		for (m = head->next; m->next != head && value > m->data; m = m->next)	//iterate till we reach the end or when value <= the value at that position
		{
			i++;
		}

		if (m->next == head && value > m->data)		//if its at the end and is greater than the all the vlaue in the list then consider this
		{
			Node* newGuy = new Node;			//create a new node to be added
			newGuy->data = value;
			newGuy->next = m->next;			//add it at the end of the list
			m->next = newGuy;
			newGuy->prev = m;
			m_size++;
			return m_size - 1;
		}

		else									//any case other than the above case
		{
			Node* newGuy = new Node;		//create a new node to be added
			newGuy->data = value;
			newGuy->next = m;				//add it before the current element
			newGuy->prev = m->prev;
			m->prev->next = newGuy;
			m->prev = newGuy;
			m_size++;
			return i;
		}
	}
}


bool Sequence::erase(int pos)		//function to erase an existing node at the given position
{
	if (pos >= m_size)		//if trying to erase at a position beyond the size of the list
	{
		return false;
	}

	Node* p;		//we create a dummy node
	int i = 0;
	for (p = head; i <= pos; p = p->next)	//iterate till we hit the position
	{
		i++;
	}

	p->prev->next = p->next;
	p->next->prev = p->prev;
	delete p;		//delete the node
	m_size--;
	return true;
}


int Sequence::remove(const ItemType& value)		//function to remove an all nodes that have value equal to the parameter passed
{
	int counter = 0;
	int i = 0;

	for (Node* p = head->next; i < m_size; p = p->next)	//iterates through the list to find the element
	{
		if (p->data == value)
		{
			Node* temp = p;			//create a temporary node 
			p = p->prev;
			temp->prev->next = temp->next;
			temp->next->prev = temp->prev;
			delete temp;		//delete the temporary pointer that points to the node that has to be deleted
			m_size--;
			counter++;
			i--;	//i decreases since the size also decreases
		}
		i++;
	}
	return counter;	//return counter
}


bool Sequence::get(int pos, ItemType& value) const
{
	if (pos >= m_size)	//
	{
		return false;
	}

	else
	{
		Node* p;		//we create a dummy node
		int i = 0;
		for (p = head->next; i < pos; p = p->next)	//iterate till we hit the position
		{
			i++;
		}	

		value = p->data;
		return true;
	}
}


bool Sequence::set(int pos, const ItemType& value)
{
	if (pos >= m_size)
	{
		return false;
	}

	else
	{
		Node* p;		//we create a dummy node
		int i = 0;
		for (p = head; i <= pos; p = p->next)	//iterate till we hit the position
		{
			i++;
		}

		p->data = value;		//set the parameter to the value at the position
		return true;
	}
}


int Sequence::find(const ItemType& value) const
{
	int i = 0;
	int counter = -1;

	for (Node* p = head->next; p != head; p = p->next)		//loop to iterate through the list
	{
		if (p->data == value)		//if the value at that position is equal to the parameter passed
		{
			counter = i;	//set counter to the position at which it's equal
			break;
		}
		i++;
	}
	return counter;	//return the position at which it was found
}


void Sequence::swap(Sequence& other)
{
	Node* p = head;			//create a temp 3rd pointer
	int SIZE = m_size;		//create a temp int

	head = other.head;		//switch the heads
	m_size = other.m_size;

	other.head = p;			//switch the sizes
	other.m_size = SIZE;
}


int subsequence(const Sequence& seq1, const Sequence& seq2)
{
	ItemType counter1;
	ItemType counter2;
	int counter = -1;
	int i = 0;

	for (int j = 0; j < seq1.size(); j++)		//iterate the bigger sequence i.e. seq1
	{
		i = 0;
		seq2.get(i, counter2);				//get the first element of the smaller sequence i.e. seq2
		seq1.get(j, counter1);				//get the elements of seq1 one by one

 		if (counter1 == counter2)			//if we find the first element of seq2 in seq1
		{
			counter = j;			//set counter to the position in the seq1
			for (; i < seq2.size() && j < seq1.size(); i++)		//iterate through seq1
			{
				seq2.get(i + 1, counter2);		//get the next element of seq1
				seq1.get(j + 1, counter1);		//get the next element	of seq2
													
				if (counter2 != counter1)		//if the next elements of seq1 and seq2 are not same then break of the loop
				{
					counter = -1;
					break;
				}
				
				if (i + 2 == seq2.size())		//if all the elements are same till we reach the end of seq2 then return counter
				{
					return counter;
				}
				j++;
			}
		}
	}
	return counter;
}

void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result)
{
	ItemType counter1;
	int count = 0;

	int i = seq1.size();
	int j = seq2.size();
	int k = result.size();

	if (seq1.size() == 0)		//if seq1 is empty then just add the elements of seq2
	{
		for (; count < j; count++)		//loop through seq2
		{
			seq2.get(count, counter1);
			result.insert(result.size(), counter1);
		}
	}

	else if (seq2.size() == 0)		//if seq2 is empty then just add the elements of seq1
	{
		for (; count < i; count++)		//loop through seq1
		{
			seq1.get(count, counter1);
			result.insert(result.size(), counter1);
		}
	}

	else		//if seq1 or seq2 is empty
	{
		if (i < j)		//if seq2 is longer than seq1
		{
			int diff = j - i;
			for (; i > 0; i--)		//add till the end of seq1
			{
				seq1.get(count, counter1);
				result.insert(result.size(), counter1);
				seq2.get(count, counter1);
				result.insert(result.size(), counter1);
				count++;
			}

			for (; diff > 0; diff--)		//add the rest of the seq2 elements
			{
				seq2.get(count, counter1);
				result.insert(result.size(), counter1);
				count++;
			}
		}

		else	//if seq1 is longer than seq2
		{
			int diff = i - j;
			for (; j > 0; j--)		//add till the end of seq2
			{
				seq1.get(count, counter1);
				result.insert(result.size(), counter1);
				seq2.get(count, counter1);
				result.insert(result.size(), counter1);
				count++;
			}

			for (; diff > 0; diff--)		//add the rest of the seq1 elements
			{
				seq1.get(count, counter1);
				result.insert(result.size(), counter1);
				count++;
			}
		}
	}

	for (; k > 0; k--)	//remove the initial elements of result
	{
		result.erase(0);
	}
}

void Sequence::dump() const			//print all the elements of the linked list
{
	for (Node* p = head->next; p != head; p = p->next)		//iterate through the list till we hit the end
	{
		cerr << p->data << endl;
	}
}