#include <iostream>
#include "piece.h"
#include "pawn.h"
#include "rook.h"
#include "knight.h"
#include "bishop.h"
#include "queen.h"
#include "king.h"
#include "board.h"
using namespace std;

int main() {

    // Rafay's test - polymorphism
    Pawn   p(WHITE, 6, 4);
    Rook   r(WHITE, 7, 0);
    Knight n(BLACK, 0, 1);

    Piece* pieces[3] = { &p, &r, &n };

    for (int i = 0; i < 3; i++) 
    {
        cout << pieces[i]->getPieceName()
             << " -- Symbol: " << pieces[i]->getSymbol()
             << " -- Color: "
             << (pieces[i]->getColor() == WHITE ? "WHITE" : "BLACK")
             << endl;
    }

    // Rameen's test - Board setup and display
    cout << "\n--- Board Setup Test ---" << endl;
    Board b;
    b.setupBoard();
    b.displayBoard();
    cout << "Board setup complete. All 32 pieces placed." << endl;

    
    return 0;
}