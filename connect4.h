#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>

#define HUMAN 1
#define AI 0

typedef int bool;
enum { false, true };

typedef int Turn;

// board is [row][column]; row is increasing from top to bottom, column is
// increasing from left to right
typedef struct {
    Turn turn;
    char board [6][7];
    int columnHeight [7];
    bool valid;
} GameState;

typedef struct {
    char symbol;
    int column;
} Move;

typedef struct {
    double value;
    Move move;
} AIMove;

Move getMove();
Move getHumanMove();
Move getAIMove();
void performMove(Move);
void performMoveOn(GameState*, Move);
void performMoveOnExplicit(GameState*, int, char);

char getSymbol();
void printBoard();
void printBoard2(char[6][7]);
char checkWinner();

void getSuccessors(GameState[7], GameState);
AIMove value(GameState, int);
AIMove maxValue(GameState, int);
AIMove minValue(GameState, int);
double heuristic(GameState);

int threeInARow(char, char[6][7], int, int);
int twoInARow(char, char[6][7], int, int);

int player1 = HUMAN;    // corresponds to turn 0
int player2 = AI;

GameState gameState;
