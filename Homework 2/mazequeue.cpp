#include <queue>
#include <iostream>
using namespace std;

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
	queue<Coord> coordQueue;
	coordQueue.push(Coord(sr, sc));

	maze[sr][sc] = '#';

	while (!coordQueue.empty())
	{
		Coord a = coordQueue.front();
		coordQueue.pop();

		if (a.r() == er && a.c() == ec)
		{
			return true;
		}

		if (maze[a.r() + 1][a.c()] == '.')
		{
			coordQueue.push(Coord(a.r() + 1, a.c()));
			maze[a.r() + 1][a.c()] = '#';
		}
		if (maze[a.r()][a.c() - 1] == '.')
		{
			coordQueue.push(Coord(a.r(), a.c() - 1));
			maze[a.r()][a.c() - 1] = '#';
		}
		if (maze[a.r() - 1][a.c()] == '.')
		{
			coordQueue.push(Coord(a.r() - 1, a.c()));
			maze[a.r() - 1][a.c()] = '#';
		}
		if (maze[a.r()][a.c() + 1] == '.')
		{
			coordQueue.push(Coord(a.r(), a.c() + 1));
			maze[a.r()][a.c() + 1] = '#';
		}
	}
	return false;
}


int main()
{
	queue<Coord> coordQueue;    // declare a queue of Coords

	Coord a(5, 6);
	coordQueue.push(a);            // enqueue item at back of queue
	coordQueue.push(Coord(3, 4));   // enqueue item at back of queue
	//...
	Coord b = coordQueue.front();  // look at front item
	coordQueue.pop();              // remove the front item from queue
	if (coordQueue.empty())        // Is the queue empty?
		cout << "empty!" << endl;
	cout << coordQueue.size() << endl;  // num of elements

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