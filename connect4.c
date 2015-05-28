#include <stdio.h>
#include <limits.h>
#include <string.h>

#define HUMAN 1
#define AI 0

typedef int bool;
enum { false, true };

typedef int Turn;

typedef struct {
    Turn turn;
    char board [6][7];
    int columnHeight [7];
} GameState;

typedef struct {
    char symbol;
    int column;
} Move;

typedef struct {
    int value;
    Move move;
} AIMove;

Move getMove();
Move getHumanMove();
Move getAIMove();
void performMove();

char getSymbol();
void printBoard();
char checkWinner();

GameState* getSuccessors(GameState);
AIMove value(Turn, char[6][7]);
AIMove maxValue(char[6][7]);
AIMove minValue(char[6][7]);

int player1 = HUMAN;
int player2 = HUMAN;

GameState gameState;

void playGame() {
    int i, j;
    char winner;
    bool end = false;

    gameState = (GameState){.turn = 0, .board = 0, .columnHeight = {5, 5, 5, 5, 5, 5, 5}};

    for (i = 0; i < 6; i++) {
        for (j = 0; j < 7; j++) {
            gameState.board[i][j] = ' ';
        }
    }
    printBoard(gameState);

    Move move;
    while(!end) {
        move = getMove();
        performMove(move);
        printBoard(gameState);
        printf("Move: %c -> %i \n", move.symbol, move.column);
        winner = checkWinner(gameState.board);
        if (winner != '?') {
            end = true;
            if (winner != '-') {
                printf("\n Winner: %c \n", winner); 
            } else {
                printf("\n Draw.");
            }
        }
        gameState.turn = !gameState.turn;
    }
}
    
Move getMove(int playerNum) {
    Move move;
    char playerSymbol = getSymbol(gameState.turn);
    if (playerNum == 1) {
        if (player1 == HUMAN) {
            move = getHumanMove();
        } else {
            move = getAIMove();
        }
    } else {
        if (player2 == HUMAN) {
            move = getHumanMove();
        } else {
            move = getAIMove();
        }
    }
    move.symbol = playerSymbol;
    return move;
}

Move getHumanMove() {
    bool valid = false;
    int input = 0;
    while (!valid) {
        printf("Enter input: ");
        scanf("%d", &input);
        if (input > 0 && input <= 7 && gameState.columnHeight[input - 1] >= 0) { 
            valid = true;
        }
    }
    Move move = {0, input - 1};
    return move;
}

Move getAIMove() {
    // TODO

    Move move = {0, 0};
    return move;
}

GameState* getSuccessors(GameState newGameState) {
    int i;
    GameState successors[7];
    for (i = 0; i < 7; i++) {
        if (newGameState.board[0][i] != " ") {
	    successors[i] = ((void *)0);
	} else {
	    successors[i] = newGameState;
	    successors[i].turn = !successors[i].turn;
	    Move move = {getSymbol(successors[i].turn), i};
	    performMoveOn(successors[i], move);
	}
    }
    return successors;
}

/**
 * Minimax algorithm implementation of AI.
 * AI's symbol is 'O' and turn is 1.
 **/
AIMove value(Turn turn, char board[6][7]) {
    if (checkWinner(board) == 'O') {
        AIMove aiMove = {0, 1};
        return aiMove;
    } else if (checkWinner(board) == 'X') {
        AIMove aiMove = {0, -1};
        return aiMove;
    } else if (checkWinner(board) == '-') {
        AIMove aiMove = {0, 0};
        return aiMove;
    } else {
        if (turn) {
            return maxValue(board);
        } else {
            return minValue(board);
        }
    }
}

AIMove maxValue(char board[6][7]) {
    int i;
    AIMove successorMove;
    AIMove aiMove = {INT_MIN, 0};
    GameState successors[7];
    memcpy(getSuccessors(board), successors, sizeof(GameState));
    //successors = getSuccessors(board);
    for (i = 0; i < 7; i++) {
        successorMove = value(0, successors[i].board);
        if (successorMove.value > aiMove.value) {
            aiMove = successorMove;
        }
    }
    return aiMove;
}

AIMove minValue(char board[6][7]) {
    int i;
    AIMove successorMove;
    AIMove aiMove = {INT_MAX, 0};
    GameState successors[7];
    memcpy(getSuccessors(board), successors, sizeof(GameState));
    //successors = getSuccessors(board);
    for (i = 0; i < 7; i++) {
        successorMove = value(1, successors[i].board);
        if (successorMove.value < aiMove.value) {
            aiMove = successorMove;
        }
    }
    return aiMove;
}


void performMove(Move move) {
    gameState.board[gameState.columnHeight[move.column]][move.column] = move.symbol;
    gameState.columnHeight[move.column] = gameState.columnHeight[move.column] - 1; 
}

void performMoveOn(GameState newGameState, Move move) {
    newGameState.board[gameState.columnHeight[move.column]][move.column] = move.symbol;
    newGameState.columnHeight[move.column] = gameState.columnHeight[move.column] - 1;
}

char getSymbol(Turn turn) {
    char symbol = 0;
    if (turn) {
        symbol = 'O';
    } else {
        symbol = 'X';
    }
    return symbol;
}

void printBoard() {
    int i, j;
    printf("Begin printBoard \n");
    char playerSymbol = getSymbol(gameState.turn);
        
    printf("\n");
    printf("Player %c's Turn: \n", playerSymbol);
    printf(" 1   2   3   4   5   6   7 \n");

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

void printBoard2(char board[6][7]) {
    int i, j;
    printf("Begin printBoard \n");
    char playerSymbol = getSymbol(gameState.turn);
    printf("\n");
    printf("Player %c's Turn: \n", playerSymbol);
    printf(" 1   2   3   4   5   6   7 \n");

    for (i = 0; i < 6; i++) {
        for (j = 0; j < 7; j++) {
            if (j != 0) {
                printf(" |");
            }
            printf(" ");
            printf("%c", board[i][j]);
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
    int i, j;

    //playGame();

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
    printf("TestVerticalWinner - expected: X \n");
    printf("Winner: %c \n", checkWinner(verticalBoard));
    printf("\n");

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
    printf("TestHorizontalWinner1 - expected: O \n");
    printf("Winner: %c \n", checkWinner(horizontalBoard));
    printf("\n");

    char horizontalBoard2 [6][7];
    for (i = 0; i < 6; i++) {
        for (j = 0; j < 7; j++) {
            horizontalBoard2[i][j] = ' ';
        }
    }
    horizontalBoard2[5][1] = 'O';
    horizontalBoard2[5][2] = 'O';
    horizontalBoard2[5][3] = 'O';
    horizontalBoard2[5][4] = 'O';
    printf("TestHorizontalWinner2 - expected: O \n");
    printf("Winner: %c \n", checkWinner(horizontalBoard2));
    printf("\n");

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
    printf("TestDiagonalWinner1 - expected: X \n");
    printf("Winner: %c \n", checkWinner(diagonalBoard));
    printf("\n");

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
    printf("TestDiagonalWinner2 - expected: O \n");
    printf("Winner: %c \n", checkWinner(diagonalBoard2));
    printf("\n");

    char drawBoard [6][7];
    for (i = 0; i < 6; i++) {
        for (j = 0; j < 7; j++) {
            drawBoard[i][j] = ' ';
        }
    }
    drawBoard[0][0] = 'O';
    drawBoard[0][1] = 'O';
    drawBoard[0][2] = 'O';
    drawBoard[0][3] = 'X';
    drawBoard[0][4] = 'O';
    drawBoard[0][5] = 'O';
    drawBoard[0][6] = 'O';

    drawBoard[1][0] = 'X';
    drawBoard[1][1] = 'X';
    drawBoard[1][2] = 'X';
    drawBoard[1][3] = 'O';
    drawBoard[1][4] = 'X';
    drawBoard[1][5] = 'X';
    drawBoard[1][6] = 'X';

    drawBoard[2][0] = 'O';
    drawBoard[2][1] = 'O';
    drawBoard[2][2] = 'X';
    drawBoard[2][3] = 'X';
    drawBoard[2][4] = 'X';
    drawBoard[2][5] = 'O';
    drawBoard[2][6] = 'X';

    drawBoard[3][0] = 'X';
    drawBoard[3][1] = 'X';
    drawBoard[3][2] = 'O';
    drawBoard[3][3] = 'O';
    drawBoard[3][4] = 'X';
    drawBoard[3][5] = 'X';
    drawBoard[3][6] = 'O';

    drawBoard[4][0] = 'O';
    drawBoard[4][1] = 'O';
    drawBoard[4][2] = 'X';
    drawBoard[4][3] = 'X';
    drawBoard[4][4] = 'O';
    drawBoard[4][5] = 'O';
    drawBoard[4][6] = 'X';

    drawBoard[5][0] = 'O';
    drawBoard[5][1] = 'O';
    drawBoard[5][2] = 'X';
    drawBoard[5][3] = 'X';
    drawBoard[5][4] = 'O';
    drawBoard[5][5] = 'X';
    drawBoard[5][6] = 'O';
    printBoard2(drawBoard);
    printf("TestDraw - expected: - \n");
    printf("Winner: %c \n", checkWinner(drawBoard));
    printf("\n");

    return 0;
}
