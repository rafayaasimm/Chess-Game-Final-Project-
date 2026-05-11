#include "game.h"

Player::Player(string n, Color c)
    : name(n), color(c) {}
 
string Player::getName()  const
 {
     return name;
     }
Color  Player::getColor() const 
{
     return color; 
    }
 