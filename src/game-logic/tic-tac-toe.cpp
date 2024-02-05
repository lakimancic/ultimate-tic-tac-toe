#include "tic-tac-toe.hpp"

TicTacToe::TicTacToe()
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            this->board[i][j] = Cell::EMPTY;
    this->onMove = Cell::EMPTY;
    this->isEnd = false;
}

TicTacToe::~TicTacToe()
{
}

bool TicTacToe::IsValidMove(int y, int x) const
{
    if (y < 0 || y >= 3)
        return false;
    if (x < 0 || x >= 3)
        return false;
    if (this->isEnd)
        return false;
    return this->board[y][x] == Cell::EMPTY;
}

Cell TicTacToe::CheckWin() const
{
    // Check Rows & Columns
    for (int i = 0; i < 3; i++)
    {
        if (this->board[i][0] == this->board[i][1] && this->board[i][0] == this->board[i][2])
            return this->board[i][0];
        if (this->board[0][i] == this->board[1][i] && this->board[0][i] == this->board[2][i])
            return this->board[0][i];
    }
    // Check Diagonals
    if (this->board[0][0] == this->board[1][1] && this->board[0][0] == this->board[2][2])
        return this->board[0][0];
    if (this->board[0][2] == this->board[1][1] && this->board[0][2] == this->board[2][0])
        return this->board[0][2];
    //
    return Cell::EMPTY;
}

bool TicTacToe::PlayMove(int y, int x)
{
    if (!this->IsValidMove(y, x) || this->isEnd)
    {
        return false;
    }
    this->board[y][x] = this->onMove;
    if (this->CheckWin() == Cell::EMPTY)
        this->onMove = this->onMove == Cell::X ? Cell::O : Cell::X;
    else
        this->isEnd = true;
    // Check Draw
    bool draw = true;
    for (int i = 0; i < 3 && draw; i++)
        for (int j = 0; j < 3 && draw; j++)
            draw = draw && this->board[i][j] != Cell::EMPTY;
    if (draw && !this->isEnd)
    {
        this->onMove = Cell::EMPTY;
        this->isEnd = true;
    }
    return true;
}

std::vector<Move> TicTacToe::GetAvailableMoves() const
{
    std::vector<Move> moves;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (this->board[i][j] == Cell::EMPTY && !this->isEnd)
                moves.push_back(Move{i, j});
    return moves;
}

bool TicTacToe::operator==(const TicTacToe &obj) const
{
    return this->isEnd && obj.isEnd && this->onMove == obj.onMove && this->onMove != Cell::EMPTY;
}

std::ostream &operator<<(std::ostream &out, const TicTacToe &ttt)
{
    out << "┌───┬───┬───┐\n";
    for (int i = 0; i < 3; i++)
    {
        out << "│ ";
        for (int j = 0; j < 3; j++)
        {
            out << " XO"[ttt.board[i][j]] << " │ ";
        }
        out << '\n';
        if (i < 2)
            out << "├───┼───┼───┤\n";
        else
            out << "└───┴───┴───┘";
    }
    return out << std::endl;
}
