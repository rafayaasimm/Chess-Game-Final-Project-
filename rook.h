#pragma once
#include "piece.h"

// Rook piece ki class - yeh Piece class se inherit karti hai
class Rook : public Piece {
public:
    // Constructor - Rook banata hai, color aur position deta hai
    Rook(Color c, int r, int cl);

    // Rook ka symbol return karta hai - WHITE ke liye 'R', BLACK ke liye 'r'
    char getSymbol() const override;

    // Piece ka naam return karta hai - "Rook"
    string getPieceName() const override;

    // Check karta hai ke Rook ka move valid hai ya nahi
    // Rook sirf seedhi line mein move kar sakta hai
    // ya toh same row mein ya same column mein
    // beech mein koi bhi piece nahi honi chahiye
    // apne hi color ki piece par nahi ja sakta
    bool isValidMove(Board& b, int toRow, int toCol) override;
};