#include "montecarlo.hpp"

MCTS_Node::MCTS_Node(Move move) : value(0), vis(0), move(move), parent(nullptr)
{
}

MCTS_Node::~MCTS_Node()
{
    for (MCTS_Node *node : this->childs)
        delete node;
}

void MCTS_Node::AddChild(MCTS_Node *newNode)
{
    newNode->parent = this;
    this->childs.push_back(newNode);
}

inline float MCTS_Node::uct(int N, float c) const
{
    return this->vis > 0 ? (this->value / this->vis + c * sqrtf(logf(N) / this->vis)) : INFINITY;
}

MCTS::MCTS(TicTacToe state) : state(state)
{
    this->root = new MCTS_Node({-1, -1});
}

MCTS::~MCTS()
{
    delete this->root;
}

void MCTS::iteration()
{
    this->tempState = this->state;
    MCTS_Node *node = this->selection();
    node = this->expansion(node);
    float value = this->simulation();
    this->backpropagation(node, value);
}

void MCTS::debug()
{
    std::cout << "VISITS: " << this->root->vis << std::endl;
    for (auto &child : this->root->childs)
    {
        std::cout << "MOVE: " << child->move.y << " " << child->move.x << " INFO: ";
        std::cout << child->value << " " << child->vis << std::endl;
    }
    std::cout << this->state;
}

MCTS_Node *MCTS::selection()
{
    MCTS_Node *curr = this->root;
    while (curr->childs.size())
    {
        int maxInd = 0;
        for (int i = 1; i < (int)curr->childs.size(); i++)
            if (curr->childs[i]->uct(this->root->vis, this->C) > curr->childs[maxInd]->uct(this->root->vis, this->C))
                maxInd = i;
        curr = curr->childs[maxInd];
        this->tempState.PlayMove(curr->move.y, curr->move.x);
    }
    return curr;
}

MCTS_Node *MCTS::expansion(MCTS_Node *node)
{
    if (node->vis == 0)
        return node;
    std::vector<Move> moves = this->tempState.GetAvailableMoves();
    if (moves.size() == 0)
        return node;
    for (Move &move : moves)
        node->AddChild(new MCTS_Node(move));
    this->tempState.PlayMove(moves[0].y, moves[0].x);
    return node->childs[0];
}

float MCTS::simulation()
{
    Cell player = this->tempState.GetOnMove();
    std::vector<Move> moves;
    Move tempMove;
    while (!this->tempState.IsEnded())
    {
        moves = this->tempState.GetAvailableMoves();
        std::srand(std::time(nullptr));
        tempMove = moves[std::rand() % moves.size()];
        this->tempState.PlayMove(tempMove.y, tempMove.x);
    }
    if (this->tempState.GetOnMove() == Cell::EMPTY)
        return 0.f;
    return this->tempState.GetOnMove() == player ? 1.f : -1.f;
}

void MCTS::backpropagation(MCTS_Node *node, float value)
{
    while (node)
    {
        node->value += value;
        node->vis++;
        node = node->parent;
    }
}
