#include "ai/montecarlo.hpp"

int main()
{
    // Game game;
    // game.Loop();
    TicTacToe ttt;
    ttt.SetOnMove(Cell::X);
    ttt.PlayMove(1, 1);
    ttt.PlayMove(0, 0);
    ttt.PlayMove(0, 1);
    MCTS mcts(ttt);
    for (int i = 0; i < 1000; i++)
    {
        // std::cout << i << std::endl;
        mcts.iteration();
    }
    mcts.debug();
    return 0;
}