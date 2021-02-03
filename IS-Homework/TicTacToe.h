#pragma once
#include<iostream>
#include<vector>
#include<limits.h>

struct Move
{
	int Value;
	int X;
	int Y;
	Move(int _val, int _x, int _y) : Value(_val), X(_x), Y(_y) {};
};
class TicTacToe
{
private:
	int board[3][3] = { 0 };
public:
	bool isFull()
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (board[i][j] == 0)
				{
					return false;
				}
			}
		}
		return true;
	}
	void Print()
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (board[i][j] == 0)
				{
					std::cout << "_ ";
				}
				else if (board[i][j] == 1)
				{
					std::cout << "X ";
				}
				else
				{
					std::cout << "O ";
				}
			}
			std::cout << std::endl;
		}
	}
	int State()
	{
		for (int i = 0; i < 3; ++i) {
			if (board[i][0] != 0 && board[i][0] == board[i][1] && board[i][0] == board[i][2])
				if (board[i][0] == 1)
				{
					return 1000;
				}
				else
				{
					return -1000;
				}

			if (board[0][i] != 0 && board[0][i] == board[1][i] && board[0][i] == board[2][i])
				if (board[0][i] == 1)
				{
					return 1000;
				}
				else
				{
					return -1000;
				}
		}

		if ((board[0][0] == board[1][1] && board[0][0] == board[2][2]) || (board[0][2] == board[1][1] && board[0][2] == board[2][0]))
			if (board[1][1] != 0)
				if (board[1][1] == 1)
				{
					return 1000;
				}
				else
				{
					return -1000;
				}

		return 0;
	}
	Move AlphaBeta(int depth, bool maximizingPlayer, int alpha, int beta)
	{
		int Best_Row = -1;
		int Best_Column = -1;
		int Best_Score = 0;
		if (maximizingPlayer)
		{
			Best_Score = -1000;
		}
		else
		{
			Best_Score = 1000;
		}
		std::vector<std::pair<int, int>> FreeSpaces;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (board[i][j] == 0)
				{

					FreeSpaces.push_back(std::make_pair(i, j));
				}
			}
		}
		int score = State();
		if (FreeSpaces.empty() || score != 0)
		{
			Best_Score = score;
			return Move(Best_Score, Best_Row, Best_Column);
		}

		for (int i = 0; i < FreeSpaces.size(); i++)
		{
			int x = FreeSpaces[i].first;
			int y = FreeSpaces[i].second;
			if (maximizingPlayer)
			{
				board[x][y] = 1;
				int score = AlphaBeta(depth + 1, !maximizingPlayer, alpha, beta).Value;
				if (Best_Score < score)
				{
					Best_Score = score - 10 * depth;
					Best_Row = x;
					Best_Column = y;

					if (Best_Score > alpha)
					{
						alpha = Best_Score;
					}

					board[x][y] = 0;
					if (beta <= alpha)
					{
						break;
					}
				}
			}
			else
			{
				board[x][y] = 2;
				int score = AlphaBeta(depth + 1, !maximizingPlayer, alpha, beta).Value;
				if (Best_Score > score)
				{
					Best_Score = score + 10 * depth;
					Best_Row = x;
					Best_Column = y;

					if (Best_Score < beta)
					{
						beta = Best_Score;
					}

					board[x][y] = 0;
					if (beta <= alpha)
					{
						break;
					}
					
				}
			}
			board[x][y] = 0;
		}
		return Move(Best_Score, Best_Row, Best_Column);
	}
	void Begin(int first)
	{
		int x, y;
		int winner;
		while (true)
		{
			if (first == 2)
			{
				std::cout << "AI move:" << std::endl;
				Move AI_move = AlphaBeta(0, true, INT_MIN, INT_MAX);
				std::cout << AI_move.Value << " " << AI_move.X << " " << AI_move.Y << std::endl;
				board[AI_move.X][AI_move.Y] = 1;
				Print();
				winner = State();
				if (winner == 1000)
				{
					std::cout << "Machine Wins" << std::endl;
					return;
				}
				else if (winner == -1000)
				{
					std::cout << "Human Wins" << std::endl;
					return;
				}
				else if (winner == 0 && isFull())
				{
					std::cout << "Draw!" << std::endl;
					return;
				}

				std::cout << "Your move:" << std::endl;
				while (true)
				{
					std::cin >> x >> y;
					if (board[x][y] == 0)
					{
						break;
					}
					else
						std::cout << "Nope that spot is already taken try again" << std::endl;
				}
				board[x][y] = 2;
				winner = State();
				if (winner == 1000)
				{
					std::cout << "Machine Wins" << std::endl;
					return;
				}
				else if (winner == -1000)
				{
					std::cout << "Human Wins" << std::endl;
					return;
				}
				else if (winner == 0 && isFull())
				{
					std::cout << "Draw!" << std::endl;
					return;
				}
			}
			else
			{
				std::cout << "Your move:" << std::endl;
				while (true)
				{
					std::cin >> x >> y;
					if (board[x][y] == 0)
					{
						break;
					}
					else
						std::cout << "Nope that spot is already taken try again" << std::endl;
				}
				board[x][y] = 1;
				Print();
				winner = State();
				if (winner == -1000)
				{
					std::cout << "Machine Wins" << std::endl;
					return;
				}
				else if (winner == 1000)
				{
					std::cout << "Human Wins" << std::endl;
					return;
				}
				else if (winner == 0 && isFull())
				{
					std::cout << "Draw!" << std::endl;
					return;
				}

				std::cout << "AI move:" << std::endl;
				Move AI_move = AlphaBeta(0, false, INT_MIN, INT_MAX);
				std::cout << AI_move.Value << " " << AI_move.X << " " << AI_move.Y << std::endl;
				board[AI_move.X][AI_move.Y] = 2;
				Print();
				winner = State();
				if (winner == -1000)
				{
					std::cout << "Machine Wins" << std::endl;
					return;
				}
				else if (winner == 1000)
				{
					std::cout << "Human Wins" << std::endl;
					return;
				}
				else if (winner == 0 && isFull())
				{
					std::cout << "Draw!" << std::endl;
					return;
				}
			}
			
		}
	return;
	}
};