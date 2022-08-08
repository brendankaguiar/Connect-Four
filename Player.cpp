//
//  Player.cpp
//  Connect4
//
//  Created by Brendan Aguiar on 8/6/22.

#include "Player.hpp"
Player::Player(char _token) :token(_token){}
Player::Player(){};
char Player::get_token()
{
    return token;
}
