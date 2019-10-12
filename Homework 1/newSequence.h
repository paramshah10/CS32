#ifndef NEWSEQUENCE_INCLUDED
#define NEWSEQUENCE_INCLUDED

#include <string>

using namespace std;

const int DEFAULT_MAX_ITEMS = 250;
using ItemType = unsigned long;

class Sequence
{
public:
	Sequence(int a = DEFAULT_MAX_ITEMS);
	Sequence(const Sequence& other);
	Sequence& operator=(const Sequence& other);
	~Sequence();
	bool empty() const;
	int size() const;
	int insert(int pos, const ItemType& value);
	int insert(const ItemType& value);
	bool erase(int pos);
	int remove(const ItemType& value);
	bool get(int pos, ItemType& value) const;
	bool set(int pos, const ItemType& value);
	int find(const ItemType& value) const;
	void swap(Sequence& other);
	void dump() const;

private:
	ItemType *sequence;
	int len;
	int counter;
};

#endif // !NEWSEQUENCE_INCLUDED
