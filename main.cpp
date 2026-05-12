#include "game.h"
#include "gui.h"
#include <iostream>
using namespace std;

int main() {

   

    //// Rafay's test - polymorphism check karna tha
    //// Alag alag pieces banaye aur base class pointer se access kiya
    //Pawn   p(WHITE, 6, 4);
    //Rook   r(WHITE, 7, 0);
    //Knight n(BLACK, 0, 1);
    //Piece* pieces[3] = { &p, &r, &n };
    //for (int i = 0; i < 3; i++) 
    //{
    //    cout << pieces[i]->getPieceName()
    //         << " -- Symbol: " << pieces[i]->getSymbol()
    //         << " -- Color: "
    //         << (pieces[i]->getColor() == WHITE ? "WHITE" : "BLACK")
    //         << endl;
    //}

    //// Rameen's test - Board setup aur display check karna tha
    //cout << "\n--- Board Setup Test ---" << endl;
    //Board b;
    //b.setupBoard();
    //b.displayBoard();
    //cout << "Board setup complete. All 32 pieces placed." << endl;

    //// Faryal's test - Console wali game flow check karna tha
    //string p1, p2;
    //cout << "Enter Player 1 name (WHITE): ";
    //cin >> p1;
    //cout << "Enter Player 2 name (BLACK): ";
    //cin >> p2;
    //Game game(p1, p2);
    //game.start();
    //return 0;


    // Dono players ke naam console se lo
    string p1, p2;
    cout << "Enter Player 1 name (WHITE): ";  cin >> p1;
    cout << "Enter Player 2 name (BLACK): ";  cin >> p2;

    // Game object banao - board setup hoga aur players set honge
    Game game(p1, p2);

    // GUI object banao - board ka reference aur player names do
    GUI gui(game.getBoard(), p1, p2);

    // GUI ki main loop shuru karo - jab tak window band na ho game chalta rahega
    gui.run(game);

    return 0;
}