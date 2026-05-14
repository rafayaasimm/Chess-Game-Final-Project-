#include "game.h"
#include <stdexcept>

// Player constructor - naam aur color set karta hai
Player::Player(string n, Color c) : name(n), color(c) {
    // Agar naam empty hai to exception throw karo
    if (n.empty())
        throw invalid_argument("Player ka naam empty nahi ho sakta!");
}

// Player ka naam return karta hai
string Player::getName() const
{
    return name;
}

// Player ka color return karta hai WHITE ya BLACK
Color Player::getColor() const
{
    return color;
}

// Turn switch karta hai - WHITE ke baad BLACK aur BLACK ke baad WHITE
// 1 - 0 = 1 aur 1 - 1 = 0 - is trick se index toggle hota hai
void Game::switchTurn()
{
    currentTurn = 1 - currentTurn;
}

// User ki input string ko board coordinates mein convert karta hai
// jaise "e2" -> column = 4, row = 6
bool Game::parseInput(string in, int& r, int& c) {
    try {
        // Input exactly 2 characters ka hona chahiye jaise "e2"
        if (in.length() != 2)
            return false;

        // Pehla character letter hona chahiye 'a' se 'h' tak
        if (in[0] < 'a' || in[0] > 'h')
            throw invalid_argument("Column letter 'a' se 'h' ke beech hona chahiye!");

        // Doosra character number hona chahiye '1' se '8' tak
        if (in[1] < '1' || in[1] > '8')
            throw invalid_argument("Row number '1' se '8' ke beech hona chahiye!");

        // Pehla character letter hai - 'a' se minus karke column nikalo
        // a=0, b=1, c=2 ... h=7
        c = in[0] - 'a';

        // Doosra character number hai - board upar se neeche hai
        // isliye 8 minus karte hain - "1" = row 7, "8" = row 0
        r = 8 - (in[1] - '0');

        // Check karo ke calculated position board ke andar hai
        return (r >= 0 && r < 8 && c >= 0 && c < 8);
    }
    catch (const invalid_argument& e) {
        // Invalid input format - message print karo aur false return karo
        cout << "Input error: " << e.what() << "\n";
        return false;
    }
}

// Game constructor - dono players banata hai aur board setup karta hai
Game::Game(string p1Name, string p2Name) : players{ {p1Name, WHITE}, {p2Name, BLACK} }, currentTurn(0)
{
    try {
        // Player names empty nahi hone chahiye
        if (p1Name.empty() || p2Name.empty())
            throw invalid_argument("Player names empty nahi ho sakte!");

        // Dono players ka naam alag hona chahiye
        if (p1Name == p2Name)
            throw invalid_argument("Dono players ka naam alag hona chahiye!");

        // Saare pieces apni starting position par rakh do
        board.setupBoard();
    }
    catch (const invalid_argument& e) {
        // Invalid player names - message print karo
        cout << "Game setup error: " << e.what() << "\n";

        // Default names assign karo taake game band na ho
        cout << "Default names use ho rahe hain: Player1 aur Player2\n";
    }
}

// Check karta hai ke diye gaye color ka koi bhi valid move bacha hai ya nahi
bool Game::isCheckmate(Color color) {
    try {
        // Diye gaye color ke har piece ko check karo
        for (int r = 0; r < 8; r++) {
            for (int c = 0; c < 8; c++) {
                Piece* p = board.getPiece(r, c);

                // Agar square empty hai ya doosre color ka piece hai to skip karo
                if (p == nullptr || p->getColor() != color) continue;

                // Is piece ke liye board par har possible destination check karo
                for (int tr = 0; tr < 8; tr++) {
                    for (int tc = 0; tc < 8; tc++) {
                        // Agar yeh move piece ki rules ke hisaab se invalid hai to skip
                        if (!p->isValidMove(board, tr, tc)) continue;

                        // Move temporarily karo - simulate karne ke liye
                        Piece* captured = board.getPiece(tr, tc);
                        board.setPiece(tr, tc, p);
                        board.setPiece(r, c, nullptr);
                        p->setPosition(tr, tc);

                        // Check karo ke is move ke baad king still check mein hai ya nahi
                        bool stillInCheck = board.isInCheck(color);

                        // Move wapas undo karo
                        p->setPosition(r, c);
                        board.setPiece(r, c, p);
                        board.setPiece(tr, tc, captured);

                        // Agar koi move mila jis se check khatam hota hai
                        // to checkmate nahi hai
                        if (!stillInCheck) return false;
                    }
                }
            }
        }

        // Koi bhi escape move nahi mila - checkmate hai
        return true;
    }
    catch (...) {
        // Checkmate check mein koi masla - safe side par false return karo
        cout << "Checkmate check mein error aaya.\n";
        return false;
    }
}

// Main game loop - players baari baari move karte hain
void Game::start() {
    try {
        // Pehle board display karo
        board.displayBoard();

        while (true) {
            // Abhi jis player ki baari hai usse lo
            Player& current = players[currentTurn];

            // Player se move maango
            cout << "\n" << current.getName()
                << " (" << (current.getColor() == WHITE ? "WHITE" : "BLACK")
                << ") -- Enter move (e.g. e2 e4): ";

            string from, to;

            // Input lene mein masla aa sakta hai - try catch se handle karo
            try {
                if (!(cin >> from >> to))
                    throw runtime_error("Input read karne mein masla aaya!");
            }
            catch (const runtime_error& e) {
                cout << "Input error: " << e.what() << "\n";
                cin.clear();
                cin.ignore(1000, '\n');
                continue;
            }

            int fR, fC, tR, tC;

            // Input format check karo - "e2" jaisi honi chahiye
            if (!parseInput(from, fR, fC) || !parseInput(to, tR, tC)) {
                cout << "Invalid input format. Use letter+number like e2." << endl;
                continue;
            }

            // Source square par piece check karo
            Piece* p = board.getPiece(fR, fC);
            if (p == nullptr) {
                cout << "No piece at " << from << "." << endl;
                continue;
            }

            // Check karo ke yeh piece current player ki hai ya nahi
            if (p->getColor() != current.getColor()) {
                cout << "That is not your piece!" << endl;
                continue;
            }

            // Move karne ki koshish karo
            if (!board.movePiece(fR, fC, tR, tC)) {
                cout << "Invalid move. Try again." << endl;
                continue;
            }

            // Move hone ke baad updated board dikhao
            board.displayBoard();

            // Opponent ka color nikalo
            Color opponent = (current.getColor() == WHITE) ? BLACK : WHITE;

            // Check karo ke opponent check mein hai ya nahi
            if (board.isInCheck(opponent)) {
                // Agar check mein hai aur koi escape move nahi to checkmate
                if (isCheckmate(opponent)) {
                    cout << "\nCHECKMATE! " << current.getName() << " WINS!" << endl;
                    break;
                }
                // Sirf check hai checkmate nahi
                cout << "CHECK!" << endl;
            }
            else if (isCheckmate(opponent)) {
                // Check nahi hai lekin koi move bhi nahi - stalemate yaani draw
                cout << "\nSTALEMATE! The game is a draw." << endl;
                break;
            }

            // Baari switch karo - doosre player ki turn
            switchTurn();
        }
    }
    catch (const out_of_range& e) {
        // Array ya board access out of range hua
        cout << "Game error (out of range): " << e.what() << "\n";
        cout << "Game band ho rahi hai.\n";
    }
    catch (const runtime_error& e) {
        // Koi runtime masla aaya
        cout << "Game runtime error: " << e.what() << "\n";
        cout << "Game band ho rahi hai.\n";
    }
    catch (...) {
        // Koi bhi unexpected error
        cout << "Game mein unknown error aa gaya! Game band ho rahi hai.\n";
    }
}