//
//  Minimax.hpp
//  Template Practice
//
//  Created by Brendan Aguiar on 8/24/22.
//

#ifndef Minimax_hpp
#define Minimax_hpp
#include <iostream>
class Minimax
{
private:
    int transition[6][7];
    int player;
public:
    Minimax();
    void to_move(int state[][7]);
    void max_value(int state[][7], int move[]);
    void min_value(int state[][7], int move[]);
    bool is_terminal(int state[][7]);
    int utility(int state[][7]);
    void actions(int a[], int state[][7]);
    void result(int state[][7], int a);
    bool check_for_winner(const int state[][7], const int utility) const;
    bool check_vertical(const int state[][7], const int utility) const;
    bool check_diagN(const int state[][7], const int utility) const;
    bool check_diagP(const int state[][7], const int utility) const;
    bool check_for_tie(const int state[][7]) const;
};
#endif /* Minimax_hpp */
