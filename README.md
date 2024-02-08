# TicTacToe, Connect4, and UltimateTicTacToe Game with AI using Monte Carlo Tree Search Algorithm

This repository contains implementations of the classic games TicTacToe, Connect4, and UltimateTicTacToe in C++, along with an AI player utilizing the Monte Carlo Tree Search (MCTS) algorithm.

## Games Implemented

### 1. TicTacToe

TicTacToe is a simple two-player game played on a 3x3 grid. Players take turns marking spaces with their respective symbols, typically "X" and "O", aiming to get three of their symbols in a row horizontally, vertically, or diagonally.

### 2. Connect4

Connect4 is a classic two-player game played on a 7x6 grid. Players take turns dropping colored discs from the top into a column, with the objective of connecting four of their own discs vertically, horizontally, or diagonally.

### 3. UltimateTicTacToe

UltimateTicTacToe is an extended version of TicTacToe played on a 3x3 grid of TicTacToe boards. Players take turns making moves on a smaller TicTacToe board within the larger grid. The objective is to win three smaller TicTacToe boards in a row.

## AI Player

The AI player incorporated in these games utilizes the Monte Carlo Tree Search (MCTS) algorithm to make decisions. MCTS is a heuristic search algorithm commonly used in games with large branching factors and imperfect information. It simulates multiple random games from the current game state and selects moves based on the outcomes of these simulations.

## How to Use

1. Clone the repository to your local machine.
2. Compile the source code using the provided Makefile by running the `make` command in the terminal.
3. Run the executable file.
4. Choose the game you want to play (TicTacToe, Connect4, or UltimateTicTacToe).
5. Follow the prompts to make moves and interact with the game.
6. If playing against the AI, the AI player will utilize the MCTS algorithm to make its moves.

## Dependencies

The codebase has no external dependencies other than a standard C++ compiler.

## Contributors

- Lazar Mancic

## License

This project is licensed under the [MIT License](LICENSE). Feel free to use and modify the code for your own purposes. Contributions are welcome via pull requests.

For more details about each game and the AI implementation, please refer to the source code in `src` directory. If you encounter any issues or have suggestions for improvements, please feel free to open an issue on GitHub. Enjoy playing!
