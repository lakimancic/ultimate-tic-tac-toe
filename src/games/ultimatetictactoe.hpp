#ifndef ULTIMATETICTACTOE_HPP
#define ULTIMATETICTACTOE_HPP

#include "tictactoe.hpp"
#include "../utils/color.hpp"

class UltimateTicTacToe : public Game<Move>
{
private:
    TicTacToe board[3][3];
    int cx, cy;

public:
    UltimateTicTacToe();
    virtual ~UltimateTicTacToe();

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