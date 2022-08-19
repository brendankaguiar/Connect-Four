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
	bool check_for_winner(int state[][7], int player);
	bool check_vertical(int state[][7], int player);
	bool check_diagN(int player, int grid[][7]);
	bool check_diagP(int player, int grid[][7]);
	bool check_for_tie(int grid[][7]);
private:
	int transition[6][7];
	int player;
};
#endif