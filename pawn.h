#pragma once
#include "piece.h"

// Pawn piece is the smallest piece
class Pawn : public Piece {
private:
    bool hasMoved; // Pawn pehle chala hai ya nai

public:
    Pawn(Color c, int r, int cl);
    char getSymbol() const override;
    string getPieceName() const override;
    bool isValidMove(Board& b, int toRow, int toCol) override;
};