#include "ultimate-tic-tac-toe.hpp"

UltimateTicTacToe::UltimateTicTacToe()
{
    this->onMove = Cell::EMPTY;
    this->isEnd = false;
    this->cx = this->cy = -1;
}

UltimateTicTacToe::~UltimateTicTacToe()
{
}

bool UltimateTicTacToe::IsValidMove(int y, int x) const
{
    if (y < 0 || y >= 9)
        return false;
    if (x < 0 || x >= 9)
        return false;
    int dx = x / 3;
    int dy = y / 3;
    if ((dx != this->cx || dy != this->cy) && this->cx != -1 && this->cy != -1)
        return false;
    return this->board[dy][dx].IsValidMove(y % 3, x % 3);
}

Cell UltimateTicTacToe::CheckWin() const
{
    // Check Rows & Columns
    for (int i = 0; i < 3; i++)
    {
        if (this->board[i][0] == this->board[i][1] && this->board[i][0] == this->board[i][2])
            return this->board[i][0].onMove;
        if (this->board[0][i] == this->board[1][i] && this->board[0][i] == this->board[2][i])
            return this->board[0][i].onMove;
    }
    // Check Diagonals
    if (this->board[0][0] == this->board[1][1] && this->board[0][0] == this->board[2][2])
        return this->board[0][0].onMove;
    if (this->board[0][2] == this->board[1][1] && this->board[0][2] == this->board[2][0])
        return this->board[0][2].onMove;
    //
    return Cell::EMPTY;
}

bool UltimateTicTacToe::PlayMove(int y, int x)
{
    if (!this->IsValidMove(y, x))
        return false;
    int dx = x / 3;
    int dy = y / 3;
    this->board[dy][dx].onMove = this->onMove;
    this->board[dy][dx].PlayMove(y % 3, x % 3);
    if (this->CheckWin() == Cell::EMPTY)
    {
        this->onMove = this->onMove == Cell::X ? Cell::O : Cell::X;
        this->cx = x % 3;
        this->cy = y % 3;
        if (this->board[this->cy][this->cx].IsEnded())
            this->cx = this->cy = -1;
    }
    else
        this->isEnd = true;
    return true;
}

std::ostream &operator<<(std::ostream &out, const UltimateTicTacToe &ttt)
{
    int dx, dy;
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            dx = j / 3;
            dy = i / 3;

            bool cond = (ttt.cx == -1 && ttt.cy == -1) || (ttt.cx == dx && ttt.cy == dy);
            cond = cond || (j % 3 == 0 && ttt.cx == dx - 1 && ttt.cy == dy);
            cond = cond || (i % 3 == 0 && ttt.cy == dy - 1 && ttt.cx == dx);
            cond = cond || (j % 3 == 0 && ttt.cx == dx - 1 && i % 3 == 0 && ttt.cy == dy - 1);

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

            cond = (ttt.cx == -1 && ttt.cy == -1) || (ttt.cx == dx && ttt.cy == dy);
            cond = cond || (i % 3 == 0 && ttt.cy == dy - 1 && ttt.cx == dx);

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

                bool cond = (ttt.cx == -1 && ttt.cy == -1) || (ttt.cx == dx && ttt.cy == dy);
                cond = cond || (j % 3 == 0 && ttt.cx == dx - 1 && ttt.cy == dy);

                if (cond)
                    out << Color(255, 255, 0);
                else
                    out << ColorEffect::RESET;

                if (j % 3)
                    out << "│";
                else
                    out << "┃";

                cond = (ttt.cx == -1 && ttt.cy == -1) || (ttt.cx == dx && ttt.cy == dy);

                if (cond)
                    out << Color(255, 255, 0);
                else
                    out << ColorEffect::RESET;

                if (j < 9)
                    out << " "
                        << " XO"[ttt.board[dy][dx].AtBoard(i % 3, j % 3)] << " ";
            }
            out << "\n";
        }
    }
    return out;
}
