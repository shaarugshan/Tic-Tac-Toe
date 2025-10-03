#include <stdio.h>
#include <stdlib.h>

#define MIN_SIZE 3
#define MAX_SIZE 10

// Function declarations
char** initializeBoard(int size);
void displayBoard(char** board, int size);
void freeBoard(char** board, int size);
int getMove(char** board, int size, char player);
int checkWin(char** board, int size, char player);
int checkDraw(char** board, int size);
void writeLog(char** board, int size, int moveNumber, char player);

int main() {
    int size;

    printf("Enter board size (3 to 10): ");
    scanf("%d", &size);

    if (size < MIN_SIZE || size > MAX_SIZE) {
        printf("Invalid size! Must be between 3 and 10.\n");
        return 1;
    }

    char** board = initializeBoard(size);
    int moveCount = 0;
    char currentPlayer = 'X';

    while (1) {
        displayBoard(board, size);
        if (!getMove(board, size, currentPlayer)) continue;

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

        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
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

// Get and validate move
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

