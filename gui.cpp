#include "gui.h"
#include "queen.h"
#include "rook.h"
#include "bishop.h"
#include "knight.h"
#include <iostream>
#include <stdexcept>
using namespace std;

// Constructor - GUI banata hai, window, font aur sprites load karta hai
GUI::GUI(Board& b, string p1, string p2) : board(b),
window(sf::VideoMode(640, 700), "Chess Game"),
player1Name(p1), player2Name(p2)
{
    try {
        // Window theek se bani ya nahi check karo
        if (!window.isOpen())
            throw runtime_error("SFML window open nahi hui!");

        // Window ki maximum frame rate 60 per second set karo
        window.setFramerateLimit(60);

        // Font load karo player names dikhane ke liye
      // SFML built-in font use karo - koi file ki zaroorat nahi
        if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf"))
            if (!font.loadFromFile("C:/Windows/Fonts/calibri.ttf"))
                if (!font.loadFromFile("C:/Windows/Fonts/tahoma.ttf"))
                    if (!font.loadFromFile("C:/Windows/Fonts/verdana.ttf"))
                        if (!font.loadFromFile("C:/Windows/Fonts/cour.ttf"))
                            if (!font.loadFromFile("C:/Windows/Fonts/consola.ttf"))
                                if (!font.loadFromFile("C:/Windows/Fonts/times.ttf"))
                                    cout << "No font found\n";

        // Saari 12 piece images load karo
        loadSprites();

        // Legal moves array ko false se initialize karo
        clearLegalMoves();
    }
    catch (const runtime_error& e) {
        // Runtime error aaya - message print karo aur game bina font ke chalao
        cout << "GUI setup mein masla: " << e.what() << "\n";
        cout << "Game bina font ke chalay ga...\n";
        clearLegalMoves();
    }
    catch (...) {
        // Koi bhi unexpected error - game band karo
        cout << "GUI mein unknown error aa gaya!\n";
        window.close();
    }
}

// Saari 12 piece images disk se load karta hai aur sprites banata hai
void GUI::loadSprites() {
    // Har piece ka symbol - pehle 6 WHITE hain baaki 6 BLACK
    const char syms[12] = { 'K','Q','R','B','N','P',
                             'k','q','r','b','n','p' };

    // Har piece ki image ka full path
    const char* paths[12] = {
     "pieces/wK.png",
     "pieces/wQ.png",
     "pieces/wR.png",
     "pieces/wB.png",
     "pieces/wN.png",
     "pieces/wP.png",
     "pieces/bK.png",
     "pieces/bQ.png",
     "pieces/bR.png",
     "pieces/bB.png",
     "pieces/bN.png",
     "pieces/bP.png"
    };

    int loadedCount = 0;

    for (int i = 0; i < 12; i++) {
        try {
            // Symbol map mein store karo taake baad mein dhund sakein
            symMap[i] = syms[i];

            // Image file load karo - agar fail ho to exception throw karo
            if (!textures[i].loadFromFile(paths[i]))
                throw runtime_error(string("Image load nahi hui: ") + paths[i]);

            // Smooth scaling enable karo taake image resize hone par blur na lage
            textures[i].setSmooth(true);

            // Sprite ko texture se link karo
            sprites[i].setTexture(textures[i]);

            // Image ko exactly ek square mein fit karne ke liye scale karo
            float sx = (float)TILE / textures[i].getSize().x;
            float sy = (float)TILE / textures[i].getSize().y;
            sprites[i].setScale(sx, sy);

            loadedCount++;
        }
        catch (const runtime_error& e) {
            // Ek image nahi mili - warning print karo aur baaki load karte raho
            cout << "Warning: " << e.what() << "\n";
        }
    }

    // Agar koi bhi image load nahi hui to serious error hai
    if (loadedCount == 0)
        throw runtime_error("Koi bhi piece image load nahi hui! pieces folder check karo.");

    cout << loadedCount << "/12 piece images successfully load hui.\n";
}

// Diye gaye symbol ka index symMap mein dhundta hai
// -1 return karta hai agar symbol nahi mila
int GUI::getIndex(char sym) {
    for (int i = 0; i < 12; i++)
        if (symMap[i] == sym) return i;
    return -1;
}

// legalMoves array ko saaf karta hai - sab squares false kar deta hai
void GUI::clearLegalMoves() {
    for (int r = 0; r < 8; r++)
        for (int c = 0; c < 8; c++)
            legalMoves[r][c] = false;
}

// Diye gaye square par jo piece hai uske saare valid moves calculate karta hai
// green dots dikhane ke liye use hota hai
void GUI::computeLegalMoves(int row, int col) {
    try {
        // Row aur column valid range mein hone chahiye
        if (row < 0 || row > 7 || col < 0 || col > 7)
            throw out_of_range("computeLegalMoves: row/col board se bahar hai!");

        clearLegalMoves();
        Piece* p = board.getPiece(row, col);

        // Agar square empty hai to kuch karne ki zaroorat nahi
        if (p == nullptr) return;

        // Board ke har square ko check karo
        for (int r = 0; r < 8; r++) {
            for (int c = 0; c < 8; c++) {
                // Agar piece ki movement rules ke hisaab se invalid hai to skip
                if (!p->isValidMove(board, r, c)) continue;

                // Move temporarily simulate karo
                Piece* captured = board.getPiece(r, c);
                board.setPiece(r, c, p);
                board.setPiece(row, col, nullptr);
                p->setPosition(r, c);

                // Check karo ke is move ke baad apna king safe hai
                bool safe = !board.isInCheck(p->getColor());

                // Move wapas undo karo
                p->setPosition(row, col);
                board.setPiece(row, col, p);
                board.setPiece(r, c, captured);

                // Agar king safe hai to yeh valid move hai - true mark karo
                if (safe) legalMoves[r][c] = true;
            }
        }
    }
    catch (const out_of_range& e) {
        // Invalid position - legal moves clear karo aur continue karo
        cout << "Legal moves error: " << e.what() << "\n";
        clearLegalMoves();
    }
}

// 64 squares draw karta hai aur neeche info bar bhi
void GUI::drawBoard() {
    // Har square draw karo alternate colors ke saath
    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            sf::RectangleShape sq(sf::Vector2f(TILE, TILE));
            sq.setPosition(c * TILE, r * TILE);
            // Even squares light color, odd squares dark color
            sq.setFillColor((r + c) % 2 == 0 ? lightSq : darkSq);
            window.draw(sq);
        }
    }

    // Neeche dark info bar draw karo jisme player names aur turn dikhega
    sf::RectangleShape bar(sf::Vector2f(640, 60));
    bar.setPosition(0, 640);
    bar.setFillColor(sf::Color(30, 30, 30));
    window.draw(bar);

    // Beech mein chota dot jo current turn ka color dikhata hai
    sf::CircleShape dot(10);
    dot.setFillColor(currentTurn == WHITE
        ? sf::Color::White : sf::Color(20, 20, 20));
    dot.setOutlineColor(sf::Color::Yellow);
    dot.setOutlineThickness(2.f);
    dot.setOrigin(10, 10);
    dot.setPosition(320, 665);
    window.draw(dot);

    // Left side par WHITE player ka indicator square
    sf::RectangleShape wi(sf::Vector2f(16, 16));
    wi.setFillColor(sf::Color::White);
    // Agar WHITE ki turn hai to yellow outline warna grey
    wi.setOutlineColor(currentTurn == WHITE
        ? sf::Color::Yellow : sf::Color(80, 80, 80));
    wi.setOutlineThickness(2.f);
    wi.setPosition(10, 652);
    window.draw(wi);

    // Right side par BLACK player ka indicator square
    sf::RectangleShape bi(sf::Vector2f(16, 16));
    bi.setFillColor(sf::Color(30, 30, 30));
    // Agar BLACK ki turn hai to yellow outline warna grey
    bi.setOutlineColor(currentTurn == BLACK
        ? sf::Color::Yellow : sf::Color(80, 80, 80));
    bi.setOutlineThickness(2.f);
    bi.setPosition(614, 652);
    window.draw(bi);

    // Player names sirf tab draw karo jab font properly load hua ho
    if (font.getInfo().family != "") {
        try {
            // WHITE player ka naam left side par
            sf::Text t1;
            t1.setFont(font); t1.setCharacterSize(15);
            // Jis ki baari hai uska naam yellow, doosra grey
            t1.setFillColor(currentTurn == WHITE
                ? sf::Color::Yellow : sf::Color(180, 180, 180));
            // Agar WHITE ki turn hai to naam ke saath << arrow bhi dikhao
            t1.setString(player1Name + (currentTurn == WHITE ? " <<" : ""));
            t1.setPosition(32, 650);
            window.draw(t1);

            // BLACK player ka naam right side par
            sf::Text t2;
            t2.setFont(font); t2.setCharacterSize(15);
            t2.setFillColor(currentTurn == BLACK
                ? sf::Color::Yellow : sf::Color(180, 180, 180));
            // Agar BLACK ki turn hai to >> arrow pehle dikhao
            t2.setString((currentTurn == BLACK ? ">> " : "") + player2Name);
            sf::FloatRect b2 = t2.getLocalBounds();
            // Text ko right side se align karo
            t2.setPosition(608 - b2.width, 650);
            window.draw(t2);
        }
        catch (...) {
            // Text draw karne mein koi masla - skip karo game chalti rahegi
            cout << "Player names draw karne mein masla aaya.\n";
        }
    }
}

// Selected piece par green overlay aur legal squares par dots draw karta hai
void GUI::drawHighlightsAndDots() {
    // Agar koi piece select nahi to kuch draw karne ki zaroorat nahi
    if (!pieceSelected) return;

    // Selected square par green overlay draw karo
    sf::RectangleShape hl(sf::Vector2f(TILE, TILE));
    hl.setPosition(selCol * TILE, selRow * TILE);
    hl.setFillColor(hlGreen);
    window.draw(hl);

    // Har legal move square par indicator draw karo
    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            if (!legalMoves[r][c]) continue;

            Piece* target = board.getPiece(r, c);
            if (target == nullptr) {
                // Empty square par chota green dot draw karo
                sf::CircleShape dot(12);
                dot.setFillColor(sf::Color(20, 85, 30, 160));
                dot.setOrigin(12, 12);
                dot.setPosition(c * TILE + TILE / 2.f, r * TILE + TILE / 2.f);
                window.draw(dot);
            }
            else {
                // Enemy piece wale square par green ring draw karo
                sf::RectangleShape ring(sf::Vector2f(TILE, TILE));
                ring.setPosition(c * TILE, r * TILE);
                ring.setFillColor(sf::Color(20, 85, 30, 60));
                ring.setOutlineColor(sf::Color(20, 85, 30, 200));
                ring.setOutlineThickness(5.f);
                window.draw(ring);
            }
        }
    }
}

// Saari pieces apni current position par draw karta hai
void GUI::drawPieces() {
    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            try {
                Piece* p = board.getPiece(r, c);

                // Empty square skip karo
                if (p == nullptr) continue;

                // Piece ke symbol se uska sprite index nikalo
                int idx = getIndex(p->getSymbol());

                // Agar index nahi mila to skip karo
                if (idx == -1) continue;

                // Sprite ko sahi position par draw karo
                sprites[idx].setPosition(c * TILE, r * TILE);
                window.draw(sprites[idx]);
            }
            catch (...) {
                // Kisi ek piece ko draw karne mein masla - skip karo baaki draw hoti rahein
                cout << "Piece draw error at row=" << r << " col=" << c << "\n";
            }
        }
    }
}

// Game khatam hone par bada overlay screen par dikhata hai
// checkmate ya stalemate dono ke liye use hota hai
void GUI::drawEndScreen(string line1, string line2, sf::Color col) {
    try {
        // Poori screen par dark overlay draw karo
        sf::RectangleShape overlay(sf::Vector2f(640, 700));
        overlay.setFillColor(sf::Color(0, 0, 0, 190));
        window.draw(overlay);

        // Colored banner draw karo - checkmate ke liye gold, stalemate ke liye blue
        sf::RectangleShape banner(sf::Vector2f(500, 80));
        banner.setFillColor(col);
        banner.setOrigin(250, 40);
        banner.setPosition(320, 280);
        window.draw(banner);

        // Doosra banner winner ka naam dikhane ke liye
        sf::RectangleShape banner2(sf::Vector2f(400, 50));
        banner2.setFillColor(sf::Color(50, 50, 50));
        banner2.setOrigin(200, 25);
        banner2.setPosition(320, 370);
        window.draw(banner2);

        // Sirf tab text draw karo jab font load hua ho
        if (font.getInfo().family != "") {
            // Bada message jaise "CHECKMATE!"
            sf::Text msg;
            msg.setFont(font); msg.setCharacterSize(42);
            msg.setFillColor(sf::Color::White);
            msg.setString(line1);
            sf::FloatRect mb = msg.getLocalBounds();
            // Text ko banner ke beech mein center karo
            msg.setOrigin(mb.left + mb.width / 2.f, mb.top + mb.height / 2.f);
            msg.setPosition(320, 280);
            window.draw(msg);

            // Chota message jaise "rafay WINS!"
            sf::Text sub;
            sub.setFont(font); sub.setCharacterSize(24);
            sub.setFillColor(sf::Color::Yellow);
            sub.setString(line2);
            sf::FloatRect sb = sub.getLocalBounds();
            sub.setOrigin(sb.left + sb.width / 2.f, sb.top + sb.height / 2.f);
            sub.setPosition(320, 370);
            window.draw(sub);
        }

        // End screen display karo
        window.display();

        // 4 second ruko taake player result dekh sake
        sf::sleep(sf::seconds(4));
        window.close();
    }
    catch (...) {
        // End screen draw mein masla - game band karo
        cout << "End screen draw nahi ho saka. Window band ho rahi hai.\n";
        window.close();
    }
}

// Promotion popup draw karta hai jab pawn last row par pahunche
void GUI::drawPromotionPanel() {
    // Agar promotion pending nahi to kuch mat karo
    if (!promoWaiting) return;

    // Poori screen par semi-transparent overlay
    sf::RectangleShape overlay(sf::Vector2f(640, 700));
    overlay.setFillColor(sf::Color(0, 0, 0, 140));
    window.draw(overlay);

    // Panel ka size aur position calculate karo - screen ke beech mein
    float panelW = 4 * TILE + 20.f;
    float panelH = TILE + 40.f;
    float panelX = (640 - panelW) / 2.f;
    float panelY = (640 - panelH) / 2.f;

    // Blue panel background draw karo
    sf::RectangleShape panel(sf::Vector2f(panelW, panelH));
    panel.setPosition(panelX, panelY);
    panel.setFillColor(sf::Color(44, 82, 140));
    panel.setOutlineColor(sf::Color::White);
    panel.setOutlineThickness(2.f);
    window.draw(panel);

    // WHITE ke liye uppercase symbols, BLACK ke liye lowercase
    char whiteChoices[4] = { 'Q','R','B','N' };
    char blackChoices[4] = { 'q','r','b','n' };
    char* choices = (promoColor == WHITE) ? whiteChoices : blackChoices;

    // Charo options draw karo - Q R B N
    for (int i = 0; i < 4; i++) {
        float x = panelX + 10 + i * TILE;
        float y = panelY + 10.f;

        // Har option ka background box
        sf::RectangleShape optBg(sf::Vector2f(TILE, TILE));
        optBg.setPosition(x, y);
        optBg.setFillColor(sf::Color(60, 100, 170));
        optBg.setOutlineColor(sf::Color::White);
        optBg.setOutlineThickness(1.f);
        window.draw(optBg);

        // Piece ki image draw karo
        int idx = getIndex(choices[i]);
        if (idx != -1) {
            sprites[idx].setPosition(x, y);
            window.draw(sprites[idx]);
        }
    }
}

// Promotion popup par click handle karta hai
// Player jis piece par click kare pawn usmein convert ho jata hai
void GUI::handlePromoClick(int mx, int my) {
    float panelW = 4 * TILE + 20.f;
    float panelX = (640 - panelW) / 2.f;
    float panelY = (640 - (TILE + 40.f)) / 2.f;

    char whiteChoices[4] = { 'Q','R','B','N' };
    char blackChoices[4] = { 'q','r','b','n' };
    char* choices = (promoColor == WHITE) ? whiteChoices : blackChoices;

    // Check karo player ne konse option par click kiya
    for (int i = 0; i < 4; i++) {
        float x = panelX + 10 + i * TILE;
        float y = panelY + 10.f;

        // Agar click is option ke andar hai
        if (mx >= x && mx <= x + TILE && my >= y && my <= y + TILE) {
            try {
                // Purana pawn delete karo
                delete board.getPiece(promoRow, promoCol);

                // Chosen piece ka uppercase symbol nikalo
                char sym = toupper(choices[i]);
                Piece* newPiece = nullptr;

                // New piece banao jo player ne choose ki
                if (sym == 'Q') newPiece = new Queen(promoColor, promoRow, promoCol);
                else if (sym == 'R') newPiece = new Rook(promoColor, promoRow, promoCol);
                else if (sym == 'B') newPiece = new Bishop(promoColor, promoRow, promoCol);
                else if (sym == 'N') newPiece = new Knight(promoColor, promoRow, promoCol);

                // Agar koi piece nahi bani to error throw karo
                if (newPiece == nullptr)
                    throw runtime_error("Promotion piece nahi ban saki!");

                // New piece board par rakh do
                board.setPiece(promoRow, promoCol, newPiece);

                // Promotion complete - popup band karo
                promoWaiting = false;
            }
            catch (const runtime_error& e) {
                // Promotion mein masla - message print karo
                cout << "Promotion error: " << e.what() << "\n";
                promoWaiting = false;
            }
            catch (...) {
                // Memory alloc ya koi aur masla
                cout << "Promotion mein unknown error!\n";
                promoWaiting = false;
            }
            return;
        }
    }
}

// Har move ke baad check karta hai ke game khatam hua ya nahi
void GUI::checkEndConditions(Color opponent, Game& game, string moverName) {
    try {
        if (board.isInCheck(opponent)) {
            if (game.isCheckmate(opponent)) {
                // Check bhi hai aur koi move bhi nahi - checkmate
                drawEndScreen("CHECKMATE!", moverName + " WINS!",
                    sf::Color(180, 140, 0));
            }
            else {
                // Sirf check hai - red border draw karo warning ke liye
                sf::RectangleShape border(sf::Vector2f(636, 636));
                border.setPosition(2, 2);
                border.setFillColor(sf::Color::Transparent);
                border.setOutlineColor(sf::Color::Red);
                border.setOutlineThickness(6.f);
                window.draw(border);
            }
        }
        else if (game.isCheckmate(opponent)) {
            // Check nahi lekin koi move bhi nahi - stalemate yaani draw
            drawEndScreen("STALEMATE!", "The game is a draw.",
                sf::Color(0, 120, 180));
        }
    }
    catch (...) {
        // Check/checkmate calculation mein masla - game continue karo
        cout << "End condition check mein error aaya.\n";
    }
}

// Mouse click handle karta hai - piece select karna ya move karna
void GUI::handleClick(int mx, int my, Game& game) {
    try {
        // Agar promotion popup open hai to pehle woh handle karo
        if (promoWaiting) { handlePromoClick(mx, my); return; }

        // Board ke neeche info bar par click ignore karo
        if (my > 640) return;

        // Mouse pixel position ko board row aur column mein convert karo
        int col = mx / TILE;
        int row = my / TILE;

        // Board ke bahar click ignore karo
        if (row < 0 || row > 7 || col < 0 || col > 7) return;

        if (!pieceSelected) {
            // Pehla click - piece select karo
            Piece* p = board.getPiece(row, col);

            // Sirf apni piece select ho sakti hai
            if (p != nullptr && p->getColor() == currentTurn) {
                selRow = row; selCol = col;
                pieceSelected = true;
                // Is piece ke liye saare valid moves calculate karo
                computeLegalMoves(row, col);
            }
        }
        else {
            // Agar same square par dobara click kiya to deselect karo
            if (row == selRow && col == selCol) {
                pieceSelected = false;
                selRow = selCol = -1;
                clearLegalMoves();
                return;
            }

            Color moverColor = currentTurn;
            // Current player ka naam winner message ke liye
            string moverName = (moverColor == WHITE) ? player1Name : player2Name;
            Color opponent = (moverColor == WHITE) ? BLACK : WHITE;

            // Move karne ki koshish karo
            if (board.movePiece(selRow, selCol, row, col)) {
                Piece* moved = board.getPiece(row, col);

                // Check karo ke pawn last row par pahuncha ya nahi
                if (moved && moved->getPieceName() == "Pawn") {
                    if ((moved->getColor() == WHITE && row == 0) ||
                        (moved->getColor() == BLACK && row == 7)) {
                        // Promotion pending - popup dikhao
                        promoWaiting = true;
                        promoRow = row; promoCol = col;
                        promoColor = moved->getColor();
                    }
                }

                // Turn switch karo
                currentTurn = opponent;

                // Promotion pending ho to end conditions baad mein check karo
                if (!promoWaiting)
                    checkEndConditions(opponent, game, moverName);
            }
            else {
                // Invalid move - shayad doosri apni piece select karna chahte hain
                Piece* p = board.getPiece(row, col);
                if (p != nullptr && p->getColor() == currentTurn) {
                    // Nayi piece select karo
                    selRow = row; selCol = col;
                    computeLegalMoves(row, col);
                    return;
                }
            }

            // Selection reset karo next move ke liye
            pieceSelected = false;
            selRow = selCol = -1;
            clearLegalMoves();
        }
    }
    catch (const out_of_range& e) {
        // Board se bahar access - selection reset karo
        cout << "Click handling error: " << e.what() << "\n";
        pieceSelected = false;
        selRow = selCol = -1;
        clearLegalMoves();
    }
    catch (...) {
        // Koi aur masla - safely reset karo
        cout << "Click mein unknown error aaya.\n";
        pieceSelected = false;
        selRow = selCol = -1;
        clearLegalMoves();
    }
}

// Main game loop - events handle karta hai aur har frame board draw karta hai
void GUI::run(Game& game) {
    while (window.isOpen()) {
        try {
            // SFML events check karo
            sf::Event event;
            while (window.pollEvent(event)) {
                // X button dabane par window band karo
                if (event.type == sf::Event::Closed)
                    window.close();

                // Mouse click hone par handleClick call karo
                if (event.type == sf::Event::MouseButtonPressed)
                    if (event.mouseButton.button == sf::Mouse::Left)
                        handleClick(event.mouseButton.x,
                            event.mouseButton.y, game);
            }

            // Screen saaf karo dark background se
            window.clear(sf::Color(20, 20, 20));

            // Sab kuch draw karo sahi order mein
            drawBoard();             // Pehle squares draw karo
            drawHighlightsAndDots(); // Phir green dots
            drawPieces();            // Phir pieces images
            drawPromotionPanel();    // Sabse upar promotion popup agar ho

            // Sab kuch screen par display karo
            window.display();
        }
        catch (const runtime_error& e) {
            // Game loop mein runtime error - print karo aur band karo
            cout << "Game loop error: " << e.what() << "\n";
            window.close();
        }
        catch (...) {
            // Koi bhi unexpected error - safely band karo
            cout << "Game loop mein unknown error! Window band ho rahi hai.\n";
            window.close();
        }
    }
}