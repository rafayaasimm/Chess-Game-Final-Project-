#pragma once
#include "piece.h"

// Rook piece moves in straight line
class Rook : public Piece {
public:
    Rook(Color c, int r, int cl);
    char getSymbol() const override;
    string getPieceName() const override;
    bool isValidMove(Board& b, int toRow, int toCol) override;
};