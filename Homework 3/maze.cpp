bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec) {
	if (sr == er && sc == ec) {
		return true;
	}
	maze[sr][sc] = 'O';
	if (maze[sr + 1][sc] == '.') { //SOUTH
		bool result = pathExists(maze, nRows, nCols, sr + 1, sc, er, ec);
		if (result)
			return true;
	}
	if (maze[sr][sc - 1] == '.') { //WEST

		bool result = pathExists(maze, nRows, nCols, sr, sc - 1, er, ec);
		if (result)
			return true;
	}
	if (maze[sr - 1][sc] == '.') { //NORTH

		bool result = pathExists(maze, nRows, nCols, sr - 1, sc, er, ec);
		if (result)
			return true;
	}
	if (maze[sr][sc + 1] == '.') { //EAST

		bool result = pathExists(maze, nRows, nCols, sr, sc + 1, er, ec);
		if (result)
			return true;
	}

	return false;
}
