#include "king.h"
#include "board.h"

King::King(Color c, int r, int cl): Piece(c, r, cl, c == WHITE ? 'K' : 'k') {}

char King::getSymbol() const { return symbol; }
string King::getPieceName() const { return "King"; }

bool King::isValidMove(Board& b, int toRow, int toCol) {
    int rowDiff = abs(toRow - row);
    int colDiff = abs(toCol - col);

    if (rowDiff > 1 || colDiff > 1) return false;
    if (rowDiff == 0 && colDiff == 0) return false;

    Piece* target = b.getPiece(toRow, toCol);
    if (target != nullptr && target->getColor() == color) return false;

    return true;
}