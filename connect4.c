#include <stdio.h>

#define HUMAN 1
#define AI 0

typedef int bool;
enum { false, true };

typedef int Turn;

typedef struct {
    Turn turn;
    char board [6][7];
} GameState;

typedef struct {
    int x;
    int y;
} Position;

Position getHumanMove();
Position getAIMove();
char getSymbol();
void printBoard();
char checkWinner();

int player1 = HUMAN;
int player2 = HUMAN;

GameState gameState;

void playGame() {
    int i, j;

    char emptyBoard [6][7];
    GameState gameState = {1, *emptyBoard};

    for (i = 0; i < 6; i++) {
        for (j = 0; j < 7; j++) {
            gameState.board[i][j] = ' ';
        }
    }
    printBoard(gameState);

    Position position;
    while(true) {
        position = getHumanMove();
        printf("Move: (%c, %c) \n", position.x, position.y);
    }
}
    
Position getMove(int playerNum) {
    Position position;
    char playerSymbol = getSymbol(gameState.turn);
    if (playerNum == 1) {
        if (player1 == HUMAN) {
            position = getHumanMove();
        } else {
            position = getAIMove();
        }
    } else {
        if (player2 == HUMAN) {
            position = getHumanMove();
        } else {
            position = getAIMove();
        }
    }
    return position;
}

Position getHumanMove() {
    bool valid = false;
    char input[2] = {0, 0};
    while (!valid) {
        printf("Enter input: ");
        scanf("%s", &input);
        // Convert to int
        input[0] = input[0] - '0';
        input[1] = input[1] - '0';
        if (input[0] > 0 && input[0] < 8 && input[1] > 0 && input[1] < 7) {
            valid = true;
        }
    }
    Position position = {input[0], input[1]};
    return position;
}

Position getAIMove() {
    // TODO
    Position position = {0, 0};
    return position;
}


char getSymbol(Turn turn) {
    char symbol = 0;
    if (turn) {
        symbol = 'X';
    } else {
        symbol = 'O';
    }
    return symbol;
}

void printBoard() {
    int i, j;
    printf("Begin printBoard \n");
    char playerSymbol = getSymbol(gameState.turn);
        
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
            // Check diagonal - up-right
            if (i >= 3 && j <= 3) {
                if (board[i][j] == board[i-1][j+1] && board[i][j] == board[i-2][j+2] && board[i][j] == board[i-3][j+3] && board[i][j] != ' ') {
                    return board[i][j];
                }
            }
            // Check diagonal - up-left
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

    playGame();

    /*
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
    **/

    return 0;
}
