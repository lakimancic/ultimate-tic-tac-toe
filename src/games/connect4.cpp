#include "connect4.hpp"

Connect4::Connect4()
{
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
            this->board[i][j] = PlayerState::NONE;
}

Connect4::~Connect4()
{
}

bool Connect4::IsValidMove(const int &move) const
{
    if (move < 0 || move >= COLS)
        return false;
    return this->board[0][move] == PlayerState::NONE;
}

bool Connect4::PlayMove(const int &move)
{
    if (!this->IsValidMove(move))
        return false;
    int i = ROWS - 1;
    while (this->board[i][move] != PlayerState::NONE)
        i--;
    this->board[i][move] = this->onMove;
    this->CheckEnd();
    this->SwitchMove();
    return true;
}

std::vector<int> Connect4::GetAvailableMoves() const
{
    std::vector<int> moves;
    if (this->end)
        return moves;
    for (int i = 0; i < COLS; i++)
        if (this->IsValidMove(i))
            moves.push_back(i);
    return moves;
}

void Connect4::Display(std::ostream &out) const
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if (this->board[i][j] == PlayerState::NONE)
                out << BgColor(0, 0, 255);
            else if (this->board[i][j] == PlayerState::PLAYER)
                out << BgColor(255, 255, 0);
            else
                out << BgColor(255, 0, 0);
            out << "   ";
        }
        out << '\n';
    }
    out << ColorEffect::RESET;
}

void Connect4::CloneTo(Game *game) const
{
    *(Connect4 *)game = *this;
}

Game<int> *Connect4::Clone() const
{
    return new Connect4(*this);
}

void Connect4::CheckEnd()
{
    PlayerState winner = PlayerState::NONE;
    // Horizontal Check
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS - 3; j++)
            if (this->board[i][j] != PlayerState::NONE)
            {
                bool winning = true;
                for (int k = 1; k < 4; k++)
                    winning = winning && this->board[i][j] == this->board[i][j + k];
                if (winning)
                    winner = this->board[i][j];
            }
    // Vertical Check
    for (int i = 0; i < ROWS - 3; i++)
        for (int j = 0; j < COLS; j++)
            if (this->board[i][j] != PlayerState::NONE)
            {
                bool winning = true;
                for (int k = 1; k < 4; k++)
                    winning = winning && this->board[i][j] == this->board[i + k][j];
                if (winning)
                    winner = this->board[i][j];
            }
    // Positive Diagonal Check
    for (int i = 0; i < ROWS - 3; i++)
        for (int j = 0; j < COLS - 3; j++)
            if (this->board[i][j] != PlayerState::NONE)
            {
                bool winning = true;
                for (int k = 1; k < 4; k++)
                    winning = winning && this->board[i][j] == this->board[i + k][j + k];
                if (winning)
                    winner = this->board[i][j];
            }
    // Negative Diagonal Check
    for (int i = 3; i < ROWS; i++)
        for (int j = 0; j < COLS - 3; j++)
            if (this->board[i][j] != PlayerState::NONE)
            {
                bool winning = true;
                for (int k = 1; k < 4; k++)
                    winning = winning && this->board[i][j] == this->board[i - k][j + k];
                if (winning)
                    winner = this->board[i][j];
            }

    if (winner != PlayerState::NONE)
    {
        this->end = true;
        this->onMove = winner;
        return;
    }

    // Check Draw
    bool draw = true;
    for (int i = 0; i < ROWS && draw; i++)
        for (int j = 0; j < COLS && draw; j++)
            draw = draw && this->board[i][j] != PlayerState::NONE;

    if (draw)
    {
        this->end = true;
        this->onMove = PlayerState::NONE;
    }
}

void Connect4::Reset()
{
    this->Game::Reset();

    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
            this->board[i][j] = PlayerState::NONE;
}
