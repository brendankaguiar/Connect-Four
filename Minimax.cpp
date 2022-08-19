#include "Minimax.hpp"
Minimax::Minimax()
{
	for (int row = 0; row < 6; row++)
		for (int col = 0; col < 7; col++)
			transition[row][col] = 0;
}
void Minimax::min_value(int state[][7], int move[])
{
	if (is_terminal(state))
	{
		move[0] = -1;
		move[1] = utility(state);
	}
	else
	{
		move[1] = 100000;
		int a[7];//possible moves or actions
		for (int i = 0; i < 7; i++)
			a[i] = -1;//initialize actions array to 3
		actions(a, state);
		int i = 0;
		while (a[i] != -1)
		{
			int move2[2];
			result(state, a[i]);//assign next transition state/player to move
			max_value(transition, move2);
			if (move2[1] < move[1]) //return next action and it's utility value
			{
				move[0] = a[i];
				move[1] = move2[1];
			}
			i++;
		}
	}
}

void Minimax::max_value(int state[][7], int move[])
{
	if (is_terminal(state))
	{
		move[0] = -1;
		move[1] = utility(state);
	}
	else
	{
		move[1] = -100000;
		int a[7];//possible moves or actions
		for (int i = 0; i < 7; i++)
			a[i] = -1;//initialize actions array to 3
		actions(a, state);
		int i = 0;
		while (a[i] != -1)
		{
			int move2[2];
			result(state, a[i]);//assign next transition state
			min_value(transition, move2);
			if (move2[1] > move[1]) //return next action and it's utility value
			{
				move[0] = a[i];
				move[1] = move2[1];
			}
			i++;
		}
	}
}

void Minimax::to_move(int state[][7])//Check which turn it is assuming X goes first
{
	player = 0;
	for (int row = 0; row < 6; row++)
		for (int col = 0; col < 7; col++)
			player += state[row][col];	
	if (player == 0)
		player = -1;//min's move
	else
		player = 1;//max's move
}

bool Minimax::is_terminal(int state[][7])//check if state is terminal 
{
	if (check_for_winner(state, -1) || check_for_winner(state,1))
		return true;
	else
		return false;
}

int Minimax::utility(int state[][7]) //get utility value of terminal state
{
	for (int row = 0; row < 3; row++)//check horizontals
	{
		for (int col = 0; col < 4; col++)
		{
			if (state[row][0 + col] == state[row][1 + col] 
				&& state[row][1 + col] == state[row][2 + col] && state[row][2 + col] == state[row][3 + col])
			{
				return state[row][col];//will return -1 if O wins, else returns 1 if X wins
			}
		}
	}
	for (int col = 0; col < 7; col++)//check verticals
	{
		for (int row = 0; row < 3; row++)
		{
			if (state[row + 0][col] == state[1 + row][col] && state[row + 1][col] == state[row + 2][col]
				&& state[2 + row][col] == state[row + 3][col])//check verticals
			{
				return state[row][col];//return utility value
			}
		}
	}
	if (check_diagN(1, state) || check_diagP(1, state))
		return 1;
	if (check_diagN(-1, state) || check_diagP(-1, state))
		return -1;
	return 0;//returns 0 if no winner was decided
}

void Minimax::actions(int a[], int state[][7]) //get possible actions
{
	int k = 0;
	for (int col = 0; col < 7; col++)
	{
		if (state[0][col] == 0)
		{
			a[k] = col;
			k++;
		}
	}
}

void Minimax::result(int state[][7], int a)
{
	to_move(state);
	for (int row = 0; row < 6; row++)
	{
		for (int col = 0; col < 7; col++)
			transition[row][col] = state[row][col];//update transition
	}
	int row = 0;
	int i = 0;
	while (i < 6)//search for row to place token into
	{
		if (state[i][a] == 0)
			row++;
		i++;
	}
	transition[row - 1][a] = player;//place new token
	to_move(transition);//assign player for next transition
}

bool Minimax::check_for_winner(int grid[][7], int p)
{
	int aligned = 0;
	for (int row = 5; row >= 0; row--)//check horizontal
	{
		for (int col = 6; col >= 0; col--)
		{
			if (grid[row][col] == p)
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
	if (check_diagN(p, grid))//check diagonal with negative slope
		return true;
	if (check_diagP(p, grid))
		return true;
	if (check_for_tie(grid))
		return true;
	return false;
}


bool Minimax::check_for_tie(int grid[][7])
{
	int count = 0;
	for (int row = 0; row < 6; row++)
	{
		for (int col = 0; col < 7; col++)
		{
			if (grid[row][col] == 'O')
				count++;
		}
	}
	if (count == 42)
		return true;
	return false;
}
bool Minimax::check_vertical(int _grid[][7], int p)
{
	int aligned = 0;
	for (int col = 6; col >= 0; col--)//check verticals
	{
		for (int row = 5; row >= 0; row--)
		{
			if (_grid[row][col] == p)
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
bool Minimax::check_diagN(int p, int grid[][7])
{
	int start = 5;
	int shift = 3;
	int stop = 2;
	while (stop >= 0)
	{
		int transition[6][7];
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
bool Minimax::check_diagP(int p, int grid[][7])
{
	int start = 5;
	int shift = 3;
	int stop = 2;
	while (stop >= 0)
	{
		int transition[6][7];
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