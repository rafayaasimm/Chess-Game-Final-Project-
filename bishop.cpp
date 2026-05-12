#include "bishop.h"
#include "board.h"

// Constructor - Bishop object banata hai
// WHITE ho to symbol 'B' aur BLACK ho to symbol 'b' set hota hai
Bishop::Bishop(Color c, int r, int cl) : Piece(c, r, cl, c == WHITE ? 'B' : 'b') {}

// Bishop ka symbol return karta hai
char Bishop::getSymbol() const { return symbol; }

// Bishop ka naam return karta hai
string Bishop::getPieceName() const { return "Bishop"; }

// Check karta hai ke Bishop ka move valid hai ya nahi
bool Bishop::isValidMove(Board& b, int toRow, int toCol)
{
    // Row aur column ka farq calculate karo
    int rowDiff = abs(toRow - row);
    int colDiff = abs(toCol - col);

    // Diagonal move tab hota hai jab row aur column ka farq equal ho
    // agar equal nahi ya same square hai to invalid move hai
    if (rowDiff != colDiff || rowDiff == 0) return false;

    // Decide karo Bishop kis direction mein ja raha hai
    // upar ya neeche - aur left ya right
    int rowStep = (toRow > row) ? 1 : -1;
    int colStep = (toCol > col) ? 1 : -1;

    // Starting square ke agle square se check shuru karo
    int r = row + rowStep, c = col + colStep;

    // Destination tak har square check karo
    while (r != toRow || c != toCol)
    {
        // Agar beech mein koi piece hai to Bishop wahan se nahi guzar sakta
        if (b.getPiece(r, c) != nullptr) return false;

        // Agla diagonal square check karo
        r += rowStep; c += colStep;
    }

    // Destination square par check karo
    Piece* target = b.getPiece(toRow, toCol);

    // Agar destination par apna hi piece hai to invalid move hai
    if (target != nullptr && target->getColor() == color) return false;

    // Saari conditions pass ho gayi - valid move hai
    return true;
}