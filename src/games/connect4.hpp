#ifndef CONNECT4_HPP
#define CONNECT4_HPP

#include "game.hpp"
#include "../utils/color.hpp"

#define ROWS 6
#define COLS 7

class Connect4 : public Game<int>
{
private:
    PlayerState board[ROWS][COLS];

public:
    Connect4();
    virtual ~Connect4();

    virtual bool IsValidMove(const int &move) const override;
    virtual bool PlayMove(const int &move) override;
    virtual std::vector<int> GetAvailableMoves() const override;
    virtual void Display(std::ostream &out) const override;
    virtual void CloneTo(Game *game) const override;
    virtual Game<int> *Clone() const override;
    virtual void CheckEnd() override;
    virtual void Reset() override;
};

#endif