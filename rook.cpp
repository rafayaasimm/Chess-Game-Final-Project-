#include "rook.h"
#include "board.h"

// Rook banana - WHITE ho to R aur BLACK ho to r
Rook::Rook(Color c, int r, int cl): Piece(c, r, cl, c == WHITE ? 'R' : 'r') {
}

// Rook ka symbol return karna
char Rook::getSymbol() const {
    return symbol;
}

// Rook ka name return karna
string Rook::getPieceName() const {
    return "Rook";
}

// check if move is valid
bool Rook::isValidMove(Board& b, int toRow, int toCol) {

    // Rook sirf seedhi line mein chalta hai
    // ya toh row same rehti hai ya column same rehta hai
    if (row == toRow || col == toCol) {
        return true; // sahi chaal hai
    }

    // in case not valid
    return false;
}