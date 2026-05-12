#pragma once
#include "piece.h"

// Bishop piece ki class - yeh Piece class se inherit karti hai
class Bishop : public Piece
{
public:
    // Constructor - Bishop banata hai, color aur position deta hai
    Bishop(Color c, int r, int cl);

    // Bishop ka symbol return karta hai - WHITE ke liye 'B', BLACK ke liye 'b'
    char getSymbol() const override;

    // Piece ka naam return karta hai - "Bishop"
    string getPieceName() const override;

    // Check karta hai ke Bishop ka move valid hai ya nahi
    // Bishop sirf diagonal move kar sakta hai
    bool isValidMove(Board& b, int toRow, int toCol) override;
};