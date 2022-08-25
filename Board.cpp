//
//  Board.cpp
//  Template Practice
//
//  Created by Brendan Aguiar on 8/24/22.
//

#include "Board.hpp"

template <typename Datatype>
Board<Datatype>::Board(Datatype _empty_space)
{
    for (int m = 0; m < 6; m++)
    {
        for (int n = 0; n < 7; n++)
            grid[m][n] = _empty_space;
    }
    empty_space = _empty_space;
    winner = 'T';//Initialize to Tie
}

template <typename Datatype>
void Board<Datatype>::set_players(const Player<Datatype> p[])
{
    for(int i = 0; i < 2; i++)
        player[i] = p[i];
}
template <typename Datatype>
void Board<Datatype>::make_move(const Player<Datatype>& p)
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
        else if (grid[0][space] != empty_space)
            cout << "\n\nSpace filled up. Try again.\n\n" << grid[0][space] << endl;
        else
        {
            grant = true;
            int m = 5;
            while (grid[m][space] != empty_space)
                m--;
            if (p.get_token() == player[0].get_token())
                grid[m][space] = p.get_token();
            else
                grid[m][space] = player[1].get_token();
        }
    }
}
template <typename Datatype>
void Board<Datatype>::make_move_AI(const int& _move)
{
    int row = 1;
    int i = 0;
    while (i < 6)//search for row to place token into
    {
        if (grid[row - 1][_move] == empty_space)
            row++;
        i++;
    }
    grid[row][_move] = -1;
}
template <typename Datatype>
void Board<Datatype>::display_grid() const
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
            if (grid[m][n] == player[0].get_token())
                cout << '@' << " | ";
            else if (grid[m][n] == player[1].get_token())
                cout << '#' << " | ";
            else
                cout << 'O' << " | ";
        }
        cout << endl;
    }
}
template <typename Datatype>
bool Board<Datatype>::check_for_winner(const Player<Datatype>& p) const
{
    int aligned = 0;
    Datatype utility;
    if (p.get_token() == player[0].get_token())
        utility = player[0].get_token();
    else
        utility = player[1].get_token();
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
    if (check_vertical(this->grid, p))//check vertical
        return true;
    if (check_diagN(p))//check diagonal with negative slope
        return true;
    if (check_diagP(p))
        return true;
    if (check_for_tie())
        return true;
    return false;
}
template <typename Datatype>
bool Board<Datatype>::check_vertical(const Datatype _grid[][7], const Player<Datatype>& p) const
{
    int aligned = 0;
    Datatype utility;
    if (p.get_token() == player[0].get_token())
        utility = player[0].get_token();
    else
        utility = player[1].get_token();
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
template <typename Datatype>
bool Board<Datatype>::check_diagP(const Player<Datatype>& p) const
{
    int start = 5;
    int shift = 3;
    int stop = 2;
    while (stop >= 0)
    {
        Datatype transition[6][7] = {};
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
template <typename Datatype>
bool Board<Datatype>::check_diagN(const Player<Datatype>& p) const
{
    int start = 5;
    int shift = 3;
    int stop = 2;
    while (stop >= 0)
    {
        Datatype transition[6][7] = {};
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
template <typename Datatype>
bool Board<Datatype>::check_for_tie() const
{
    int count = 0;
    for (int row = 0; row < 6; row++)
    {
        for (int col = 0; col < 7; col++)
        {
            if (grid[row][col] != empty_space)
                count++;
        }
    }
    if (count == 42)
        return true;
    return false;
}
template <typename Datatype>
void Board<Datatype>::set_winner(const Player<Datatype>& p)
{
    winner = p.get_token();
}
template <typename Datatype>
Datatype Board<Datatype>::get_winner() const
{
    return winner;
}
