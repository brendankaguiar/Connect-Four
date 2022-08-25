//
//  Board.hpp
//  Template Practice
//
//  Created by Brendan Aguiar on 8/24/22.
//

#ifndef Board_hpp
#define Board_hpp
#include "Player.hpp"
#include <iostream>
using namespace std;

template <typename Datatype>
class Board
{
private:
    Datatype grid[6][7];
    Player<Datatype> player[2];
    Datatype winner;
    Datatype empty_space;
public:
    Board(Datatype empty_space);
    void set_players(const Player<Datatype> p[]);
    void make_move(const Player<Datatype>& p);
    void make_move_AI(const int& _move);
    bool check_for_winner(const Player<Datatype>& p) const;
    void set_winner(const Player<Datatype>& p);
    void display_grid() const;
    bool check_diagN(const Player<Datatype>& p) const;
    bool check_diagP(const Player<Datatype>& p) const;
    bool check_vertical(const Datatype _grid[][7], const Player<Datatype>& p) const;
    bool check_for_tie() const;
    Datatype get_winner() const;
};
#endif /* Board_hpp */
