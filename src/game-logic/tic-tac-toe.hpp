#ifndef TIC_TAC_TOE_HPP
#define TIC_TAC_TOE_HPP

#include "../includes.hpp"
#include "../interface/color.hpp"

typedef struct
{
    int y, x;
} Move;

enum Cell
{
    EMPTY,
    X,
    O
};

class TicTacToe
{
    friend class UltimateTicTacToe;
    friend class Minimax;

private:
    Cell board[3][3];
    Cell onMove;
    bool isEnd;

public:
    TicTacToe();
    virtual ~TicTacToe();

    bool IsValidMove(int y, int x) const;
    Cell CheckWin() const;
    bool IsEnded() const
    {
        return this->isEnd;
    };
    bool PlayMove(int y, int x);
    void SetOnMove(Cell cell)
    {
        this->onMove = cell;
    }
    Cell GetOnMove() const
    {
        return this->onMove;
    }
    std::vector<Move> GetAvailableMoves() const;
    const Cell &AtBoard(int i, int j) const
    {
        return this->board[i][j];
    }

    bool operator==(const TicTacToe &obj) const;

    friend std::ostream &operator<<(std::ostream &out, const TicTacToe &ttt);
};

#endif