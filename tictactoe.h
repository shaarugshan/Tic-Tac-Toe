// tictactoe.h
// Header file for Tic-Tac-Toe game declarations and constants

#ifndef TICTACTOE_H
#define TICTACTOE_H

// Standard libraries needed for types/functions (optional but common practice)
#include <stdio.h>
#include <stdlib.h>

// Constants for board size limits
#define MIN_SIZE 3
#define MAX_SIZE 10

// Function declarations
char** initializeBoard(int size);       
void displayBoard(char** board, int size); 
void freeBoard(char** board, int size);     
int getMove(char** board, int size, char player); 
// Note: getComputerMove returns the move index for the main function to process
int getComputerMove(char** board, int size); 
int checkWin(char** board, int size, char player); 
int checkDraw(char** board, int size);  
void writeLog(char** board, int size, int moveNumber, char player); 

#endif // TICTACTOE_H
