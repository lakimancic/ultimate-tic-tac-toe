#include "minimax.hpp"

int Minimax::traverse(bool maxPlayer)
{
    if (this->state.IsEnded())
    {
        if (this->state.onMove == Cell::EMPTY)
            return 0;
        return this->state.onMove == this->player ? 1 : -1;
    }
    Cell temp = this->state.onMove;
    if (maxPlayer)
    {
        std::vector<Move> moves = this->state.GetAvailableMoves();
        int maxEval = -1;
        for (Move &move : moves)
        {
            this->state.PlayMove(move.y, move.x);
            maxEval = std::max(maxEval, this->traverse(false));
            this->state.board[move.y][move.x] = Cell::EMPTY;
            this->state.onMove = temp;
            this->state.isEnd = false;
        }
        return maxEval;
    }
    else
    {
        std::vector<Move> moves = this->state.GetAvailableMoves();
        int minEval = 1;
        for (Move &move : moves)
        {
            this->state.PlayMove(move.y, move.x);
            minEval = std::min(minEval, this->traverse(true));
            this->state.board[move.y][move.x] = Cell::EMPTY;
            this->state.onMove = temp;
            this->state.isEnd = false;
        }
        return minEval;
    }
}

Minimax::Minimax(TicTacToe state) : state(state)
{
}

Minimax::~Minimax()
{
}

Move Minimax::GetBestMove()
{
    std::vector<Move> moves = this->state.GetAvailableMoves();
    this->player = this->state.onMove;
    int maxVal = -2;
    Move bestMove = {-1, -1};
    for (Move &move : moves)
    {
        this->state.PlayMove(move.y, move.x);
        int val = this->traverse(false);
        if (val > maxVal)
        {
            maxVal = val;
            bestMove = move;
        }
        this->state.board[move.y][move.x] = Cell::EMPTY;
        this->state.onMove = this->player;
        this->state.isEnd = false;
    }
    return bestMove;
}
