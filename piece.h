#pragma once
#include <iostream>
#include <string>
using namespace std;

// Color enum - piece ka rang batane ke liye WHITE ya BLACK
enum Color { WHITE, BLACK };

// Board class aage define hogi - abhi sirf forward declaration hai
// taake Piece class Board ko use kar sake bina include ke
class Board;

// Piece base class - saare chess pieces is class se inherit karte hain
// yeh abstract class hai kyunki isme pure virtual functions hain
class Piece {
protected:
    // Piece ka color - WHITE ya BLACK
    Color color;

    // Piece ki current position board par
    int row, col;

    // Piece ka character symbol jaise 'P' pawn ke liye, 'R' rook ke liye
    char symbol;

public:
    // Constructor - piece ka color, position aur symbol set karta hai
    Piece(Color c, int r, int cl, char sym) {
        color = c;
        row = r;
        col = cl;
        symbol = sym;
    }

    // Virtual destructor - taake derived class ka destructor bhi sahi se call ho
    // polymorphism ke saath memory leak rokta hai
    virtual ~Piece() {}

    // Pure virtual functions - har derived piece class ko
    // yeh apne hisaab se implement karne honge
    // is wajah se Piece class ka object seedha nahi ban sakta

    // Check karta hai ke piece ka move valid hai ya nahi
    virtual bool isValidMove(Board& b, int toRow, int toCol) = 0;

    // Piece ka character symbol return karta hai
    virtual char getSymbol() const = 0;

    // Piece ka naam return karta hai jaise "King", "Pawn" etc
    virtual string getPieceName() const = 0;

    // Piece ka color return karta hai WHITE ya BLACK
    Color getColor() const
    {
        return color;
    }

    // Piece ki current row return karta hai
    int getRow() const
    {
        return row;
    }

    // Piece ka current column return karta hai
    int getCol() const
    {
        return col;
    }

    // Move hone ke baad piece ki position update karta hai
    // Board class is function ko call karta hai jab piece move ho
    void setPosition(int r, int c) {
        row = r;
        col = c;
    }
};