#include <stdio.h>
#include <stdlib.h>
#include <time.h> // Required for random moves (Part 2)
#include "tictactoe.h"

int main() {
    srand(time(NULL));
     
    int size, mode;

    // Get board size
    printf("Enter board size N (3 <= N <= 10): ");
    scanf("%d", &size);

    if (size < MIN_SIZE || size > MAX_SIZE) {
        printf("Invalid size! Must be between 3 and 10.\n");
        return 1;
    }

    // Select Game Mode
    printf("\nSelect Game Mode:\n");
    printf("1. Two Players (User vs User)\n");
    printf("2. User vs Computer\n");
    printf("3. Three Players\n");
    printf("Enter choice (1-3): ");
    scanf("%d", &mode);

    if (mode < 1 || mode > 3) {
        printf("Invalid mode selected.\n");
        return 1;
    }

    char** board = initializeBoard(size);
    int moveCount = 0;
    int totalCells = size * size;
    char players[3] = {'X', 'O', 'Z'};
    int currentPlayerIndex = 0;

    while (1) {
        displayBoard(board, size);
        char currentPlayer = players[currentPlayerIndex];

        int validMove = 0;

        if (mode == 1 || (mode == 2 && currentPlayer == 'X') || (mode == 3)) {
            validMove = getMove(board, size, currentPlayer);
        } else if (mode == 2 && currentPlayer == 'O') {
            printf("Computer's turn (Player O):\n");
            validMove = getComputerMove(board, size);
        }

        if (!validMove) continue;

        moveCount++;
        writeLog(board, size, moveCount, currentPlayer);

        if (checkWin(board, size, currentPlayer)) {
            displayBoard(board, size);
            printf("Player %c wins!\n", currentPlayer);
            break;
        }

        if (checkDraw(board, size)) {
            displayBoard(board, size);
            printf("It's a draw!\n");
            break;
        }

        // Next player
        if (mode == 3)
            currentPlayerIndex = (currentPlayerIndex + 1) % 3;
        else
            currentPlayerIndex = (currentPlayerIndex + 1) % 2;
    }

    freeBoard(board, size);
    return 0;
}

// Allocate and initialize board
char** initializeBoard(int size) {
    char** board = malloc(size * sizeof(char*));
    for (int i = 0; i < size; i++) {
        board[i] = malloc(size * sizeof(char));
        for (int j = 0; j < size; j++) {
            board[i][j] = ' ';
        }
    }
    return board;
}

// Free board memory
void freeBoard(char** board, int size) {
    for (int i = 0; i < size; i++) {
        free(board[i]);
    }
    free(board);
}

// Print board
void displayBoard(char** board, int size) {
    printf("\n");
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf(" %c ", board[i][j]);
            if (j < size - 1) printf("|");
        }
        printf("\n");
        if (i < size - 1) {
            for (int j = 0; j < size; j++) {
                printf("---");
                if (j < size - 1) printf("+");
            }
            printf("\n");
        }
    }
    printf("\n");
}

// Get and validate move from user
int getMove(char** board, int size, char player) {
    int row, col;
    printf("Player %c, enter row and column (1-%d): ", player, size);
    scanf("%d %d", &row, &col);

    if (row < 1 || row > size || col < 1 || col > size) {
        printf("Invalid position! Try again.\n");
        return 0;
    }

    row--; col--;

    if (board[row][col] != ' ') {
        printf("Cell already occupied! Try again.\n");
        return 0;
    }

    board[row][col] = player;
    return 1;
}

// Simple computer move: pick first empty cell
int getComputerMove(char** board, int size) {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            if (board[i][j] == ' ') {
                board[i][j] = 'O';
                return 1;
            }
    return 0;
}

// Check for win
int checkWin(char** board, int size, char player) {
    // Check rows and columns
    for (int i = 0; i < size; i++) {
        int rowWin = 1, colWin = 1;
        for (int j = 0; j < size; j++) {
            if (board[i][j] != player) rowWin = 0;
            if (board[j][i] != player) colWin = 0;
        }
        if (rowWin || colWin) return 1;
    }

    // Check diagonals
    int diag1 = 1, diag2 = 1;
    for (int i = 0; i < size; i++) {
        if (board[i][i] != player) diag1 = 0;
        if (board[i][size - i - 1] != player) diag2 = 0;
    }

    return diag1 || diag2;
}

// Check for draw
int checkDraw(char** board, int size) {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            if (board[i][j] == ' ') return 0;
    return 1;
}

// Write to game log
void writeLog(char** board, int size, int moveNumber, char player) {
    FILE* file = fopen("game_log.txt", "a");
    if (!file) {
        printf("Unable to write to log file.\n");
        return;
    }

    fprintf(file, "Move %d: Player %c\n", moveNumber, player);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            fprintf(file, " %c ", board[i][j]);
            if (j < size - 1) fprintf(file, "|");
        }
        fprintf(file, "\n");
        if (i < size - 1) {
            for (int j = 0; j < size; j++) {
                fprintf(file, "---");
                if (j < size - 1) fprintf(file, "+");
            }
            fprintf(file, "\n");
        }
    }
    fprintf(file, "\n");
    fclose(file);
}
