#ifndef MINIMAX_HPP
#define MINIMAX_HPP

#include "../game-logic/tic-tac-toe.hpp"

class Minimax
{
private:
    TicTacToe state;
    Cell player;

    int traverse(bool maxPlayer = true);

public:
    Minimax(TicTacToe state);
    virtual ~Minimax();

    Move GetBestMove();
    void DoMove(int y, int x)
    {
        this->state.PlayMove(y, x);
    }
};

#endif