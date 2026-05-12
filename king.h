#pragma once
#include "piece.h"

// King piece ki class - yeh Piece class se inherit karti hai
class King : public Piece {
public:
    // Constructor - King banata hai, color aur position deta hai
    King(Color c, int r, int cl);

    // King ka symbol return karta hai - WHITE ke liye 'K', BLACK ke liye 'k'
    char getSymbol() const override;

    // Piece ka naam return karta hai - "King"
    string getPieceName() const override;

    // Check karta hai ke King ka move valid hai ya nahi
    // King sirf ek square kisi bhi direction mein move kar sakta hai
    // aur apne hi color ki piece par nahi ja sakta
    bool isValidMove(Board& b, int toRow, int toCol) override;
};