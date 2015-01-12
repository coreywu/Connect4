#include <stdio.h>

typedef int bool;
enum { false, true };

typedef int Turn;

typedef struct {
    Turn turn;
    char board [6][7];
} GameState;
    
void printBoard(GameState gameState) {
    int i, j;
    printf("Begin printBoard \n");
    char playerSymbol = 0;
    if (gameState.turn) {
        playerSymbol = 'X';
    } else {
        playerSymbol = 'O';
    }
        
    printf("\n");
    printf("Player %c's Turn: \n", playerSymbol);

    for (i = 0; i < 6; i++) {
        for (j = 0; j < 7; j++) {
            if (j != 0) {
                printf(" |");
            }
            printf(" ");
            printf("%c", gameState.board[i][j]);
        }
        printf("\n");
        printf("--------------------------- \n");
    }
}

/**
 * Inefficiently check the entire board to find either a winner or a draw.
 */
char checkWinner(char board[6][7]) {
    int i, j;
    bool draw = true;

    // Check for a draw
    for (i = 0; i < 6; i ++) {
        for (j = 0; j < 7; j++) {
            if (board[i][j] == ' ') {
                draw = false;
                break;
            }
        }
    }
    if (draw) {
        return '-';
    }

    // Check whether there is a winner.
    for (i = 5; i >= 0; i--) {
        for (j = 0; j < 7; j++) {
            // Check vertical
            if (i >= 3) {
                if (board[i][j] == board[i-1][j] && board[i][j] == board[i-2][j] && board[i][j] == board[i-3][j] && board[i][j] != ' ') {
                    return board[i][j];
                }
            }
            // Check horizontal
            if (j <= 3) {
                if (board[i][j] == board[i][j+1] && board[i][j] == board[i][j+2] && board[i][j] == board[i][j+3] && board[i][j] != ' ') {
                    return board[i][j];
                }
            }
            // Check diagnol - up-right
            if (i >= 3 && j <= 3) {
                if (board[i][j] == board[i-1][j+1] && board[i][j] == board[i-2][j+2] && board[i][j] == board[i-3][j+3] && board[i][j] != ' ') {
                    return board[i][j];
                }
            }
            // Check diagnol - up-left
            if (i >= 3 && j >= 3) {
                if (board[i][j] == board[i-1][j-1] && board[i][j] == board[i-2][j-2] && board[i][j] == board[i-3][j-3] && board[i][j] != ' ') {
                    return board[i][j];
                }
            }
        }
    }
    // No winner yet
    return '?';
}

int main(void) {
    printf("Begin main \n");
    int i, j;

    char emptyBoard [6][7];
    GameState gameState = {1, *emptyBoard};

    for (i = 0; i < 6; i++) {
        for (j = 0; j < 7; j++) {
            gameState.board[i][j] = ' ';
        }
    }
    printBoard(gameState);
    printf("Winner: %c \n", checkWinner(gameState.board));

    // Testing
    char verticalBoard [6][7];
    for (i = 0; i < 6; i++) {
        for (j = 0; j < 7; j++) {
            verticalBoard[i][j] = ' ';
        }
    }
    verticalBoard[2][6] = 'X';
    verticalBoard[3][6] = 'X';
    verticalBoard[4][6] = 'X';
    verticalBoard[5][6] = 'X';
    printf("Winner: %c \n", checkWinner(verticalBoard));

    char horizontalBoard [6][7];
    for (i = 0; i < 6; i++) {
        for (j = 0; j < 7; j++) {
            horizontalBoard[i][j] = ' ';
        }
    }
    horizontalBoard[0][3] = 'O';
    horizontalBoard[0][4] = 'O';
    horizontalBoard[0][5] = 'O';
    horizontalBoard[0][6] = 'O';
    printf("Winner: %c \n", checkWinner(horizontalBoard));

    char diagonalBoard [6][7];
    for (i = 0; i < 6; i++) {
        for (j = 0; j < 7; j++) {
            diagonalBoard[i][j] = ' ';
        }
    }
    diagonalBoard[3][3] = 'X';
    diagonalBoard[2][4] = 'X';
    diagonalBoard[1][5] = 'X';
    diagonalBoard[0][6] = 'X';
    printf("Winner: %c \n", checkWinner(diagonalBoard));

    char diagonalBoard2 [6][7];
    for (i = 0; i < 6; i++) {
        for (j = 0; j < 7; j++) {
            diagonalBoard2[i][j] = ' ';
        }
    }
    diagonalBoard2[0][0] = 'O';
    diagonalBoard2[1][1] = 'O';
    diagonalBoard2[2][2] = 'O';
    diagonalBoard2[3][3] = 'O';
    printf("Winner: %c \n", checkWinner(diagonalBoard2));

    return 0;
}
