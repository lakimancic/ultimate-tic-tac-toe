#ifndef ULTIMATE_TIC_TAC_TOE_HPP
#define ULTIMATE_TIC_TAC_TOE_HPP

#include "tic-tac-toe.hpp"
#include "../interface/color.hpp"

class UltimateTicTacToe
{
private:
    TicTacToe board[3][3];
    Cell onMove;
    bool isEnd;
    int cx, cy;

public:
    UltimateTicTacToe();
    virtual ~UltimateTicTacToe();

    bool IsValidMove(int y, int x) const;
    Cell CheckWin() const;
    bool IsEnded() const
    {
        return this->isEnd;
    };
    void SetOnMove(Cell cell)
    {
        this->onMove = cell;
    }
    Cell GetOnMove() const
    {
        return this->onMove;
    }
    bool PlayMove(int y, int x);

    friend std::ostream &operator<<(std::ostream &out, const UltimateTicTacToe &ttt);
};

#endif