#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include "../games/game.hpp"
#include "../ai/montecarlo.hpp"
#include "../utils/color.hpp"

template <class T>
class Interface
{
private:
    char *gameName;
    Game<T> *game;
    MCTS<T> *mcts;
    int iterations;

    void twoPlayers();
    void singlePlayer();

public:
    Interface(Game<T> *game, const char *gameName);
    virtual ~Interface();

    void Play();

    void SetIterations(int iters)
    {
        this->iterations = iters;
    }
};

template <class T>
inline void Interface<T>::twoPlayers()
{
    using std::cin;
    using std::cout;
    using std::endl;

    T move;
    bool valid;
    game->Reset();
    game->SetOnMove(PlayerState::PLAYER);
    while (true)
    {
        cout << ColorEffect::CLEAR;
        cout << *this->game << endl;
        if (game->GetEnd())
            break;
        cout << "Player " << this->game->GetOnMove() << " is on move!\n\n";
        valid = true;
        do
        {
            if (!valid)
                cout << "Invalid move!\n";
            cout << "Enter move: ";
            cin >> move;
            valid = false;
        } while (!this->game->PlayMove(move));
    }
    if (this->game->GetOnMove() != PlayerState::NONE)
        cout << "Player " << this->game->GetOnMove() << " is winner!\n";
    else
        cout << "It's a draw!\n";
    cin.ignore();
    cin.get();
}

template <class T>
inline void Interface<T>::singlePlayer()
{
    using std::cin;
    using std::cout;
    using std::endl;

    T move;
    bool valid;
    this->game->Reset();
    std::srand(std::time(nullptr));
    this->game->SetOnMove((PlayerState)(std::rand() % 2 + 1));
    this->mcts->UpdateState(this->game);

    while (true)
    {
        cout << ColorEffect::CLEAR;
        if (this->game->GetOnMove() == PlayerState::ENEMY)
        {
            move = this->mcts->GetBestMove(this->iterations);
        }
        else
        {
            cout << *this->game << endl;
            cout << "You are on move!" << endl;
            valid = true;
            do
            {
                if (!valid)
                    cout << "Invalid move!\n\n";
                cout << "Enter move: ";
                cin >> move;
                valid = false;
            } while (!this->game->IsValidMove(move));
        }
        this->game->PlayMove(move);
        this->mcts->DoMove(move);
        if (this->game->GetEnd())
            break;
    }
    cout << ColorEffect::CLEAR;
    cout << *this->game << endl;
    if (this->game->GetOnMove() != PlayerState::NONE)
        cout << (this->game->GetOnMove() == PlayerState::PLAYER ? "Player" : "Bot") << " is winner!\n";
    else
        cout << "It's a draw!\n";
    cin.ignore();
    cin.get();
}

template <class T>
inline void Interface<T>::Play()
{
    using std::cin;
    using std::cout;
    using std::endl;

    int action;
    while (true)
    {
        cout << ColorEffect::CLEAR;
        cout << "Welcome to " << this->gameName << " game!\n";
        cout << "1 - Two Players\n";
        cout << "2 - Single Player (MCTS AI)\n";
        cout << "3 - Exit\n";
        cout << ">> ";
        cin >> action;
        if (action == 1)
            this->twoPlayers();
        else if (action == 2)
            this->singlePlayer();
        else if (action == 3)
            break;
        else
        {
            cout << "Invalid action!\n";
            cin.ignore();
            cin.get();
        }
    }
}

template <class T>
inline Interface<T>::Interface(Game<T> *game, const char *gameName)
{
    this->game = game;
    this->mcts = new MCTS<T>(game);
    this->gameName = new char[strlen(gameName) + 1];
    strcpy(this->gameName, gameName);
    this->iterations = 1000;
}

template <class T>
inline Interface<T>::~Interface()
{
    delete this->game;
    delete this->mcts;
    delete this->gameName;
}

#endif