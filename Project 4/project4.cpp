#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <functional>
#include <cassert>

using namespace std;

#define MAX_BUCKETS 102013		//max number of buckets in the hash table //selected a large prime number to reduce collisions
#define C4 4
#define C8 8
#define C16 16

struct Bucket	//Bucket struct to store the key value pairs in the hash table
{
	string key;
	int value;
	Bucket* next;
};


class HashTable		//HashTable class that creates a hash table, inserts key-value pairs in the table and search for keys in the hash table	//my implementation is of an open hash table
{
public:
	HashTable()		//default constructor that constructs the 3 hash tables (vector of bucket pointers) of that I will use to store my keys (with keys of sizes 16, 8, and 4)
	{
		m4_buckets.resize(MAX_BUCKETS);
		m8_buckets.resize(MAX_BUCKETS);
		m16_buckets.resize(MAX_BUCKETS);
		for (int i = 0; i < MAX_BUCKETS; i++)	//initialize all pointers to nullptrs
		{
			m4_buckets[i] = nullptr;
			m8_buckets[i] = nullptr;
			m16_buckets[i] = nullptr;
		}
	}

	void insert(string key, unsigned int value, int whichVector)	//function to insert new keys into the hash table
	{
		int bucket = hashFunc(key);		//hashing the key to the index number in the vector

		if (whichVector == 4)		//if I want to insert in the hash table with keys of size 4
		{
			if (m4_buckets[bucket] == nullptr)		//if initially no keys are present at that index in the table
			{
				Bucket* temp = new Bucket;
				m4_buckets[bucket] = temp;
				temp->next = nullptr;
				temp->key = key;
				temp->value = value;
			}

			else		//if one or more keys are already present at the index in the vector
			{
				Bucket* p = m4_buckets[bucket];
				Bucket* temp = new Bucket;
				temp->next = p->next;		//add the new bucket at the start of the linked list
				p->next = temp;
				temp->key = key;
				temp->value = value;
			}
		}

		else if (whichVector == 8)		//if want to add to the hash table with keys of size 8
		{								// rest of the algorithm is the same as the one for size 4
			if (m8_buckets[bucket] == nullptr)
			{
				Bucket* temp = new Bucket;
				m8_buckets[bucket] = temp;
				temp->next = nullptr;
				temp->key = key;
				temp->value = value;
			}

			else
			{
				Bucket* p = m8_buckets[bucket];
				Bucket* temp = new Bucket;
				temp->next = p->next;
				p->next = temp;
				temp->key = key;
				temp->value = value;
			}
		}

		else		//if want to add it to the hash table with keys of size 16
		{			// rest of the algorithm is the same as the one for size 4
			if (m16_buckets[bucket] == nullptr)
			{
				Bucket* temp = new Bucket;
				m16_buckets[bucket] = temp;
				temp->next = nullptr;
				temp->key = key;
				temp->value = value;
			}

			else
			{
				Bucket* p = m16_buckets[bucket];
				Bucket* temp = new Bucket;
				temp->next = p->next;
				p->next = temp;
				temp->key = key;
				temp->value = value;
			}
		}
	}

	Bucket* search(string key, int whichVector)		//function to search for the a particular key in the hash table
	{
		int bucket = hashFunc(key);		//find the index where its hashed to

		if (whichVector == 4)		//if trying to find it in the hash table with keys of size 4
		{
			Bucket* p = m4_buckets[bucket];		//go to the index of in the vector

			if (p == nullptr)		//if no bucket is present in at that index, return a nullptr
				return p;

			else
			{
				Bucket* q = nullptr;
				for (; p != nullptr; p = p->next)	//loop through the linked list found at that index to find the value
				{
					if (p->key == key)		//if the key is found then return a pointer to that bucket
					{
						q = p;
						break;
					}
				}
				return q;	//if not found then return a nullptr
			}
		}

		else if (whichVector == 8)		//if trying to find the key in hash table with keys of size 4
		{
			Bucket* p = m8_buckets[bucket];

			if (p == nullptr)
				return p;

			else
			{
				Bucket* q = nullptr;
				for (; p != nullptr; p = p->next)
				{
					if (p->key == key)
					{
						q = p;
						break;
					}
				}
				return q;
			}
		}

		else
		{
			Bucket* p = m16_buckets[bucket];

			if (p == nullptr)
				return p;

			else
			{
				Bucket* q = nullptr;
				for (; p != nullptr; p = p->next)
				{
					if (p->key == key)
					{
						q = p;
						break;
					}
				}
				return q;
			}
		}
	}

private:
	int hashFunc(string key) const		//hash function that hashes the keys to a particular index in the vector
	{
		hash<string> hash;
		unsigned int hashVal = hash(key);
		
		return hashVal % MAX_BUCKETS;
	}

	vector<Bucket*> m4_buckets;		//vector for keys of size 4
	vector<Bucket*> m8_buckets;		//vector for keys of size 8
	vector<Bucket*> m16_buckets;	//vector for keys of size 16
};


void createDiff(istream& prevFile, istream& newFile, ostream& fdiff)		//function to create a diff file
{
	string PF;
	char s;
	while (prevFile.get(s))		//copy all the text in the previous file to a string
		PF += s;
	
	string NF;
	while (newFile.get(s))		//copy all the text in the new file to a string
		NF += s;

	HashTable hash;

	for (unsigned int i = 0; i < PF.size(); i += C4)  //hashing the first file into substrings of 4 chars
	{
		hash.insert(PF.substr(i, C4), i, C4);
	}

	for (unsigned int i = 0; i < PF.size(); i += C8)  //hashing the first file into substrings of 8 chars
	{
		hash.insert(PF.substr(i, C8), i, C8);
	}

	for (unsigned int i = 0; i < PF.size(); i += C16)  //hashing the first file into substrings of 16 chars
	{
		hash.insert(PF.substr(i, C16), i, C16);
	}

	string temp = "";		//string that is going to hold consecutive characters that need to be added
	int copy = 0;			//integer that tells how many consecutive characters that need to be copied
	int Where = -1;			//integer that tells from where the subsequence needs to be copied

	for (unsigned int j = 0; j < NF.size();)		//searching for the contents of the second file in the first file
	{
		Bucket* search;
		search = hash.search(NF.substr(j, C16), C16);	//first search for a substring of lenght 16
		
		if (search != nullptr)	//if found a match in the hash table
		{
			if (temp != "")		//if there are characters that I need to add first then write the add instruction
			{
				fdiff << "A" << temp.size() << ":" << temp;
				temp = "";
			}
			if (copy == 0)		//if this is the first substring that needs a copy construction
			{
				copy += C16;
				Where = search->value;
			}
			else
			{
				if (search->value == copy + Where)		//if the substring that need to be added is the next substrings that already need to be copied then increase the number of consecutive elements that need to be copied (or in this case the 'copy' variable)
					copy += C16;
				else		//if the substring is not in succession to the substring that needs to be copied
				{
					fdiff << "C" << copy << "," << Where;	//write the copy instruction for the substring saved
					copy = C16;			//make copy the size of the current substring
					Where = search->value;
				}
			}
			j += C16;	//increment by 16
		}

		else	//if substring of 16 not found
		{
			search = hash.search(NF.substr(j, C8), C8);		//search for substring of 8
			
			if (search != nullptr)		//if found then do the same thing what I did for 16
			{
				if (temp != "")
				{
					fdiff << "A" << temp.size() << ":" << temp;
					temp = "";
				}
				if (copy == 0)
				{
					copy += C8;
					Where = search->value;
				}
				else
				{
					if (search->value == copy + Where)
						copy += C8;
					else
					{
						fdiff << "C" << copy << "," << Where;
						copy = C8;
						Where = search->value;
					}
				}
				j += C8;
			}

			else		//if substring of 8 not found
			{
				search = hash.search(NF.substr(j, C4), C4);		//search of substring of 4
				
				if (search != nullptr)	//if found then do the same thing that i did earlier
				{
					if (temp != "")
					{
						fdiff << "A" << temp.size() << ":" << temp;
						temp = "";
					}
					if (copy == 0)
					{
						copy += C4;
						Where = search->value;
					}
					else
					{
						if (search->value == copy + Where)
							copy += C4;
						else
						{
							fdiff << "C" << copy << "," << Where;
							copy = C4;
							Where = search->value;
						}
					}
					j += C4;
				}

				else	//if no substring was found in the previous file
				{
					if (copy != 0)		//if there is stuff to be copied then write a copy construction for that
					{
						fdiff << "C" << copy << "," << Where;
						copy = 0;
						Where = -1;
					}
					temp += NF[j];		//add the current character to the string that specifies the consecutive characters that have to be added
					j++;
				}
			}
		}
	}

	if (temp != "")		//if after the loop ends and there if stuff that need to be added then write the add instruction
	{
		fdiff << "A" << temp.size() << ":" << temp;
		temp = "";
	}
	if (copy != 0)		//if there is stuff that needs to be copied then write the copy instruction
	{
		fdiff << "C" << copy << "," << Where;
		copy = 0;
		Where = -1;
	}
}


void add2File(char ac, unsigned int& pos, string prevFile, string diffFile, ostream& result)	//function that executes the add and copy instructions
{	
	if (ac == 'A')	//if the instruction is an add instruction
	{
		string temp;
		int num;
		while (diffFile[pos] != ':')	//read the numbers till you hit a semicolon, that tell you how many characters need to be copied
		{
			temp += diffFile[pos];
			pos++;
		}
		num = stoi(temp);	//convert into an integer

		result << diffFile.substr(pos + 1, num);	//write in the resulting file the characters that need to be added
		pos += num + 1;		//increment the position
	}

	else		//if its a copy instruction
	{
		string temp;
		int howMany;
		int Where;
		while (diffFile[pos] != ',')	//to determine how many characters need to be copied
		{
			temp += diffFile[pos];
			pos++;
		}
		howMany = stoi(temp);

		temp = "";
		pos++;
		while (diffFile[pos] != 'A' && diffFile[pos] != 'C' && pos != diffFile.size())	//to determine the offset from where it needs to be copied
		{
			temp += diffFile[pos];
			pos++;
		}
		Where = stoi(temp);

		result << prevFile.substr(Where, howMany);		//write out the substring from the previous file to the new file
	}
}

bool applyDiff(istream& prevFile, istream& fdiff, ostream& result)		//function to write out the new file from the previous file and supporting diff file
{
	string diff, PF;
	char s;
	
	while (fdiff.get(s))		//copy the diff file into a string
		diff += s;

	while (prevFile.get(s))		//copy the previous file into a string
		PF += s;

	const int diffsize = diff.size();

	for (unsigned int i = 0; i < diffsize;)		//loop through the diff file read the instructions
	{
		switch (diff[i])
		{
		case 'A':		//if add instruction
			i++;
			add2File('A', i, PF, diff, result);		//call the add2File function with add instruction
			break;
		case 'C':		//if copy instruction
			i++;
			add2File('C', i, PF, diff, result);		//call the add2File instruction with a copy instruction
			break;
		case '\n':
		case '\r':
			result << diff[i];		//if new line or return characters then just add them to the result
			i++;
			break;
		default:
			i++;
			break;
		}
	}

	return true;
}

////////////////////////////////////////////////

bool runtest(string oldName, string newName, string diffName, string newName2)
{
	if (diffName == oldName || diffName == newName ||
		newName2 == oldName || newName2 == diffName ||
		newName2 == newName)
	{
		cerr << "Files used for output must have names distinct from other files" << endl;
		return false;
	}
	ifstream oldFile(oldName, ios::binary);
	if (!oldFile)
	{
		cerr << "Cannot open " << oldName << endl;
		return false;
	}
	ifstream newFile(newName, ios::binary);
	if (!newFile)
	{
		cerr << "Cannot open " << newName << endl;
		return false;
	}
	ofstream diffFile(diffName, ios::binary);
	if (!diffFile)
	{
		cerr << "Cannot create " << diffName << endl;
		return false;
	}
	createDiff(oldFile, newFile, diffFile);
	diffFile.close();

	oldFile.clear();   // clear the end of file condition
	oldFile.seekg(0);  // reset back to beginning of the file
	ifstream diffFile2(diffName, ios::binary);
	if (!diffFile2)
	{
		cerr << "Cannot read the " << diffName << " that was just created!" << endl;
		return false;
	}
	ofstream newFile2(newName2, ios::binary);
	if (!newFile2)
	{
		cerr << "Cannot create " << newName2 << endl;
		return false;
	}
	assert(applyDiff(oldFile, diffFile2, newFile2));
	newFile2.close();

	newFile.clear();
	newFile.seekg(0);
	ifstream newFile3(newName2, ios::binary);
	if (!newFile)
	{
		cerr << "Cannot open " << newName2 << endl;
		return false;
	}
	if (!equal(istreambuf_iterator<char>(newFile), istreambuf_iterator<char>(),	istreambuf_iterator<char>(newFile3), istreambuf_iterator<char>()))
	{

		cerr << newName2 << " is not identical to " << newName
			<< "; test FAILED" << endl;
			return false;
	}
	return true;
}

int main()
{
	assert(runtest("C:/Users/param/source/repos/Project4/Project 4/p4testwindows/warandpeace1.txt", "C:/Users/param/source/repos/Project4/Project 4/p4testwindows/warandpeace2.txt", "mydifffile.txt", "mynewfile2.txt"));
	cerr << "Test PASSED" << endl;
	return 0;
}