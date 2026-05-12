#pragma once
#include "piece.h"

// Knight piece ki class - yeh Piece class se inherit karti hai
class Knight : public Piece {
public:
    // Constructor - Knight banata hai, color aur position deta hai
    Knight(Color c, int r, int cl);

    // Knight ka symbol return karta hai - WHITE ke liye 'N', BLACK ke liye 'n'
    // N isliye use karte hain kyunki K already King ke liye reserved hai
    char getSymbol() const override;

    // Piece ka naam return karta hai - "Knight"
    string getPieceName() const override;

    // Check karta hai ke Knight ka move valid hai ya nahi
    // Knight L shape mein move karta hai - 2 squares ek direction
    // aur 1 square doosri direction mein
    // Knight akela aisa piece hai jo doosre pieces ke upar se jump kar sakta hai
    bool isValidMove(Board& b, int toRow, int toCol) override;
};