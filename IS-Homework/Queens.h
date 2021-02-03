#pragma once
#include <stdlib.h>
#include <time.h> 
#include<vector>

class Queens
{
private:
	int N;
	int* Board;
	int* Rows;
	int* Main_Diagonal;
	int* Other_Diagonal;
public:
	void Print()
	{
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (i == Board[j]) {
					std::cout << "* ";
				}
				else {
					std::cout << "_ ";
				}
			}
			std::cout << std::endl;
		}
	}
	//Basic Print for the result
	Queens(int _N)
	{
		N = _N;
		Board = new int[N];
		Rows = new int[N];
		Main_Diagonal = new int[2*N-1];
		Other_Diagonal = new int[2*N-1];
		Reboot();
	}
	//Constructor for the Board
	void Reboot()
	{
		for (int i = 0; i < N; i++)
		{
			Board[i] = 0;
			Rows[i] = 0;
		}
		for (int i = 0; i < 2 * N - 1; i++)
		{
			Main_Diagonal[i] = 0;
			Other_Diagonal[i] = 0;
		}
		for (int i = 0; i < N; i++) 
		{
			int row = rand() % N;
			Board[i] = row;
			Rows[row]++;
			Main_Diagonal[N - (row - i + 1)]++;
			Other_Diagonal[i + row]++;
		}
	}
	//Shuffling to different position
	int GetMaxConflicts()
	{
		int max = INT_MIN;
		int* QueensConflictss = new int[N];
		std::vector<int> MaxIndexes;
		for (int i = 0; i < N; i++) {
			int row = Board[i];
			int Conflicts = 0;
			Conflicts += Rows[row]-1;
			Conflicts += Main_Diagonal[N - (row - i + 1)]-1;
			Conflicts += Other_Diagonal[i + row]-1;
			if (max < Conflicts) 
			{
				max = Conflicts;
			}
			QueensConflictss[i] = Conflicts;
		}
		if (max <= 0) {
			delete[] QueensConflictss;
			return -1;
		}
		for (int i = 0; i < N; i++) {
			if (max == QueensConflictss[i]) {
				MaxIndexes.push_back(i);
			}
		}
		int col = MaxIndexes[rand() % MaxIndexes.size()];
		delete[] QueensConflictss;
		MaxIndexes.clear();
		return col;
	}
	//seeks out the highest Conflicts between the queens
	int GetMinConflicts(int col)
	{
			int min = INT_MAX;
			int* queensConflictssRow = new int[N];
			std::vector<int> MinIndexes;
			for (int i = 0; i < N; i++) {
				int Conflictss = 0;
				Conflictss += Rows[i];
				Conflictss += Main_Diagonal[N - (i - col + 1)];
				Conflictss += Other_Diagonal[i + col];
				if (min > Conflictss) {
					min = Conflictss;
				}
				queensConflictssRow[i] = Conflictss;
			}
			for (int i = 0; i < N; i++) {
				if (min == queensConflictssRow[i]) {
					MinIndexes.push_back(i);
				}
			}
			int row = MinIndexes[rand() % MinIndexes.size()];
			delete[] queensConflictssRow;
			MinIndexes.clear();
			return row;
	}
	//seeks out the lowest Conflicts in the column
	void Move(int col)
	{
		int From = Board[col];
		int To = GetMinConflicts(col);
		Board[col] = To;
		Rows[From]--;
		Rows[To]++;

		Main_Diagonal[N - (From - col + 1)]--;
		Main_Diagonal[N - (To - col + 1)]++;
		Other_Diagonal[From + col]--;
		Other_Diagonal[To + col]++;
	}
	//Moving queens between rows
	void Solve()
	{
		int MaxMoves = 3 * N;
		int i = 0;
		while (++i < MaxMoves)
		{
			int col = GetMaxConflicts();
			if (col == -1)
			{
				return;
			}
			Move(col);
		}
		Reboot();
		Solve();
	} 
	// Solves the problem

	
};
