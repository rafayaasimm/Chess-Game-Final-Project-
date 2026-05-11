#include "pawn.h"
#include "board.h"

Pawn::Pawn(Color c, int r, int cl) : Piece(c, r, cl, c == WHITE ? 'P' : 'p') {
    hasMoved = false;
}

char Pawn::getSymbol() const { return symbol; }
string Pawn::getPieceName() const { return "Pawn"; }

void Pawn::setMoved() { hasMoved = true; }

bool Pawn::isValidMove(Board& b, int toRow, int toCol) {
    int direction = (color == WHITE) ? -1 : 1; // WHITE moves up (-1), BLACK moves down (+1)
    int rowDiff = toRow - row;
    int colDiff = toCol - col;

    // --- Forward one step: destination must be empty ---
    if (colDiff == 0 && rowDiff == direction) {
        return b.getPiece(toRow, toCol) == nullptr;
    }

    // --- Forward two steps: only from starting row, both squares must be empty ---
    if (colDiff == 0 && rowDiff == 2 * direction && !hasMoved) {
        int midRow = row + direction;
        return b.getPiece(midRow, col) == nullptr &&
            b.getPiece(toRow, toCol) == nullptr;
    }

    // --- Diagonal capture: must be an enemy piece on the target square ---
    if (abs(colDiff) == 1 && rowDiff == direction) {
        Piece* target = b.getPiece(toRow, toCol);
        return target != nullptr && target->getColor() != color;
    }

    return false;
}