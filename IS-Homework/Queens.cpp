#include <iostream>
#include <time.h>
#include "Queens.h"

using namespace std;

int main()
{
	srand(time(NULL));
	int N;
	cin >> N;
	if (N <= 3)
	{
		return 0;
	}
	clock_t start;
	double duration;
	start = clock();
	Queens Board(N);
	Board.Solve();
	duration = (clock() - start) / (double)CLOCKS_PER_SEC;
	cout << "printf: " << duration << '\n';
	//Board.Print();
	return 0;
}
