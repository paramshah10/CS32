#include "Sequence.h"
#include <iostream>
#include <cassert>

using namespace std;


int main()
{
	Sequence s;
	assert(s.empty());
	assert(s.find(42) == -1);
	assert(s.insert(42) == 0);
	assert(s.insert(54) == 1);
	assert(s.insert(50) == 1);
	assert(s.size() == 3 && s.find(42) == 0);
	
	s.dump();
	cerr << "Passed all tests" << endl;
}