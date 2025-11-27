#include <iostream>
#include <array>
#include <limits>
#include <algorithm>

using Board = std::array<char, 9>; // positions 0..8

void printBoard(const Board &b) {
    auto cell = [&](int i) {
        return b[i] == ' ' ? char('1' + i) : b[i];
    };
    std::cout << "\n";
    std::cout << " " << cell(0) << " | " << cell(1) << " | " << cell(2) << "\n";
    std::cout << "---+---+---\n";
    std::cout << " " << cell(3) << " | " << cell(4) << " | " << cell(5) << "\n";
    std::cout << "---+---+---\n";
    std::cout << " " << cell(6) << " | " << cell(7) << " | " << cell(8) << "\n\n";
}

char checkWinner(const Board &b) {
    static const int lines[8][3] = {
        {0,1,2},{3,4,5},{6,7,8}, // rows
        {0,3,6},{1,4,7},{2,5,8}, // cols
        {0,4,8},{2,4,6}          // diagonals
    };
    for (auto &ln : lines) {
        char a = b[ln[0]];
        if (a != ' ' && a == b[ln[1]] && a == b[ln[2]]) return a;
    }
    return ' '; // no winner yet
}

bool isMovesLeft(const Board &b) {
    return std::any_of(b.begin(), b.end(), [](char c){ return c == ' '; });
}

int evaluate(const Board &b, char ai, char human) {
    char w = checkWinner(b);
    if (w == ai) return +10;
    if (w == human) return -10;
    return 0;
}

int minimax(Board &b, int depth, bool isMax, char ai, char human, int alpha, int beta) {
    int score = evaluate(b, ai, human);
    if (score == 10) return score - depth;   // prefer faster wins
    if (score == -10) return score + depth;  // prefer slower losses
    if (!isMovesLeft(b)) return 0;

    if (isMax) {
        int best = std::numeric_limits<int>::min();
        for (int i = 0; i < 9; ++i) {
            if (b[i] == ' ') {
                b[i] = ai;
                int val = minimax(b, depth + 1, false, ai, human, alpha, beta);
                b[i] = ' ';
                best = std::max(best, val);
                alpha = std::max(alpha, val);
                if (beta <= alpha) break; // beta cut-off
            }
        }
        return best;
    } else {
        int best = std::numeric_limits<int>::max();
        for (int i = 0; i < 9; ++i) {
            if (b[i] == ' ') {
                b[i] = human;
                int val = minimax(b, depth + 1, true, ai, human, alpha, beta);
                b[i] = ' ';
                best = std::min(best, val);
                beta = std::min(beta, val);
                if (beta <= alpha) break; // alpha cut-off
            }
        }
        return best;
    }
}

int findBestMove(Board &b, char ai, char human) {
    int bestVal = std::numeric_limits<int>::min();
    int bestMove = -1;
    for (int i = 0; i < 9; ++i) {
        if (b[i] == ' ') {
            b[i] = ai;
            int moveVal = minimax(b, 0, false, ai, human, std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
            b[i] = ' ';
            if (moveVal > bestVal) {
                bestMove = i;
                bestVal = moveVal;
            }
        }
    }
    return bestMove;
}

int askIntInRange(const std::string &prompt, int lo, int hi) {
    while (true) {
        std::cout << prompt;
        std::string s;
        if (!std::getline(std::cin, s)) return lo; // default
        try {
            int v = std::stoi(s);
            if (v >= lo && v <= hi) return v;
        } catch (...) {}
        std::cout << "Please enter a number between " << lo << " and " << hi << ".\n";
    }
}

char askSymbol() {
    while (true) {
        std::cout << "Choose your symbol (X/O): ";
        std::string s; std::getline(std::cin, s);
        if (!s.empty()) {
            char c = (char)std::toupper((unsigned char)s[0]);
            if (c == 'X' || c == 'O') return c;
        }
        std::cout << "Invalid choice. Type X or O.\n";
    }
}

bool playOneGame() {
    Board b; b.fill(' ');
    char human = askSymbol();
    char ai = (human == 'X') ? 'O' : 'X';
    int first = askIntInRange("Who plays first? 1=You, 2=Computer: ", 1, 2);
    bool humanTurn = (first == 1);

    while (true) {
        printBoard(b);
        char w = checkWinner(b);
        if (w == human) { std::cout << "You win!\n"; break; }
        if (w == ai)    { std::cout << "Computer wins.\n"; break; }
        if (!isMovesLeft(b)) { std::cout << "It's a draw.\n"; break; }

        if (humanTurn) {
            int move = askIntInRange("Your move (1-9): ", 1, 9) - 1;
            if (b[move] != ' ') {
                std::cout << "That square is taken. Try again.\n";
                continue;
            }
            b[move] = human;
        } else {
            int move = findBestMove(b, ai, human);
            if (move == -1) {
                // should not happen, but fallback: pick first free
                for (int i = 0; i < 9; ++i) if (b[i] == ' ') { move = i; break; }
            }
            b[move] = ai;
            std::cout << "Computer chose position " << (move + 1) << ".\n";
        }
        humanTurn = !humanTurn;
    }

    printBoard(b);
    std::cout << "Play again? (y/n): ";
    std::string s; std::getline(std::cin, s);
    return !s.empty() && (s[0] == 'y' || s[0] == 'Y');
}

int main() {
    std::cout << "Tic-Tac-Toe (You vs Computer)\n";
    std::cout << "Enter numbers 1-9 to place your mark as shown on the board.\n";
    do { /* loop */ } while (playOneGame());
    std::cout << "Thanks for playing!\n";
    return 0;
}
