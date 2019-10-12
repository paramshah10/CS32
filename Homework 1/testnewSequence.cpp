#include "newSequence.h"
#include <iostream>
#include <cassert>
using namespace std;

void test()
{
	Sequence s;
	s.insert(0, 10);
	s.insert(0, 20);
	assert(s.size() == 2);
	ItemType x = 999;
	assert(s.get(0, x) && x == 20);
	assert(s.get(1, x) && x == 10);


	Sequence a(1000);   // a can hold at most 1000 items
	Sequence b(5);      // b can hold at most 5 items
	Sequence c;         // c can hold at most DEFAULT_MAX_ITEMS items
	ItemType v = 1;

	// No failures inserting 5 items into b
	for (int k = 0; k < 5; k++)
		assert(b.insert(v) != -1);

	// Failure if we try to insert a sixth item into b
	assert(b.insert(v) == -1);

	// When two Sequences' contents are swapped, their capacities are
	// swapped as well:
	a.swap(b);
	assert(a.insert(v) == -1 && b.insert(v) != -1);

}

int main()
{
	test();
	cerr << "Passed all tests" << endl;
	return 0;
}