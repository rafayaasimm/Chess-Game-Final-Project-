#include "pawn.h"
#include "board.h"

// Constructor - Pawn object banata hai
// WHITE ho to symbol 'P' aur BLACK ho to symbol 'p' set hota hai
// hasMoved false se start hota hai - pawn abhi hila nahi hai
Pawn::Pawn(Color c, int r, int cl) : Piece(c, r, cl, c == WHITE ? 'P' : 'p') {
    hasMoved = false;
}

// Pawn ka symbol return karta hai
char Pawn::getSymbol() const { return symbol; }

// Pawn ka naam return karta hai
string Pawn::getPieceName() const { return "Pawn"; }

// Jab pawn pehli baar move kare to yeh call hota hai
// hasMoved true ho jata hai taake double step band ho jaye
void Pawn::setMoved() { hasMoved = true; }

// Check karta hai ke Pawn ka move valid hai ya nahi
bool Pawn::isValidMove(Board& b, int toRow, int toCol) {

    // WHITE upar jata hai isliye -1, BLACK neeche jata hai isliye +1
    int direction = (color == WHITE) ? -1 : 1;

    // Kitni rows aage ja raha hai - positive ya negative
    int rowDiff = toRow - row;

    // Kitne columns side mein ja raha hai
    int colDiff = toCol - col;

    // --- Case 1: Ek step seedha aage ---
    // Column same rehna chahiye aur sirf 1 step aage
    // Destination square bilkul empty honi chahiye
    if (colDiff == 0 && rowDiff == direction) {
        return b.getPiece(toRow, toCol) == nullptr;
    }

    // --- Case 2: Pehli baar 2 steps aage ---
    // Column same rehna chahiye aur hasMoved false hona chahiye
    // Beech wala square aur destination dono empty hone chahiye
    if (colDiff == 0 && rowDiff == 2 * direction && !hasMoved) {
        int midRow = row + direction;
        return b.getPiece(midRow, col) == nullptr &&
            b.getPiece(toRow, toCol) == nullptr;
    }

    // --- Case 3: Diagonal capture ---
    // Sirf 1 column side mein aur 1 step aage
    // Destination par enemy piece honi chahiye - empty square par capture nahi ho sakta
    if (abs(colDiff) == 1 && rowDiff == direction) {
        Piece* target = b.getPiece(toRow, toCol);
        return target != nullptr && target->getColor() != color;
    }

    // Koi bhi case match nahi hua - invalid move hai
    return false;
}