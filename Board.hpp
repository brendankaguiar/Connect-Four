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
    int grid[6][7];
    Player player[2];
    char winner;
public:
    Board();
    void apply_states(int state[][7]);
    void set_players(const Player p[]);
    void display_grid() const;
    void make_move(const Player& p);
    void make_move_AI(const Player& p, const int& _move);
    bool check_for_winner(const Player& p) const;
    void set_winner(const Player& p);
    char get_winner() const;
    bool check_diagN(const Player& p) const;
    bool check_diagP(const Player& p) const;
    bool check_vertical(const int _grid[][7], const Player& p) const;
    int get_space(const int& row, const int& col) const;
    bool check_for_tie() const;
};

#endif /* Board_hpp */
