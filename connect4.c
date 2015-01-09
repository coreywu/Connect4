#include <stdio.h>

typedef int Turn;

typedef struct {
    Turn turn;
    char board [7][6];

} GameState;
    
void printBoard(GameState gameState) {
    printf("WTF");
    char playerSymbol = 0;
    if (gameState.turn) {
        strcpy(playerSymbol, "X");
    } else {
        strcpy(playerSymbol, "O");
    }
        
    printf("Player %s's Turn:", playerSymbol);
}

int main(void) {
    printf("HELLO WORLD");
    int i;
    int j;

    char emptyBoard [7][6];

    for (i = 0; i < 7; i++) {
        for (j = 0; j < 6; j++) {
            emptyBoard[i][j] = " ";
        }
    }
    
    GameState gameState = {0, emptyBoard};

    printBoard(gameState);
}

