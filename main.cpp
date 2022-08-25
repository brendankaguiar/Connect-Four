//
//  main.cpp
//  Template Practice
//
//  Created by Brendan Aguiar on 8/24/22.
//
#include <iostream>
using namespace std;
#include "Player.cpp"
#include "Board.cpp"
#include "Minimax.hpp"
void two_setup();
void one_setup();
void single_player();
void two_player();
Board<char> board('O');
Player<char> player[2];
Player<int> AIplayer[2];
Board<int> AIboard(0);
int main() {
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
    if (num_players == 2)//Two Player Game
        two_player();
    else//AI based game
        single_player();
    return 0;
}

void two_setup()
{
    char _token[2] = { '@', '#' };
    for (int i = 0; i < 2; i++)
    {
        cout << "Player " << i + 1 << ": " << _token[i] << " is your token.\n";
        Player<char> p(_token[i]);
        player[i] = p;
    }
    board.set_players(player);
}
void one_setup()
{
    int _token[2] = {-1, 1};
    char token[2] = { '@', '#' };
    for (int i = 0; i < 2; i++)
    {
        cout << "Player " << i + 1 << ": " << token[i] << " is your token.\n";
        Player<int> p(_token[i]);
        AIplayer[i] = p;
    }
}
void two_player()
{
    two_setup();
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
void single_player()
{
    one_setup();
    bool gameOver = false;
    int move[2];
    int state[6][7];
    while (!gameOver)
   {
       cout << "\n\nPlayer " << 1 << endl;//player 1 moves
       AIboard.make_move(AIplayer[0]);
       gameOver = AIboard.check_for_winner(AIplayer[0].get_token());
       if (!gameOver)
       {
           Minimax game;
           game.max_value(state, move);
           AIboard.make_move_AI(move[0]);
           gameOver = AIboard.check_for_winner(AIplayer[1].get_token());
           if (gameOver)
               AIboard.set_winner(AIplayer[1]);
       }
       else
                   AIboard.set_winner(AIplayer[0]);
   }
    AIboard.display_grid();
    cout << "Player " << AIboard.get_winner() << " won.\n\n";
}
