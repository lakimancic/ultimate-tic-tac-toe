#include "interface/interface.hpp"
#include "ai/montecarlo.hpp"

#include "games/tictactoe.hpp"
#include "games/connect4.hpp"
#include "games/ultimatetictactoe.hpp"

int main()
{
    Interface<Move> game(new UltimateTicTacToe, "Ultimate TicTacToe");
    game.SetIterations(40000);
    game.Play();
    return 0;
}