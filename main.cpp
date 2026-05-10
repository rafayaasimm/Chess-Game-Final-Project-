#include <iostream>
#include "piece.h"
#include "pawn.h"
#include "rook.h"
#include "knight.h"
using namespace std;

int main() {

    //three pieces made for testing
    Pawn   p(WHITE, 6, 4); // WHITE Pawn row 6 column 4 par
    Rook   r(WHITE, 7, 0); // WHITE Rook row 7 column 0 par
    Knight n(BLACK, 0, 1); // BLACK Knight row 0 column 1 par

   //three pieces added to array
   // Piece* use kiya hai yeh polymorphism hai
    Piece* pieces[3] = { &p, &r, &n };

    //har piece ki information print test
    for (int i = 0; i < 3; i++) {
        cout << pieces[i]->getPieceName()
             << " -- Symbol: " << pieces[i]->getSymbol()
             << " -- Color: "
             << (pieces[i]->getColor() == WHITE ? "WHITE" : "BLACK")
             << endl;
    }

    return 0;
}