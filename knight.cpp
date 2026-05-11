#include "knight.h"
#include "board.h"

Knight::Knight(Color c, int r, int cl) : Piece(c, r, cl, c == WHITE ? 'N' : 'n') {}

char Knight::getSymbol() const { return symbol; }
string Knight::getPieceName() const { return "Knight"; }

bool Knight::isValidMove(Board& b, int toRow, int toCol) {
    int rowDiff = abs(toRow - row);
    int colDiff = abs(toCol - col);

    // Must form an L-shape
    if (!((rowDiff == 2 && colDiff == 1) || (rowDiff == 1 && colDiff == 2)))
        return false;

    // Cannot land on a friendly piece
    Piece* target = b.getPiece(toRow, toCol);
    if (target != nullptr && target->getColor() == color) return false;
    return true;
}