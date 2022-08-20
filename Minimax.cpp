#include "Minimax.h"
Minimax::Minimax()
{
	for (int row = 0; row < 3; row++)
		for (int col = 0; col < 3; col++)
			transition[row][col] = 0;
}
void Minimax::min_value(int state[][3], int move[])
{
	if (is_terminal(state))
	{
		move[0] = -1;
		move[1] = -1;
		move[2] = utility(state);
	}
	else
	{
		move[2] = 100000;
		int a[9][2];//possible moves or actions
		for (int i = 0; i < 9; i++)
			a[i][0] = 3;//initialize actions array to 3
		actions(a, state);
		int i = 0;
		while (a[i][0] != 3)
		{
			int move2[3];
			result(state, a[i]);//assign next transition state/player to move
			max_value(transition, move2);
			if (move2[2] < move[2]) //return next action and it's utility value
			{
				move[0] = a[i][0];
				move[1] = a[i][1];
				move[2] = move2[2];
			}
			i++;
		}
	}
}

void Minimax::max_value(int state[][3], int move[])
{
	if (is_terminal(state))
	{

		move[0] = -1;
		move[1] = -1;
		move[2] = utility(state);
	}
	else
	{
		move[2] = -100000;
		int a[9][2];//possible moves or actions
		for (int i = 0; i < 9; i++)
			a[i][0] = 3;//initialize actions array to 3
		actions(a, state);
		int i = 0;
		while (a[i][0] != 3)
		{
			int move2[3];
			result(state, a[i]);//assign next transition state
			min_value(transition, move2);
			if (move2[2] > move[2]) //return next action and it's utility value
			{
				move[0] = a[i][0];
				move[1] = a[i][1];
				move[2] = move2[2];
			}
			i++;
		}
	}
}

void Minimax::to_move(int state[][3])//Check which turn it is assuming X goes first
{
	player = 0;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			player += state[i][j]; //if 0 MAX's move, else if 1, MIN's Move
	if (player == 1)
		player = -player;//if max just went, player = -1 to indicate min's move
	else
		player = 1;
}

bool Minimax::is_terminal(int state[][3])//check if state is terminal 
{
	for (int i = 0; i < 3; i++)
	{
		if (state[i][0] == state[i][1] && state[i][1] == state[i][2] && state[i][0] != 0)//check horizontals
			return true;
		if (state[0][i] == state[1][i] && state[2][i] == state[1][i] && state[0][i] != 0)//check verticals
			return true;

	}
	if (state[0][0] == state[1][1] && state[1][1] == state[2][2] && state[2][2] != 0)
		return true;//check 1st diagonal
	if (state[0][2] == state[1][1] && state[1][1] == state[2][0] && state[2][0] != 0)
		return true;//check 2nd diagonal
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (state[i][j] == 0)//move available, not terminal
			{
				return false;
			}
		}
	}
	return true;
}

int Minimax::utility(int state[][3]) //get utility value of terminal state
{
	for (int i = 0; i < 3; i++)
	{
		if (state[i][0] == state[i][1] && state[i][1] == state[i][2])//check horizontals
		{
			return state[i][0];//will return -1 if O wins, else returns 1 if X wins
		}
		if (state[0][i] == state[1][i] && state[1][i] == state[2][i])//check verticals
		{
			return state[0][i];//return utility value
		}
	}
	if (state[0][0] == state[1][1] && state[1][1] == state[2][2])//check diagonals
		return state[0][0];
	if (state[0][2] == state[1][1] && state[1][1] == state[2][0])
		return state[0][2];
	return 0;//returns 0 if no winner was decided
}

void Minimax::actions(int a[][2], int state[][3]) //get possible actions
{
	int k = 0;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			// find an empty square
			if (state[i][j] == 0)
			{
				a[k][0] = i;//assign new possible action row
				a[k][1] = j;//col
				k++;//iterate for next action, else action array filled with -2
			}
}

void Minimax::result(int state[][3], int a[])
{
	to_move(state);
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (a[0] == i && a[1] == j)
				transition[i][j] = player;//assign next transition
			else
				transition[i][j] = state[i][j];//assign current state
		}
	}
	to_move(transition);//assign player for next transition
}
