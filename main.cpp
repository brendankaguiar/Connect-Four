#include "Board.hpp"
#include "Player.hpp"
Player player[2];
Board board;
void setup();
void play();
int main()
{
    Board connect_4;
    int num_players = 0;
    bool grant = false;
    while(!grant)
    {
        cout << "How many players? Between 1 and 2 please.\n\nChoose: ";
        cin >> num_players;
        if (num_players > 2 || num_players < 1)
            cout << "Number of players out of range. Try again.\n\n";
        else
            grant = true;
    }
    if (num_players == 2)
    {
        setup();
        play();
    }
    return 0;
}
void play()
{
    bool gameOver = false;
    while (!gameOver)
    {
        for (int i = 0; i < 2; i++)
        {
            cout << "\n\nPlayer " << i + 1 << endl;
            board.make_move(player[i]);
            gameOver = board.check_for_winner(player[i]);
            if(gameOver)
            {
                board.set_winner(player[i]);
                board.display_grid();
                cout << "Player " << i + 1 << " won.\n\n";
                i = 2;
            }
        }
    }
}
void setup()
{
    char _token[2] = {'@', '#'};
    for (int i = 0; i < 2; i++)
    {
        cout << "Player " << i + 1 << ": " << _token[i] << " is your token.\n";
        Player p(_token[i]);
        player[i] = p;
    }
}
