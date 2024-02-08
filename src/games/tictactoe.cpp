#include "tictactoe.hpp"

TicTacToe::TicTacToe()
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            this->board[i][j] = PlayerState::NONE;
}

TicTacToe::~TicTacToe()
{
}

bool TicTacToe::IsValidMove(const Move &move) const
{
    if (move.x < 0 || move.x >= 3)
        return false;
    if (move.y < 0 || move.y >= 3)
        return false;
    return !this->end && this->board[move.y][move.x] == PlayerState::NONE;
}

bool TicTacToe::PlayMove(const Move &move)
{
    if (!this->IsValidMove(move))
        return false;
    this->board[move.y][move.x] = this->onMove;
    this->CheckEnd();
    this->SwitchMove();
    return true;
}

std::vector<Move> TicTacToe::GetAvailableMoves() const
{
    std::vector<Move> moves;
    if (this->end)
        return moves;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (this->IsValidMove({i, j}))
                moves.push_back({i, j});
    return moves;
}

void TicTacToe::Display(std::ostream &out) const
{
    out << "┌───┬───┬───┐\n";
    for (int i = 0; i < 3; i++)
    {
        out << "│ ";
        for (int j = 0; j < 3; j++)
        {
            out << " XO"[this->board[i][j]] << " │ ";
        }
        out << '\n';
        if (i < 2)
            out << "├───┼───┼───┤\n";
        else
            out << "└───┴───┴───┘";
    }
    out << std::endl;
}

void TicTacToe::CloneTo(Game *game) const
{
    *(TicTacToe *)game = *this;
}

Game<Move> *TicTacToe::Clone() const
{
    return new TicTacToe(*this);
}

void TicTacToe::CheckEnd()
{
    PlayerState winner = PlayerState::NONE;
    // Check Rows & Columns
    for (int i = 0; i < 3; i++)
    {
        if (this->board[i][0] != PlayerState::NONE && this->board[i][0] == this->board[i][1] && this->board[i][0] == this->board[i][2])
            winner = this->board[i][0];
        if (this->board[0][i] != PlayerState::NONE && this->board[0][i] == this->board[1][i] && this->board[0][i] == this->board[2][i])
            winner = this->board[0][i];
    }
    // Check Diagonals
    if (this->board[0][0] != PlayerState::NONE && this->board[0][0] == this->board[1][1] && this->board[0][0] == this->board[2][2])
        winner = this->board[0][0];
    if (this->board[0][2] != PlayerState::NONE && this->board[0][2] == this->board[1][1] && this->board[0][2] == this->board[2][0])
        winner = this->board[0][2];

    if (winner != PlayerState::NONE)
    {
        this->end = true;
        this->onMove = winner;
        return;
    }

    // Check Draw
    bool draw = true;
    for (int i = 0; i < 3 && draw; i++)
        for (int j = 0; j < 3 && draw; j++)
            draw = draw && this->board[i][j] != PlayerState::NONE;

    if (draw)
    {
        this->end = true;
        this->onMove = PlayerState::NONE;
    }
}

void TicTacToe::Reset()
{
    this->Game::Reset();

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            this->board[i][j] = PlayerState::NONE;
}

PlayerState TicTacToe::AtBoard(int i, int j) const
{
    return this->board[i][j];
}

std::istream &operator>>(std::istream &in, Move &move)
{
    return in >> move.y >> move.x;
}
