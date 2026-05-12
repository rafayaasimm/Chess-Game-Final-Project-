#pragma once
#include <iostream>
#include <string>
#include "piece.h"    
#include "board.h"   
using namespace std;

// Player class - ek player ki information store karta hai
class Player
{
private:
    // Player ka naam jaise "Rafay" ya "Moeed"
    string name;

    // Player ka color - WHITE ya BLACK
    Color color;

public:
    // Constructor - player ka naam aur color set karta hai
    Player(string n, Color c);

    // Player ka naam return karta hai
    string getName() const;

    // Player ka color return karta hai WHITE ya BLACK
    Color getColor() const;
};


// Game class - poori game ki logic yahan hoti hai
class Game
{
private:
    // Chess board jis par game kheli jati hai
    Board board;

    // Do players ka array - index 0 WHITE hai, index 1 BLACK hai
    Player players[2];

    // Batata hai abhi kiski baari hai - 0 matlab WHITE, 1 matlab BLACK
    int currentTurn;

    // Turn switch karta hai WHITE se BLACK ya BLACK se WHITE
    void switchTurn();

    // User ki input string ko row aur column mein convert karta hai
    // jaise "e2" ko row=6, col=4 mein badalta hai
    bool parseInput(string in, int& r, int& c);

public:
    // Constructor - dono players ke naam se game setup karta hai
    Game(string p1Name, string p2Name);

    // Game loop shuru karta hai - players baari baari move karte hain
    void start();

    // Check karta hai ke diye gaye color ka koi bhi valid move bacha hai ya nahi
    // agar koi move nahi bacha to checkmate hai
    bool isCheckmate(Color color);

    // Board ka reference return karta hai - GUI ke liye use hota hai
    Board& getBoard() { return board; }
};