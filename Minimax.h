#ifndef Minimax_H
#define Minimax_H
#include "Board.hpp"
class Minimax
{
public:
	Minimax();
	void to_move(int state[][7]);
	bool is_terminal(int state[][7]);
	int utility(int state[][7]);
	void actions(int a[], int state[][7]);
	void result(int state[][7], int a);
	void max_value(int state[][7], int move[]);
	void min_value(int state[][7], int move[]);
	bool check_for_winner(const int state[][7], const int utility) const;
	bool check_vertical(const int state[][7], const int utility) const;
	bool check_diagN(const int state[][7], const int utility) const;
	bool check_diagP(const int state[][7], const int utility) const;
	bool check_for_tie(const int state[][7]) const;
private:
	int transition[6][7];
	int player;
};
#endif
