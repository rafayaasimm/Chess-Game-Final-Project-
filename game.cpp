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
 


//  GAME Implementations

void Game::switchTurn()
{
    currentTurn = 1 - currentTurn;
}
 
bool Game::parseInput(string in, int& r, int& c) {
    if (in.length() != 2) 
    {
        return false;
    }
    c = in[0] - 'a';        
    r = 8 - (in[1] - '0'); 
    return (r >= 0 && r < 8 && c >= 0 && c < 8);
}
 
Game::Game(string p1Name, string p2Name)
    : players{{p1Name, WHITE}, {p2Name, BLACK}}, currentTurn(0)
{
    board.setupBoard();
}


