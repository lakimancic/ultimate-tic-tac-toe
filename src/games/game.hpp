#ifndef GAME_HPP
#define GAME_HPP

#include "../includes.hpp"

enum PlayerState
{
    NONE,
    PLAYER,
    ENEMY
};

template <class T>
class Game
{
protected:
    PlayerState onMove;
    bool end;

public:
    Game() : onMove(NONE), end(false){};
    virtual ~Game(){};

    void SwitchMove();

    virtual bool IsValidMove(const T &move) const = 0;
    virtual bool PlayMove(const T &move) = 0;
    virtual std::vector<T> GetAvailableMoves() const = 0;
    virtual void Display(std::ostream &out) const = 0;
    virtual void CloneTo(Game *game) const = 0;
    virtual Game<T> *Clone() const = 0;
    virtual void CheckEnd() = 0;
    virtual void Reset();

    void SetOnMove(PlayerState cell)
    {
        this->onMove = cell;
    }

    PlayerState GetOnMove() const
    {
        return this->onMove;
    }

    bool GetEnd() const
    {
        return this->end;
    }

    template <class U>
    friend std::ostream &operator<<(std::ostream &out, const Game<U> &game);
};

template <class U>
inline std::ostream &operator<<(std::ostream &out, const Game<U> &game)
{
    game.Display(out);
    return out;
}

template <class T>
inline void Game<T>::SwitchMove()
{
    if (!this->end)
        this->onMove = this->onMove == PlayerState::PLAYER ? PlayerState::ENEMY : PlayerState::PLAYER;
}

template <class T>
inline void Game<T>::Reset()
{
    this->end = false;
    this->onMove = PlayerState::NONE;
}

#endif