#include "queen.h"
#include "board.h"

// Constructor - Queen object banata hai
// WHITE ho to symbol 'Q' aur BLACK ho to symbol 'q' set hota hai
Queen::Queen(Color c, int r, int cl) : Piece(c, r, cl, c == WHITE ? 'Q' : 'q') {}

// Queen ka symbol return karta hai
char Queen::getSymbol() const { return symbol; }

// Queen ka naam return karta hai
string Queen::getPieceName() const { return "Queen"; }

// Check karta hai ke Queen ka move valid hai ya nahi
// Queen Rook aur Bishop dono ki tarah move kar sakti hai
bool Queen::isValidMove(Board& b, int toRow, int toCol) {

    // Row aur column ka farq calculate karo
    int rowDiff = abs(toRow - row);
    int colDiff = abs(toCol - col);

    // Seedhi line - ya to row same hai ya column same hai
    bool straight = (row == toRow || col == toCol);

    // Diagonal line - row aur column ka farq equal hona chahiye
    bool diagonal = (rowDiff == colDiff && rowDiff != 0);

    // Queen sirf seedhi ya diagonal line mein ja sakti hai
    // agar dono nahi to invalid move hai
    if (!straight && !diagonal) return false;

    // Direction calculate karo - Queen kis taraf ja rahi hai
    int rowStep = 0, colStep = 0;

    // Upar ya neeche
    if (toRow > row) rowStep = 1;
    else if (toRow < row) rowStep = -1;

    // Left ya right
    if (toCol > col) colStep = 1;
    else if (toCol < col) colStep = -1;

    // Source ke agle square se destination tak har square check karo
    int r = row + rowStep, c = col + colStep;

    while (r != toRow || c != toCol) {
        // Agar beech mein koi piece hai to Queen wahan se nahi guzar sakti
        if (b.getPiece(r, c) != nullptr) return false;

        // Agla square check karo same direction mein
        r += rowStep; c += colStep;
    }

    // Destination square par jo piece hai usse check karo
    Piece* target = b.getPiece(toRow, toCol);

    // Apni hi color ki piece par nahi ja sakti
    if (target != nullptr && target->getColor() == color) return false;

    // Saari conditions pass - valid move hai
    return true;
}