#include <iostream>
#include <vector>

const int ROWS = 6;
const int COLS = 7;

class Connect4 {
private:
    char board[ROWS][COLS];
    char currentPlayer;

public:
    Connect4() {
        // Initialize the board with empty spaces
        for (int i = 0; i < ROWS; ++i) {
            for (int j = 0; j < COLS; ++j) {
                board[i][j] = ' ';
            }
        }
        currentPlayer = 'X';
    }

    void displayBoard() const {
        for (int i = 0; i < ROWS; ++i) {
            for (int j = 0; j < COLS; ++j) {
                std::cout << "| " << board[i][j] << " ";
            }
            std::cout << "|\n";
        }
        std::cout << "-----------------------------\n";
        for (int i = 1; i <= COLS; ++i) {
            std::cout << "  " << i << " ";
        }
        std::cout << "\n";
    }

    bool isValidMove(int column) const {
        return column >= 1 && column <= COLS && board[0][column - 1] == ' ';
    }

    void makeMove(int column) {
        for (int i = ROWS - 1; i >= 0; --i) {
            if (board[i][column - 1] == ' ') {
                board[i][column - 1] = currentPlayer;
                break;
            }
        }
    }

    bool checkWin() const {
        // Check for horizontal, vertical, and diagonal wins
        return checkHorizontalWin() || checkVerticalWin() || checkDiagonalWin();
    }

    bool checkHorizontalWin() const {
        for (int i = 0; i < ROWS; ++i) {
            for (int j = 0; j <= COLS - 4; ++j) {
                if (board[i][j] == currentPlayer && board[i][j + 1] == currentPlayer &&
                    board[i][j + 2] == currentPlayer && board[i][j + 3] == currentPlayer) {
                    return true;
                }
            }
        }
        return false;
    }

    bool checkVerticalWin() const {
        for (int i = 0; i <= ROWS - 4; ++i) {
            for (int j = 0; j < COLS; ++j) {
                if (board[i][j] == currentPlayer && board[i + 1][j] == currentPlayer &&
                    board[i + 2][j] == currentPlayer && board[i + 3][j] == currentPlayer) {
                    return true;
                }
            }
        }
        return false;
    }

    bool checkDiagonalWin() const {
        for (int i = 0; i <= ROWS - 4; ++i) {
            for (int j = 0; j <= COLS - 4; ++j) {
                if (board[i][j] == currentPlayer && board[i + 1][j + 1] == currentPlayer &&
                    board[i + 2][j + 2] == currentPlayer && board[i + 3][j + 3] == currentPlayer) {
                    return true;
                }
            }
        }

        for (int i = 3; i < ROWS; ++i) {
            for (int j = 0; j <= COLS - 4; ++j) {
                if (board[i][j] == currentPlayer && board[i - 1][j + 1] == currentPlayer &&
                    board[i - 2][j + 2] == currentPlayer && board[i - 3][j + 3] == currentPlayer) {
                    return true;
                }
            }
        }

        return false;
    }

    bool isBoardFull() const {
        for (int i = 0; i < COLS; ++i) {
            if (board[0][i] == ' ') {
                return false;
            }
        }
        return true;
    }

    char getCurrentPlayer() const {
        return currentPlayer;
    }

    void switchPlayer() {
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }
};

int main() {
    Connect4 game;

    do {
        game.displayBoard();

        int column;
        do {
            std::cout << "Player " << game.getCurrentPlayer() << ", enter a column (1-" << COLS << "): ";
            std::cin >> column;
        } while (!game.isValidMove(column));

        game.makeMove(column);
        if (game.checkWin()) {
            game.displayBoard();
            std::cout << "Player " << game.getCurrentPlayer() << " wins!\n";
            break;
        } else if (game.isBoardFull()) {
            game.displayBoard();
            std::cout << "It's a draw!\n";
            break;
        }

        game.switchPlayer();

    } while (true);

    return 0;
}

