#pragma once
#include <iostream>
#include <string>
using namespace std;

// colour batane ke liye  WHITE ya BLACK
enum Color { WHITE, BLACK };

// Board aage aayega - abhi sirf bata rahe hain ke yeh hai
class Board;

// Yeh base class hai saare pieces is se banenge
class Piece {
protected:
    Color color;   // piece ka rang
    int row, col;  // piece ki jagah board par
    char symbol;   // piece ka symbol jaise P ya R

public:
    // constructor 
    Piece(Color c, int r, int cl, char sym) {
        color = c;
        row = r;
        col = cl;
        symbol = sym;
    }

    // destructor 
    virtual ~Piece() {}

    // yeh pure virtual hain - har piece ko khud specify krna hoga
    virtual bool isValidMove(Board& b, int toRow, int toCol) = 0;
    virtual char getSymbol() const = 0;
    virtual string getPieceName() const = 0;

    // getter functions info ke liye
    Color getColor() const 
    { 
        return color; 
    }
    int getRow() const 
    { 
        return row; 
    }
    int getCol() const 
    { 
        return col; 
    }

    // piece ki new location set
    void setPosition(int r, int c) {
        row = r;
        col = c;
    }
};