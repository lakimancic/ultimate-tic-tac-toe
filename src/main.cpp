#include "interface/interface.hpp"
#include "games/tictactoe.hpp"
#include "ai/montecarlo.hpp"

int main()
{
    Interface<Move> game(new TicTacToe, "TicTacToe");
    game.Play();
    return 0;
}