//
//  Player.hpp
//  Connect4
//
//  Created by Brendan Aguiar on 8/6/22.
//

#ifndef Player_hpp
#define Player_hpp
#include <iostream>
using namespace std;

class Player
{
private:
    char token;
public:
    Player();
    Player(char _token);
    char get_token();
};

#endif /* Player_hpp */
