#include <stack>
#include <iostream>
using namespace std;


/////////MAKE SURE ALL THE NAMES ARE CORRECT
////// YOU CHANGED THE NAMES


bool pathExists(char maze[][10], int sr, int sc, int er, int ec);
// Return true if there is a path from (sr,sc) to (er,ec)
// through the maze; return false otherwise

class Coord
{
public:
	Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
	int r() const { return m_r; }
	int c() const { return m_c; }
private:
	int m_r;
	int m_c;
};


bool pathExists(char maze[][10], int sr, int sc, int er, int ec)
{
	stack<Coord> coordStack;

	coordStack.push(Coord(sr, sc));

	maze[sr][sc] = '#';

	while (!coordStack.empty())
	{
		Coord a = coordStack.top();
		coordStack.pop();
		
		if (a.r() == er && a.c() == ec)
		{
			return true;
		}

		if (maze[a.r() + 1][a.c()] == '.')
		{
			coordStack.push(Coord(a.r() + 1, a.c()));
			maze[a.r() + 1][a.c()] = '#';
		}
		if (maze[a.r()][a.c() - 1] == '.')
		{
			coordStack.push(Coord(a.r(), a.c() - 1));
			maze[a.r()][a.c() - 1] = '#';
		}
		if (maze[a.r() - 1][a.c()] == '.')
		{
			coordStack.push(Coord(a.r() - 1, a.c()));
			maze[a.r() - 1][a.c()] = '#';
		}
		if (maze[a.r()][a.c() + 1] == '.')
		{
			coordStack.push(Coord(a.r(), a.c() + 1));
			maze[a.r()][a.c() + 1] = '#';
		}
	}
	return false;
}


int main()
{
	char maze[10][10] = {
		{ 'X','X','X','X','X','X','X','X','X','X' },
		{ 'X','.','.','.','.','X','.','.','.','X' },
		{ 'X','.','X','X','.','X','X','X','.','X' },
		{ 'X','X','X','.','.','.','.','X','.','X' },
		{ 'X','.','X','X','X','.','X','X','X','X' },
		{ 'X','.','X','.','.','.','X','.','.','X' },
		{ 'X','.','.','.','X','.','X','.','.','X' },
		{ 'X','X','X','X','X','.','X','.','X','X' },
		{ 'X','.','.','.','.','.','.','.','.','X' },
		{ 'X','X','X','X','X','X','X','X','X','X' }
	};

	if (pathExists(maze, 3, 5, 8, 8))
		cout << "Solvable!" << endl;
	else
		cout << "Out of luck!" << endl;

	return 0;
}