#include <iostream>
#include <cmath>
#include <limits>
#include <vector>

using namespace std;

vector<pair<int, int>> solvePuzzle( int**, pair<int, int>); //this how we start off the solution
int GetManhattan(int**); //This is the how we get Manhattan for heurestic value
int slidePuzzle( int**, int, int&, vector<pair<int, int>>&, pair<int, int> prev); //Sliding through the puzzle
vector<pair<int, int>> generateNeighbours(pair<int, int>, pair<int, int>); // Generates all available neighbours of the current position of zero except the previous one
void swapPosition( int**, vector<pair<int, int>>); // Swaps two positions in the matrix

int finalZeroPosition; //Where the zero has to be (-1 is bottom right)
int rows; //How big the puzzle will be (its a square so no need for column)

int main()
{
	int N;
	pair<int, int> *initialEmptyTile=new pair<int, int>(0,0);
	cout << "hello" << endl;
	cin >> N;
	rows = ceil(sqrt(N));
	int** initialMatrix = new int* [rows];

	for (unsigned int i = 0; i < rows; ++i) {
		initialMatrix[i] = new int[rows];
	}
	//Matrix created
	cin >> finalZeroPosition;
	if (finalZeroPosition == -1)
	{
		finalZeroPosition=N;
	}
	//Where the zero has to be and if given -1 place in the bottom right therefore position N
	for (unsigned int i = 0; i < rows; ++i) {
		for (unsigned int j = 0; j < rows; ++j) {
			cin >> initialMatrix[i][j];
			if (initialMatrix[i][j] == 0) {
				initialEmptyTile = new pair<int, int>(i,j);
			}
		}
	}
	//Fill up the matrix and locate the beginning position of zero

	vector<pair<int,int>> resultPath = solvePuzzle(initialMatrix, *initialEmptyTile);

	cout << resultPath.size() - 1 << endl;

	for (unsigned int i = 0; i < resultPath.size() - 1; ++i) {
		if (resultPath[i].first > resultPath[i + 1].first)
			cout << "down" << endl;
		else if (resultPath[i].first < resultPath[i + 1].first)
			cout << "up" << endl;
		else if (resultPath[i].second > resultPath[i + 1].second)
			cout << "right" << endl;
		else
			cout << "left" << endl;
	}

}

vector<pair<int,int>> solvePuzzle(int** matrix, pair<int,int> initialEmptyTile)
{
	vector<pair<int,int>> currentPath;
	currentPath.push_back(initialEmptyTile);

	int threshold = GetManhattan(matrix);

	while (true) {

		int temp = slidePuzzle(matrix, 0, threshold, currentPath, pair<int, int>(-1, -1));

		if (temp == -1)
			return currentPath;
		//A solution has been found

		if (temp == INT_MAX)
			return vector<pair<int, int>>(); 
		//There is no solution

		threshold = temp;
		cout << threshold << endl;
	}
}

int GetManhattan(int** matrix)
{
     int manhattan = 0;
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < rows; ++j)
        {
            if (matrix[i][j] == 0)
            {
                continue;
            }
            if (matrix[i][j] <= finalZeroPosition)
            {
                manhattan += (abs(i - ((matrix[i][j] - 1) / rows)) + abs(j - ((matrix[i][j] - 1) % rows)));
				//Before the position of zero all other numbers are supposed to be where they are
            }
            else
            {
                manhattan += (abs(i - (matrix[i][j] / rows)) + abs(j - (matrix[i][j] % rows)));
				// On or after the position of zero all have to be pushed into the position of a the number ahead of them Example 6->7 
            }
        }
    }
    return manhattan;
}

int slidePuzzle( int** matrix, int g, int& threshold, vector<pair<int,int>>& path, pair<int,int> prev) {

	int h = GetManhattan(matrix);
	int f = g + h;

	if (f > threshold)
		return f;

	if (h == 0) { // We have reached a solution when the sum of all the manhatton distances in the matrix equals zero
		return -1; //function returns -1 when succesfull
	}

	int min = INT_MAX;

	pair<int, int> current = path.back();
	for (pair<int, int> next : generateNeighbours(current, prev)) {
		path.push_back(next);
		prev = current;
		swapPosition(matrix, path);
		int temp = slidePuzzle(matrix, g + 1, threshold, path, prev);

		if (temp == -1)
			return -1;

		if (temp < min)
			min = temp;

		swapPosition(matrix, path);
		path.pop_back();
	}

	return min;
}

void swapPosition( int** matrix, vector<pair<int, int>> path) {

	int nextX = path.back().first, nextY = path.back().second;
	path.pop_back();
	int currentX = path.back().first, currentY = path.back().second;

	int temp = matrix[currentX][currentY];
	matrix[currentX][currentY] = matrix[nextX][nextY];
	matrix[nextX][nextY] = temp;
}

vector<pair<int, int>> generateNeighbours(pair<int, int> current, pair<int, int> prev) {
	vector<pair<int, int>> adjTiles;
	int x = current.first;
	int y = current.second;

	if (x > 0) {
		pair<int, int>* temp = new pair<int, int>(x - 1, y);
		if (*temp != prev) //Checks the neighbours is the previous move
			adjTiles.push_back(*temp);
	}

	if (y > 0) {
		pair<int, int>* temp = new pair<int, int>(x, y - 1);
		if (*temp != prev)
			adjTiles.push_back(*temp);
	}

	if (x < rows - 1) {
		pair<int, int>* temp = new pair<int, int>(x + 1, y);
		if (*temp != prev)
			adjTiles.push_back(*temp);
	}

	if (y < rows - 1) {
		pair<int, int>* temp = new pair<int, int>(x, y + 1);
		if (*temp != prev)
			adjTiles.push_back(*temp);
	}

	return adjTiles;
}
