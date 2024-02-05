#include "interface/game.hpp"

int main()
{
    // Game game;
    // game.Loop();
    UltimateTicTacToe ttt;
    ttt.SetOnMove(Cell::X);
    ttt.PlayMove(1, 2);
    ttt.PlayMove(3, 6);
    std::cout << ttt;
    return 0;
}