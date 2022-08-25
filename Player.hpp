//
//  Player.hpp
//  Template Practice
//
//  Created by Brendan Aguiar on 8/24/22.
//

#ifndef Player_hpp
#define Player_hpp

#include <stdio.h>
template <typename Datatype>
class Player
{
private:
     Datatype token;
public:
    Player(){};
    Player(Datatype _token);
    Datatype get_token() const;
};
#endif /* Player_hpp */
