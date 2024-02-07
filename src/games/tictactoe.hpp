#ifndef TICTACTOE_HPP
#define TICTACTOE_HPP

#include "game.hpp"

typedef struct
{
    int y, x;
} Move;

std::istream &operator>>(std::istream &in, Move &move);

class TicTacToe : public Game<Move>
{
private:
    PlayerState board[3][3];

public:
    TicTacToe();
    virtual ~TicTacToe();

    virtual bool IsValidMove(const Move &move) const override;
    virtual bool PlayMove(const Move &move) override;
    virtual std::vector<Move> GetAvailableMoves() const override;
    virtual void Display(std::ostream &out) const override;
    virtual void CloneTo(Game *game) const override;
    virtual Game<Move> *Clone() const override;
    virtual void CheckEnd() override;
    virtual void Reset() override;
};

#endif