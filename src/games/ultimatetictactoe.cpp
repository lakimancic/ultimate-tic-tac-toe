#include "ultimatetictactoe.hpp"

UltimateTicTacToe::UltimateTicTacToe()
{
    this->cx = this->cy = -1;
}

UltimateTicTacToe::~UltimateTicTacToe()
{
}

bool UltimateTicTacToe::IsValidMove(const Move &move) const
{
    if (move.x < 0 || move.x >= 9)
        return false;
    if (move.y < 0 || move.y >= 9)
        return false;
    if (this->cx == -1 && this->cy == -1)
        return this->board[move.y / 3][move.x / 3].IsValidMove({move.y % 3, move.x % 3});
    if (this->cx != move.x / 3 || this->cy != move.y / 3)
        return false;
    return this->board[this->cy][this->cx].IsValidMove({move.y % 3, move.x % 3});
}

bool UltimateTicTacToe::PlayMove(const Move &move)
{
    if (!this->IsValidMove(move))
        return false;
    this->board[move.y / 3][move.x / 3].SetOnMove(this->onMove);
    this->board[move.y / 3][move.x / 3].PlayMove({move.y % 3, move.x % 3});
    if (!this->board[move.y % 3][move.x % 3].GetEnd())
    {
        this->cx = move.x % 3;
        this->cy = move.y % 3;
    }
    else
        this->cx = this->cy = -1;
    this->CheckEnd();
    this->SwitchMove();
    return true;
}

std::vector<Move> UltimateTicTacToe::GetAvailableMoves() const
{
    std::vector<Move> moves;
    if (this->end)
        return moves;
    if (this->cx != -1 && this->cy != -1)
    {
        moves = this->board[this->cy][this->cx].GetAvailableMoves();
        for (Move &move : moves)
        {
            move.x += this->cx * 3;
            move.y += this->cy * 3;
        }
    }
    else
    {
        for (int i = 0; i < 9; i++)
            for (int j = 0; j < 9; j++)
                if (this->IsValidMove({i, j}))
                    moves.push_back({i, j});
    }
    return moves;
}

void UltimateTicTacToe::Display(std::ostream &out) const
{
    int dx, dy;
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            dx = j / 3;
            dy = i / 3;

            bool cond = (this->cx == -1 && this->cy == -1) || (this->cx == dx && this->cy == dy);
            cond = cond || (j % 3 == 0 && this->cx == dx - 1 && this->cy == dy);
            cond = cond || (i % 3 == 0 && this->cy == dy - 1 && this->cx == dx);
            cond = cond || (j % 3 == 0 && this->cx == dx - 1 && i % 3 == 0 && this->cy == dy - 1);

            if (cond)
                out << Color(255, 255, 0);
            else
                out << ColorEffect::RESET;

            if (i == 0)
            {
                if (j == 0)
                    out << "┏";
                else if (j < 9)
                {
                    if (j % 3)
                        out << "┯";
                    else
                        out << "┳";
                }
                else
                    out << "┓\n";
            }
            else if (i < 9)
            {
                if (i % 3)
                {
                    if (j == 0)
                        out << "┠";
                    else if (j < 9)
                    {
                        if (j % 3)
                            out << "┼";
                        else
                            out << "╂";
                    }
                    else
                        out << "┨\n";
                }
                else
                {
                    if (j == 0)
                        out << "┣";
                    else if (j < 9)
                    {
                        if (j % 3)
                            out << "┿";
                        else
                            out << "╋";
                    }
                    else
                        out << "┫\n";
                }
            }
            else
            {
                if (j == 0)
                    out << "┗";
                else if (j < 9)
                {
                    if (j % 3)
                        out << "┷";
                    else
                        out << "┻";
                }
                else
                    out << "┛\n";
            }

            cond = (this->cx == -1 && this->cy == -1) || (this->cx == dx && this->cy == dy);
            cond = cond || (i % 3 == 0 && this->cy == dy - 1 && this->cx == dx);

            if (cond)
                out << Color(255, 255, 0);
            else
                out << ColorEffect::RESET;

            if (j < 9)
            {
                if (i % 3)
                    out << "───";
                else
                    out << "━━━";
            }
        }

        if (i < 9)
        {
            for (int j = 0; j < 10; j++)
            {
                dx = j / 3;
                dy = i / 3;

                bool cond = (this->cx == -1 && this->cy == -1) || (this->cx == dx && this->cy == dy);
                cond = cond || (j % 3 == 0 && this->cx == dx - 1 && this->cy == dy);

                if (cond)
                    out << Color(255, 255, 0);
                else
                    out << ColorEffect::RESET;

                if (j % 3)
                    out << "│";
                else
                    out << "┃";

                cond = (this->cx == -1 && this->cy == -1) || (this->cx == dx && this->cy == dy);

                if (cond)
                    out << Color(255, 255, 0);
                else
                    out << ColorEffect::RESET;

                if (j < 9)
                    out << " "
                        << " XO"[this->board[dy][dx].AtBoard(i % 3, j % 3)] << " ";
            }
            out << "\n";
        }
    }
    // out << this->onMove << "\n";
    out << ColorEffect::RESET;
}

void UltimateTicTacToe::CloneTo(Game *game) const
{
    *(UltimateTicTacToe *)game = *this;
}

Game<Move> *UltimateTicTacToe::Clone() const
{
    return new UltimateTicTacToe(*this);
}

void UltimateTicTacToe::CheckEnd()
{
    PlayerState winner = PlayerState::NONE;
    // Check Rows & Columns
    for (int i = 0; i < 3; i++)
    {
        if (this->board[i][0].GetEnd() && this->board[i][1].GetEnd() && this->board[i][2].GetEnd())
            if (this->board[i][0].GetOnMove() != PlayerState::NONE)
                if (this->board[i][0].GetOnMove() == this->board[i][1].GetOnMove() && this->board[i][0].GetOnMove() == this->board[i][2].GetOnMove())
                    winner = this->board[i][0].GetOnMove();
        if (this->board[0][i].GetEnd() && this->board[1][i].GetEnd() && this->board[2][i].GetEnd())
            if (this->board[0][i].GetOnMove() != PlayerState::NONE)
                if (this->board[0][i].GetOnMove() == this->board[1][i].GetOnMove() && this->board[0][i].GetOnMove() == this->board[2][i].GetOnMove())
                    winner = this->board[0][i].GetOnMove();
    }
    // Check Diagonals
    if (this->board[0][0].GetEnd() && this->board[1][1].GetEnd() && this->board[2][2].GetEnd())
        if (this->board[0][0].GetOnMove() != PlayerState::NONE)
            if (this->board[0][0].GetOnMove() == this->board[1][1].GetOnMove() && this->board[0][0].GetOnMove() == this->board[2][2].GetOnMove())
                winner = this->board[0][0].GetOnMove();
    if (this->board[2][0].GetEnd() && this->board[1][1].GetEnd() && this->board[0][2].GetEnd())
        if (this->board[2][0].GetOnMove() != PlayerState::NONE)
            if (this->board[2][0].GetOnMove() == this->board[1][1].GetOnMove() && this->board[2][0].GetOnMove() == this->board[0][2].GetOnMove())
                winner = this->board[2][0].GetOnMove();

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
            draw = draw && this->board[i][j].GetEnd();

    if (draw)
    {
        this->end = true;
        this->onMove = PlayerState::NONE;
    }
}

void UltimateTicTacToe::Reset()
{
    this->Game::Reset();

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            this->board[i][j].Reset();
}
