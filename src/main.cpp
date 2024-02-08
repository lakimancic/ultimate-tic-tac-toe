#include "interface/interface.hpp"

#include "games/tictactoe.hpp"
#include "games/connect4.hpp"
#include "games/ultimatetictactoe.hpp"

int main()
{
    using std::cin;
    using std::cout;
    using std::endl;

    int choice;
    while (true)
    {
        cout << ColorEffect::CLEAR;
        cout << "Choose Game you want to play!\n";
        cout << "1 - TicTacToe\n";
        cout << "2 - Connect4\n";
        cout << "3 - UltimateTicTacToe\n";
        cout << ">> ";
        cin >> choice;
        if (choice == 1)
        {
            Interface<Move> game(new TicTacToe, "TicTacToe");
            game.Play();
        }
        else if (choice == 2)
        {
            Interface<int> game(new Connect4, "Connect4");
            game.SetIterations(40000);
            game.Play();
        }
        else if (choice == 3)
        {
            Interface<Move> game(new UltimateTicTacToe, "UltimateTicTacToe");
            game.SetIterations(40000);
            game.Play();
        }
    }
    return 0;
}