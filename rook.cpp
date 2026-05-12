#include "rook.h"
#include "board.h"

// Constructor - Rook object banata hai
// WHITE ho to symbol 'R' aur BLACK ho to symbol 'r' set hota hai
Rook::Rook(Color c, int r, int cl) : Piece(c, r, cl, c == WHITE ? 'R' : 'r') {}

// Rook ka symbol return karta hai
char Rook::getSymbol() const { return symbol; }

// Rook ka naam return karta hai
string Rook::getPieceName() const { return "Rook"; }

// Check karta hai ke Rook ka move valid hai ya nahi
bool Rook::isValidMove(Board& b, int toRow, int toCol) {

    // Rook sirf seedhi line mein chalta hai
    // agar dono row aur column dono change ho rahe hain to diagonal hai - invalid
    if (row != toRow && col != toCol) return false;

    // Same square par nahi ja sakta - koi movement hi nahi hui
    if (row == toRow && col == toCol) return false;

    // Direction calculate karo - Rook kis taraf ja raha hai
    int rowStep = 0, colStep = 0;

    // Upar ya neeche
    if (toRow > row) rowStep = 1;
    else if (toRow < row) rowStep = -1;

    // Left ya right
    if (toCol > col) colStep = 1;
    else if (toCol < col) colStep = -1;

    // Source ke agle square se destination tak har beech wala square check karo
    int r = row + rowStep, c = col + colStep;

    while (r != toRow || c != toCol) {
        // Agar beech mein koi bhi piece hai to Rook wahan se nahi guzar sakta
        if (b.getPiece(r, c) != nullptr) return false;

        // Agla square check karo same direction mein
        r += rowStep;
        c += colStep;
    }

    // Destination square par jo piece hai usse check karo
    Piece* target = b.getPiece(toRow, toCol);

    // Apni hi color ki piece par nahi ja sakta
    if (target != nullptr && target->getColor() == color) return false;

    // Saari conditions pass - valid move hai
    return true;
}