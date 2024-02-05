#include "game.hpp"

using std::cin;
using std::cout;
using std::endl;

void Game::twoPlayers() const
{
    int turn = 0, mx, my;
    bool valid;
    TicTacToe game;
    game.SetOnMove(Cell::X);
    while (true)
    {
        cout << ColorEffect::CLEAR;
        cout << game << endl;
        if (game.IsEnded())
            break;
        cout << "Player " << (turn + 1) << " is on move!\n\n";
        valid = true;
        do
        {
            if (!valid)
                cout << "Invalid move!\n\n";
            cout << "Enter move (row, col): ";
            cin >> my >> mx;
            valid = false;
        } while (!game.PlayMove(my, mx));
        if (!game.IsEnded())
            turn = !turn;
    }
    if (game.GetOnMove() != Cell::EMPTY)
        cout << "Player " << (turn + 1) << " is winner!\n";
    else
        cout << "It's a draw!\n";
    cin.ignore();
    cin.get();
}

void Game::singlePlayer() const
{
    std::srand(std::time(nullptr));
    int turn = std::rand() % 2;
    bool valid;
    Move nextMove;
    TicTacToe game;
    game.SetOnMove(Cell::X);
    Minimax minimax(game);
    while (true)
    {
        cout << ColorEffect::CLEAR;
        if (turn)
        {
            nextMove = minimax.GetBestMove();
            if (game.IsEnded())
            {
                cout << game << endl;
                break;
            }
        }
        else
        {
            cout << game << endl;
            if (game.IsEnded())
                break;
            cout << "You are on move!\n\n";
            valid = true;
            do
            {
                if (!valid)
                    cout << "Invalid move!\n\n";
                cout << "Enter move (row, col): ";
                cin >> nextMove.y >> nextMove.x;
                valid = false;
            } while (!game.IsValidMove(nextMove.y, nextMove.x));
        }
        game.PlayMove(nextMove.y, nextMove.x);
        minimax.DoMove(nextMove.y, nextMove.x);
        if (!game.IsEnded())
            turn = !turn;
    }
    if (game.GetOnMove() != Cell::EMPTY)
        cout << (turn ? "Bot" : "Player") << " is winner!\n";
    else
        cout << "It's a draw!\n";
    cin.ignore();
    cin.get();
}

Game::Game()
{
}

Game::~Game()
{
}

void Game::Loop()
{
    int option;
    cout << "Welcome to TicTacToe Game!\n\n";
    while (true)
    {
        cout << "1 - Classic TicTacToe (2 Players)\n";
        cout << "2 - Classic TicTacToe (1 Player - Minimax)\n";
        cout << "3 - Ultimate TicTacToe (2 Players)\n";
        cout << "4 - Ultimate TicTacToe (1 Plyaer - MCTS)\n\n";
        cout << ">> ";
        cin >> option;
        switch (option)
        {
        case 1:
            this->twoPlayers();
            break;
        case 2:
            this->singlePlayer();
            break;
        default:
            cout << "Invalid option!\n";
            cin.ignore();
            cin.get();
            break;
        }
        cout << ColorEffect::CLEAR;
    }
}
