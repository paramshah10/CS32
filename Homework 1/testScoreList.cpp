#include "ScoreList.h"
#include <cassert>
#include <iostream>

using namespace std;

int mainx()
{
	ScoreList SL;

	SL.add(21);
	SL.add(3);
	SL.add(2);
	SL.add(99);
	SL.add(54);

	assert(SL.size() == 5);
	assert(SL.minimum() == 2);
	assert(SL.maximum() == 99);

	cerr << "Passed all tests" << endl;

	return 0;
}