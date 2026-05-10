#pragma once
#include "piece.h"

// Knight piece moves in L shape
class Knight : public Piece {
public:
    Knight(Color c, int r, int cl);
    char getSymbol() const override;
    string getPieceName() const override;
    bool isValidMove(Board& b, int toRow, int toCol) override;
};