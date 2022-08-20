#include "Board.hpp"
#include "Player.hpp"
#include "Minimax.h"
Player player[2];
Board board;
int _winner = 0;
int turn;
void setup();
void single_player();
void two_player();

int main()
{
    int num_players = 0;
    bool grant = false;
    while (!grant)
    {
        cout << "How many players? Between 1 and 2 please.\n\nChoose: ";
        cin >> num_players;
        if (num_players > 2 || num_players < 1)
            cout << "Number of players out of range. Try again.\n\n";
        else
            grant = true;
    }
    setup();
    if (num_players == 2)//Two Player Game
        two_player();
    else//AI based game
        single_player();
    return 0;
}
void single_player()
{
    cout << "working on it.\n";
    bool gameOver = false;
    int move[2];
    int state[6][7];
    while (!gameOver)
    {
        cout << "\n\nPlayer " << 1 << endl;//player 1 moves
        board.make_move(player[0]);
        gameOver = board.check_for_winner(player[0].get_token());
        if (!gameOver)
        {
            board.apply_states(state);
            Minimax game;
            game.max_value(state, move);
            board.make_move_AI(player[1], move[0]);
            gameOver = board.check_for_winner(player[1].get_token());
            if (gameOver)
                board.set_winner(player[1]);
        }
        else
            board.set_winner(player[0]);
    }
    board.display_grid();
    cout << "Player " << board.get_winner() << " won.\n\n";
}
void two_player()
{
    bool gameOver = false;
    while (!gameOver)
    {
        for (int i = 0; i < 2; i++)
        {
            cout << "\n\nPlayer " << i + 1 << endl;
            board.make_move(player[i]);
            gameOver = board.check_for_winner(player[i].get_token());
            if (gameOver)
            {
                if (board.check_for_tie())
                    cout << "It's a Tie!\n\n";
                else
                {
                    board.set_winner(player[i]);
                    cout << "Player " << i + 1 << " : " << player[i].get_token() << " won.\n\n";
                }
                board.display_grid();
                i = 2;
            }
        }
    }
}
void setup()
{
    char _token[2] = { '@', '#' };
    for (int i = 0; i < 2; i++)
    {
        cout << "Player " << i + 1 << ": " << _token[i] << " is your token.\n";
        Player p(_token[i]);
        player[i] = p;
    }
    board.set_players(player);
}
