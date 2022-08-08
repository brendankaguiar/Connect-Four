#include "Board.hpp"
#include "Player.hpp"
Player player[2];
Board board;
int _winner = 0;
int turn;
void setup();
void play();
void load_state(int _state[][7]);
void max_value(int _state[][7], int _move[]);
void min_value(int _state[][7], int _move[]);
bool is_terminal(int _state[][7], Player p);
bool check_vertical(int _grid[][7], Player p);
bool check_diagN(int _state[][7], Player p);
bool check_diagP(int _state[][7], Player p);
bool check_for_tie(int _state[][7]);
int utility(int _state[][7]);
void actions(int _a[], int _state[][7]);
void result(int _state[][7], int a);
void to_move(int _state[][7]);
int transition[6][7];
int main()
{
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
    if (num_players == 2)//Two Player Game
    {
        setup();
        play();
    }
    else//AI based game
    {
        int state[6][7], move[2];//move[0] = move to make, move[1] = value
        bool gameOver = false;
        while (!gameOver)
        {
            for (int i = 0; i < 2; i++)
            {
                if(i == 0)//Player 1 moves
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
                else//AI Player moves
                {
                    load_state(state);
                    max_value(state, move);
                    board.make_move_AI(player[i], move[0]);
                    gameOver = board.check_for_winner(player[i]);
                    if(gameOver)
                    {
                        board.set_winner(player[i]);
                        board.display_grid();
                        cout << "AI Player won.\n\n";
                        i = 2;
                    }
                }
            }
        }
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
void load_state(int _state[][7])
{
    for (int row = 0; row < 6; row++)
    {
        for (int col = 0; col < 7; col++)
        {
            char token = board.get_space(row, col);
            if (token == '@')
                _state[row][col] = 1;
            else if (token == '#')
                _state[row][col] = -1;
            else
                _state[row][col] = 0;
            //cout << _state[row][col];
        }
        //cout << endl;
    }
}
void min_value(int _state[][7], int _move[])
{
    if (is_terminal(_state, player[0]) || is_terminal(_state, player[1]))
        {
        _move[0] = -1;//no more moves to make
        _move[1] = _winner;
    }
    else
    {
        _move[1] = 100;
        int a[7];//positions for possible actions
        for (int pos = 0; pos < 7; pos++)
            a[pos] = -1;
        actions(a,_state);
        int i = 0;
        while(a[i] != -1)
        {
            int move2[2];
            result(_state, a[i]);
            max_value(transition, move2);
            if (move2[1] < _move[1])//return next action and it's utility value
            {
                _move[0] = a[i];
                _move[1] = move2[1];
            }
            i++;
        }
    }
}
void max_value(int _state[][7], int _move[])
{
    if (is_terminal(_state, player[0]) || is_terminal(_state, player[1]))
        {
        _move[0] = -1;//no more moves to make
        _move[1] = _winner;
    }
    else
    {
        _move[1] = -100;
        int a[7];//positions for possible actions
        for (int pos = 0; pos < 7; pos++)
            a[pos] = -1;
        actions(a,_state);
        int i = 0;
        while(a[i] != -1)
        {
            int move2[2];
            result(_state, a[i]);
            min_value(transition, move2);
            if (move2[1] > _move[1])//return next action and it's utility value
            {
                _move[0] = a[i];
                _move[1] = move2[1];
            }
            i++;
        }
    }
}
bool is_terminal(int _state[][7], Player p)
{
    int aligned = 0;
    int token;
    if (p.get_token() == '@')
        token = -1;
    else
        token = 1;
    for (int row = 5; row >= 0; row--)//check horizontal
    {
        for (int col = 6; col >= 0; col--)
        {
            if(_state[row][col] == token)
            {
                aligned++;
                if (aligned == 4)
                {
                    _winner = token;
                    return true;
                }
            }
            else
            {
                aligned = 0;
                if (col == 3)
                    col = -1;
            }
        }
    }
    if (check_vertical(_state, p))//check vertical
    {
        _winner = token;
        return true;
    }
    if (check_diagN(_state, p))//check diagonal with negative slope
    {
        _winner = token;
        return true;
    }
    if (check_diagP(_state, p))
    {
        _winner = token;
        return true;
    }
    if (check_for_tie(_state))
    {
        _winner = 0;
        return true;
    }
    return false;
}
bool check_for_tie(int _state[][7])
{
    int count = 0;
    for (int row = 0; row < 6; row++)
    {
        for (int col = 0; col < 7; col++)
        {
            if (_state[row][col] != 0)
                count++;
        }
    }
    if (count == 42)
    {
        _winner = 0;
        return true;
    }
    return false;
}
bool check_vertical(int _state[][7], Player p)
{
    int aligned = 0;
    int token;
    if (p.get_token() == '@')
        token = -1;
    else
        token = 1;
    for (int col = 6; col >= 0; col--)//check verticals
    {
        for (int row = 5; row >= 0; row--)
        {
            if(_state[row][col] == token)
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
bool check_diagN(int _state[][7], Player p)
{
    int start = 5;
    int shift = 3;
    int stop = 2;
    while(stop >= 0)
    {
        int transition[6][7];
        for (int row = start; row >= stop; row--)
        {
            for (int col = 0; col < 4; col++)
            {
                transition[row][col] = _state[row][col + shift];
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
bool check_diagP(int _state[][7], Player p)
{
    int start = 5;
    int shift = 3;
    int stop = 2;
    while(stop >= 0)
    {
        int transition[6][7];
        for (int row = start; row >= stop; row--)
        {
            for (int col = 6; col >= 3; col--)
            {
                transition[row][col] = _state[row][col - shift];
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
void actions(int _a[], int _state[][7])
{
    int k = 0;
    for (int col = 0; col < 7; col++)
    {
        if (_state[0][col] == 0)
        {
            _a[k] = col;
            k++;
        }
    }
}

void result(int _state[][7], int a)
{
    to_move(_state);
    for(int row = 0; row < 6; row++)//apply current state to transition
        for (int col = 0; col < 7; col++)
            transition[row][col] = _state[row][col];
    for (int col = 0; col < 7; col++)
    {
        if (a == col)
        {
            int row = 0;
            while (_state[row][col] != 'O')
                transition[row - 1][col] = turn;//make next transition move
        }
    }
    to_move(transition);//assign turn for next transition
}
void to_move(int _state[][7])
{
    turn = 0;
    for (int row = 0; row < 6; row++)
        for (int col = 0; col < 7; col++)
            turn += _state[row][col];
    if (turn == 1)
        turn = -1;//min's move
    else
        turn = 1;//max's move
}
