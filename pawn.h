#pragma once
#include "piece.h"

// Pawn piece ki class - yeh Piece class se inherit karti hai
// Pawn chess ka sabse chota aur zyada rules wala piece hai
class Pawn : public Piece {
private:
    // Track karta hai ke pawn apni starting position se hila hai ya nahi
    // pehli baar 2 squares aage ja sakta hai sirf tab jab hasMoved false ho
    bool hasMoved;

public:
    // Constructor - Pawn banata hai, color aur position deta hai
    // hasMoved false se start hota hai
    Pawn(Color c, int r, int cl);

    // Pawn ka symbol return karta hai - WHITE ke liye 'P', BLACK ke liye 'p'
    char getSymbol() const override;

    // Piece ka naam return karta hai - "Pawn"
    string getPieceName() const override;

    // Check karta hai ke Pawn ka move valid hai ya nahi
    // WHITE pawn upar jata hai, BLACK pawn neeche jata hai
    // seedha 1 square move kar sakta hai agar square empty ho
    // pehli baar 2 squares bhi ja sakta hai agar hasMoved false ho
    // diagonal sirf tab ja sakta hai jab enemy piece ho wahan
    bool isValidMove(Board& b, int toRow, int toCol) override;

    // Jab pawn pehli baar move kare to hasMoved ko true karta hai
    // taake agle baar 2 square wala option band ho jaye
    void setMoved();
};