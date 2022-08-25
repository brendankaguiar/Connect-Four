//
//  Player.cpp
//  Template Practice
//
//  Created by Brendan Aguiar on 8/24/22.
//

#include "Player.hpp"

template <typename Datatype>
Player<Datatype>::Player(Datatype _token)
{
    token = _token;
};

template <typename Datatype>
Datatype Player<Datatype>::get_token() const
{
    return token;
}
