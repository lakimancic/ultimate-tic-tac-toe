#ifndef GAME_HPP
#define GAME_HPP

#include "../game-logic/ultimate-tic-tac-toe.hpp"
#include "../ai/minimax.hpp"

class Game
{
private:
    void twoPlayers() const;
    void singlePlayer() const;

public:
    Game();
    virtual ~Game();

    void Loop();
};

#endif