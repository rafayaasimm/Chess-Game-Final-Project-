#pragma once
#include "piece.h"

// Queen piece ki class - yeh Piece class se inherit karti hai
// Queen chess ka sabse powerful piece hai
class Queen : public Piece {
public:
    // Constructor - Queen banata hai, color aur position deta hai
    Queen(Color c, int r, int cl);

    // Queen ka symbol return karta hai - WHITE ke liye 'Q', BLACK ke liye 'q'
    char getSymbol() const override;

    // Piece ka naam return karta hai - "Queen"
    string getPieceName() const override;

    // Check karta hai ke Queen ka move valid hai ya nahi
    // Queen Rook aur Bishop dono ki tarah move kar sakti hai
    // yani seedhi line mein bhi aur diagonal mein bhi
    // jitne bhi squares chahiye ja sakti hai lekin beech mein
    // koi piece nahi hona chahiye
    bool isValidMove(Board& b, int toRow, int toCol) override;
};