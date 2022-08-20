//
//  Board.cpp
//  Connect4
//
//  Created by Brendan Aguiar on 8/6/22.
//

#include "Board.hpp"
#include "Player.hpp"

Board::Board()
{
    for (int m = 0; m < 6; m++)
    {
        for (int n = 0; n < 7; n++)
            grid[m][n] = 0;
    }
    winner = 'T';//Initialize to Tie
}

void Board::apply_states(int state[][7])
{
    for (int row = 0; row < 6; row++)
        for (int col = 0; col < 7; col++)
            state[row][col] = grid[row][col];
}

void Board::set_players(const Player p[])
{
    for(int i = 0; i < 2; i++)
        player[i] = p[i];
}

void Board::make_move(const Player& p)
{
    bool grant = false;
    while (!grant)
    {
        display_grid();
        int space;
        cout << "\n\nPlayer " << p.get_token() << " Choose your position: ";
        cin >> space;
        if (space > 6 || space < 0)
            cout << "\n\nSpace out of bounds. Try again.\n\n";
        else if (grid[0][space] != 0)
            cout << "\n\nSpace filled up. Try again.\n\n" << grid[0][space] << endl;
        else
        {
            grant = true;
            int m = 5;
            while (grid[m][space] != 0)
                m--;
            if (p.get_token() == player[0].get_token())
                grid[m][space] = -1;
            else
                grid[m][space] = 1;
        }
    }
}

void Board::display_grid() const
{
    cout << endl;
    for (int pos = 0; pos < 7; pos++)
        cout << "   " << pos;
    cout << endl << endl;
    for (int m = 0; m < 6; m++)
    {
        cout << " | ";
        for (int n = 0; n < 7; n++)
        {
            if (grid[m][n] == -1)
                cout << '@' << " | ";
            else if (grid[m][n] == 1)
                cout << '#' << " | ";
            else
                cout << 'O' << " | ";
        }
        cout << endl;
    }
}

void Board::make_move_AI(const Player& p, const int& _move)
{
    int row = 1;
    int i = 0;
    while (i < 6)//search for row to place token into
    {
        if (grid[row - 1][_move] == 0)
            row++;
        i++;
    }
    grid[row][_move] = -1;//p.get_token();
}


bool Board::check_for_winner(const Player& p) const
{
    int aligned = 0;
    int utility;
    if (p.get_token() == '@')
        utility = -1;
    else
        utility = 1;
    for (int row = 5; row >= 0; row--)//check horizontal
    {
        for (int col = 6; col >= 0; col--)
        {
            if (grid[row][col] == utility)
            {
                aligned++;
                if (aligned == 4)
                    return true;
            }
            else
            {
                aligned = 0;
                if (col == 3)
                    col = -1;
            }
        }
    }
    if (check_vertical(grid, p))//check vertical
        return true;
    if (check_diagN(p))//check diagonal with negative slope
        return true;
    if (check_diagP(p))
        return true;
    if (check_for_tie())
        return true;
    return false;
}


bool Board::check_for_tie() const
{
    int count = 0;
    for (int row = 0; row < 6; row++)
    {
        for (int col = 0; col < 7; col++)
        {
            if (grid[row][col] != 0)
                count++;
        }
    }
    if (count == 42)
        return true;
    return false;
}


bool Board::check_vertical(const int _grid[][7], const Player& p) const
{
    int aligned = 0;
    int utility;
    if (p.get_token() == '@')
        utility = -1;
    else
        utility = 1;
    for (int col = 6; col >= 0; col--)//check verticals
    {
        for (int row = 5; row >= 0; row--)
        {
            if (_grid[row][col] == utility)
            {
                aligned++;
                if (aligned == 4)
                {
                    return true;
                }
            }
            else
            {
                aligned = 0;
                if (row == 3)
                    row = -1;
            }
        }
    }
    return false;
}


char Board::get_winner() const
{
    return winner;
}


void Board::set_winner(const Player& p)
{
    winner = p.get_token();
}


bool Board::check_diagN(const Player& p) const
{
    int start = 5;
    int shift = 3;
    int stop = 2;
    while (stop >= 0)
    {
        int transition[6][7] = {};
        for (int row = start; row >= stop; row--)
        {
            for (int col = 0; col < 4; col++)
            {
                transition[row][col] = grid[row][col + shift];
            }
            shift--;
        }
        if (check_vertical(transition, p))
            return true;
        stop--;
        start--;
        shift = 3;
    }
    return false;
}

bool Board::check_diagP(const Player& p) const
{
    int start = 5;
    int shift = 3;
    int stop = 2;
    while (stop >= 0)
    {
        int transition[6][7] = {};
        for (int row = start; row >= stop; row--)
        {
            for (int col = 6; col >= 3; col--)
            {
                transition[row][col] = grid[row][col - shift];
            }
            shift--;
        }
        if (check_vertical(transition, p))
            return true;
        stop--;
        start--;
        shift = 3;
    }
    return false;
}


int Board::get_space(const int& row, const int& col) const
{
    return grid[row][col];
}
