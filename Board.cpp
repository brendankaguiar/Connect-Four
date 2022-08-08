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
    for (int m = 0; m < 7; m++)
    {
        for (int n = 0; n < 7; n++)
        {
            grid[m][n] = 'O';
            if (m == 6)
                grid[m][n] = '-';
        }
    }
}

void Board::display_grid()
{
    cout << endl;
    for (int pos = 0; pos < 7; pos++)
        cout << "   " << pos;
    cout << endl << endl;
    for (int m = 0; m < 7; m++)
    {
        cout << " | ";
        for (int n = 0; n < 7; n++)
            cout << grid[m][n] << " | ";
        cout << endl;
    }
}
void Board::make_move(Player p)
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
        else if (grid[0][space] != 'O')
            cout << "\n\nSpace filled up. Try again.\n\n" << grid[0][space] << endl;
        else
        {
            grant = true;
            int m = 5;
            while(grid[m][space] != 'O')
                m--;
            grid[m][space] = p.get_token();
        }
    }
}
bool Board::check_for_winner(Player p)
{
    //bool hoz = false;
    int aligned = 0;
    for (int row = 5; row >= 0; row--)//check horizontal
    {
        for (int col = 6; col >= 0; col--)
        {
            if(grid[row][col] == p.get_token())
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
    if (this->check_vertical(grid, p))//check vertical
        return true;
    if (this->check_diagN(p))//check diagonal with negative slope
        return true;
    if (this->check_diagP(p))
        return true;
    return false;
}
bool Board::check_vertical(char _grid[][7], Player p)
{
    int aligned =0;
    for (int col = 6; col >= 0; col--)//check verticals
    {
        for (int row = 5; row >= 0; row--)
        {
            if(_grid[row][col] == p.get_token())
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
char Board::get_winner()
{
    return winner;
}
void Board::set_winner(Player p)
{
    winner = p.get_token();
}
bool Board::check_diagN(Player p)
{
    int start = 5;
    int shift = 3;
    int stop = 2;
    while(stop >= 0)
    {
        char transition[6][7];
        for (int row = start; row >= stop; row--)
        {
            for (int col = 0; col < 4; col++)
            {
                transition[row][col] = grid[row][col + shift];
            }
            shift--;
        }
        if (this->check_vertical(transition, p))
            return true;
        stop--;
        start--;
        shift = 3;
    }
    return false;
}
bool Board::check_diagP(Player p)
{
    int start = 5;
    int shift = 3;
    int stop = 2;
    while(stop >= 0)
    {
        char transition[6][7];
        for (int row = start; row >= stop; row--)
        {
            for (int col = 6; col >= 3; col--)
            {
                transition[row][col] = grid[row][col - shift];
            }
            shift--;
        }
        if (this->check_vertical(transition, p))
            return true;
        stop--;
        start--;
        shift = 3;
    }
    return false;
}

