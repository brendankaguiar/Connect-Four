//
//  Board.hpp
//  Connect4
//
//  Created by Brendan Aguiar on 8/6/22.
//

#ifndef Board_hpp
#define Board_hpp
#include <iostream>
#include <vector>
#include <string>
#include "Player.hpp"
using namespace std;
class Board
{
private:
    char grid[7][7];
    char winner;
public:
    Board();
    void apply_states(int state[][7]);
    void get_grid(int _grid[][7]);
    void make_move(Player p);
    void make_move_AI(Player p, int _move);
    void display_grid();
    bool check_for_winner(Player p);
    void set_winner(Player p);
    char get_winner();
    bool check_diagN(Player p);
    bool check_diagP(Player p);
    bool check_vertical(char _grid[][7], Player p);
    char get_space(int row, int col);
    bool check_for_tie();
};

#endif /* Board_hpp */
