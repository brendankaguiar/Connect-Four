#include "Board.hpp"
#include "Player.hpp"
Player player[2];
Board board;
void setup();
void play();
int main()
{
    Board connect_4;
    setup();
    play();
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
