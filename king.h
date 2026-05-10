#pragma once
#include "piece.h"

class King : public Piece {
public:
    King(Color c, int r, int cl);
    char getSymbol() const override;
    string getPieceName() const override;
    bool isValidMove(Board& b, int toRow, int toCol) override;
};