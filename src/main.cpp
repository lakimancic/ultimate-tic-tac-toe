#include "interface/interface.hpp"
#include "games/tictactoe.hpp"
#include "games/connect4.hpp"
#include "ai/montecarlo.hpp"

int main()
{
    Interface<int> game(new Connect4, "Connect4");
    game.Play();
    return 0;
}