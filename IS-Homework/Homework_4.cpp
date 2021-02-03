#include"TicTacToe.h"


int main()
{
    int n;
    std::cout << "If you want to be first type 1, if not type 2" << std::endl;
    std::cin >> n;
    TicTacToe Game;
    Game.Print();
    Game.Begin(n);
    return 0;
}