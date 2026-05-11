#pragma once
#include <iostream>
#include <string>
#include "piece.h"    
#include "board.h"   
using namespace std;
 
class Player 
{
private:
    string name;
    Color  color;
 
public:
    Player(string n, Color c);
 
    string getName()  const;
    Color  getColor() const;
};
 
 
class Game
{
private:
    Board  board;
    Player players[2];
    int    currentTurn;   // 0 = WHITE player, 1 = BLACK player
    void switchTurn();
    bool parseInput(string in, int& r, int& c);
    bool isCheckmate(Color color);
 
public:
    Game(string p1Name, string p2Name);
    void start();
};