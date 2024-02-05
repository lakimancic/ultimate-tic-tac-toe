#ifndef MONTE_CARLO_HPP
#define MONTE_CARLO_HPP

#include "../game-logic/ultimate-tic-tac-toe.hpp"

class MCTS_Node
{
    friend class MCTS;

private:
    float value;
    int vis;
    Move move;
    std::vector<MCTS_Node *> childs;
    MCTS_Node *parent;

public:
    MCTS_Node(Move move);
    virtual ~MCTS_Node();

    void AddChild(MCTS_Node *newNode);
    float uct(int N, float c) const;
};

class MCTS
{
private:
    const float C = 2.0;

    MCTS_Node *root;
    TicTacToe state, tempState;

    MCTS_Node *selection();
    MCTS_Node *expansion(MCTS_Node *node);
    float simulation();
    void backpropagation(MCTS_Node *node, float value);

public:
    MCTS(TicTacToe state);
    virtual ~MCTS();

    void iteration();
    void debug();
};

#endif