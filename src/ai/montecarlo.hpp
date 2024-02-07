#ifndef MONTE_CARLO_HPP
#define MONTE_CARLO_HPP

#include "../games/game.hpp"

template <class T>
class MCTS_Node
{
    template <class U>
    friend class MCTS;

private:
    float value;
    int vis;
    T move;
    std::vector<MCTS_Node *> childs;
    MCTS_Node *parent;

public:
    MCTS_Node();
    MCTS_Node(T move);
    virtual ~MCTS_Node();

    void AddChild(MCTS_Node *newNode);
    float uct(int N, float c) const;
};

template <class T>
class MCTS
{
private:
    const float C = 2.0;

    MCTS_Node<T> *root;
    Game<T> *state, *tempState;

    MCTS_Node<T> *selection();
    MCTS_Node<T> *expansion(MCTS_Node<T> *node);
    float simulation();
    void backpropagation(MCTS_Node<T> *node, float value);

    void iteration();

public:
    MCTS(Game<T> *state);
    virtual ~MCTS();

    T GetBestMove(int iterations = 1000);
    void DoMove(const T &move);
    void UpdateState(Game<T> *state);

    void debug();
};

template <class T>
inline MCTS_Node<T>::MCTS_Node() : value(0), vis(0), parent(nullptr)
{
}

template <class T>
inline MCTS_Node<T>::MCTS_Node(T move) : value(0), vis(0), move(move), parent(nullptr)
{
}

template <class T>
inline MCTS_Node<T>::~MCTS_Node()
{
    for (MCTS_Node *node : this->childs)
        delete node;
}

template <class T>
inline void MCTS_Node<T>::AddChild(MCTS_Node *newNode)
{
    newNode->parent = this;
    this->childs.push_back(newNode);
}

template <class T>
inline float MCTS_Node<T>::uct(int N, float c) const
{
    return this->vis > 0 ? (this->value / this->vis + c * sqrtf(logf(N) / this->vis)) : INFINITY;
}

template <class T>
inline MCTS_Node<T> *MCTS<T>::selection()
{
    MCTS_Node<T> *curr = this->root;
    while (curr->childs.size())
    {
        int maxInd = 0;
        for (int i = 1; i < (int)curr->childs.size(); i++)
            if (curr->childs[i]->uct(this->root->vis, this->C) > curr->childs[maxInd]->uct(this->root->vis, this->C))
                maxInd = i;
        curr = curr->childs[maxInd];
        this->tempState->PlayMove(curr->move);
    }
    return curr;
}

template <class T>
inline MCTS_Node<T> *MCTS<T>::expansion(MCTS_Node<T> *node)
{
    if (node->vis == 0)
        return node;
    std::vector<T> moves = this->tempState->GetAvailableMoves();
    if (moves.size() == 0)
        return node;
    for (T &move : moves)
        node->AddChild(new MCTS_Node<T>(move));
    this->tempState->PlayMove(moves[0]);
    return node->childs[0];
}

template <class T>
inline float MCTS<T>::simulation()
{
    PlayerState player = this->tempState->GetOnMove();
    if (this->tempState->GetEnd())
        return player == PlayerState::NONE ? 0.f : 1.f;
    std::vector<T> moves;
    while (!this->tempState->GetEnd())
    {
        moves = this->tempState->GetAvailableMoves();
        std::srand(std::time(nullptr));
        this->tempState->PlayMove(moves[std::rand() % moves.size()]);
    }
    if (this->tempState->GetOnMove() == PlayerState::NONE)
        return 0.f;
    return this->tempState->GetOnMove() == player ? -1.f : 1.f;
}

template <class T>
inline void MCTS<T>::backpropagation(MCTS_Node<T> *node, float value)
{
    while (node)
    {
        node->value += value;
        value = -value;
        node->vis++;
        node = node->parent;
    }
}

template <class T>
inline MCTS<T>::MCTS(Game<T> *state)
{
    this->state = state->Clone();
    this->tempState = state->Clone();

    this->root = nullptr;
}

template <class T>
inline MCTS<T>::~MCTS()
{
    delete this->state;
    delete this->tempState;
    delete this->root;
}

template <class T>
inline T MCTS<T>::GetBestMove(int iterations)
{
    delete this->root;
    this->root = new MCTS_Node<T>;

    for (int i = 0; i < iterations; i++)
        this->iteration();

    int maxVis = 0;
    T move;
    for (MCTS_Node<T> *child : this->root->childs)
        if (child->vis > maxVis)
        {
            maxVis = child->vis;
            move = child->move;
        }
    return move;
}

template <class T>
inline void MCTS<T>::DoMove(const T &move)
{
    this->state->PlayMove(move);
}

template <class T>
inline void MCTS<T>::UpdateState(Game<T> *state)
{
    state->CloneTo(this->state);
}

template <class T>
inline void MCTS<T>::iteration()
{
    this->state->CloneTo(this->tempState);
    MCTS_Node<T> *node = this->selection();
    node = this->expansion(node);
    float value = this->simulation();
    this->backpropagation(node, value);
}

template <class T>
inline void MCTS<T>::debug()
{

    std::cout << "VISITS: " << this->root->vis << std::endl;
    for (auto &child : this->root->childs)
    {
        std::cout << "MOVE: " << child->move.y << " " << child->move.x << " INFO: ";
        std::cout << child->value << " " << child->vis << std::endl;
    }
    std::cout << *this->state;
}

#endif