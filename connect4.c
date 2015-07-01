#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>

#define HUMAN 1
#define AI 0

typedef int bool;
enum { false, true };

typedef int Turn;

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
    int value;
    Move move;
} AIMove;

Move getMove();
Move getHumanMove();
Move getAIMove();
void performMove(Move);
void performMoveOn(GameState*, Move);

char getSymbol();
void printBoard();
void printBoard2(char[6][7]);
char checkWinner();

void getSuccessors(GameState[7], GameState);
AIMove value(Turn, GameState, int);
AIMove maxValue(GameState, int);
AIMove minValue(GameState, int);

int player1 = HUMAN;    // corresponds to turn 0
int player2 = AI;

GameState gameState;

void playGame() {
    int i, j;
    char winner;
    bool end = false;

    gameState = (GameState){.turn = 0, .board = 0, .columnHeight = {5, 5, 5, 5, 5, 5, 5}, .valid = false};

    for (i = 0; i < 6; i++) {
        for (j = 0; j < 7; j++) {
            gameState.board[i][j] = ' ';
        }
    }
    printBoard(gameState);

    Move move;
    while(!end) {
        move = getMove(gameState.turn);
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
    if (playerNum == 0) {
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
    int randNum = rand() % 7;
    Move move = {'O', randNum};
    return move;
}

void getSuccessors(GameState successors[7], GameState newGameState) {
    int i;
    for (i = 0; i < 7; i++) {
	successors[i] = newGameState;
        if (newGameState.board[0][i] != ' ') {
	        successors[i].valid = false;
	    } else {
            successors[i].turn = !successors[i].turn;
            Move move = {getSymbol(successors[i].turn), i};
            performMoveOn(&successors[i], move);
        }
    }
}

/**
 * Minimax algorithm implementation of AI.
 * AI's symbol is 'O' and turn is 1.
 **/
AIMove value(Turn turn, GameState gameState, int depth) {
    if (checkWinner(gameState.board) == 'O') {
        AIMove aiMove = {.value = 1, .move = 0};
        //printf("WINNER: OOOOOO %i \n", aiMove.value);
        return aiMove;
    } else if (checkWinner(gameState.board) == 'X') {
        AIMove aiMove = {.value = -1, .move = 0};
        return aiMove;
    } else if (checkWinner(gameState.board) == '-') {
        AIMove aiMove = {.value = 0, .move = 0};
        return aiMove;
    } else if (depth == 0) {
        AIMove aiMove = {.value = 0, .move = 0};
        return aiMove;
    } else {
        if (turn) {
            return maxValue(gameState, depth);
        } else {
            return minValue(gameState, depth);
        }
    }
}
AIMove maxValue(GameState gameState, int depth) {
    int i;
    AIMove successorMove;
    AIMove aiMove = {INT_MIN, 0};
    GameState successors[7];
    getSuccessors(successors, gameState);

    //printf("SUCCESSORs[0]: %i \n", value(0, successors[0]).value);
    //printBoard2(successors[0].board);

    //printf("SUCCESSORs[1]: %i \n", value(0, successors[1]).value);
    //printBoard2(successors[1].board);

    //printf("SUCCESSORs[2]: %i \n", value(0, successors[2]).value);
    //printBoard2(successors[2].board);

    //printf("SUCCESSORs[3]: %i \n", value(0, successors[3]).value);
    //printBoard2(successors[3].board);

    //printf("SUCCESSORs[4]: %i \n", value(0, successors[4]).value);
    //printBoard2(successors[4].board);

    //printf("SUCCESSORs[5]: %i \n", value(0, successors[5]).value);
    //printBoard2(successors[5].board);

    //printf("SUCCESSORs[6]: %i \n", value(0, successors[6]).value);
    //printBoard2(successors[6].board);

    for (i = 0; i < 7; i++) {
        if (successors[i].valid == true) {
            successorMove = value(0, successors[i], depth - 1);
            if (successorMove.value > aiMove.value) {
                aiMove = successorMove;
                aiMove.move.column = i;
            }
        }
    }
    return aiMove;
}

AIMove minValue(GameState gameState, int depth) {
    int i;
    AIMove successorMove;
    AIMove aiMove = {INT_MAX, 0};
    GameState successors[7];
    getSuccessors(successors, gameState);
    for (i = 0; i < 7; i++) {
        if (successors[i].valid == true) {
            successorMove = value(1, successors[i], depth - 1);
            if (successorMove.value < aiMove.value) {
                aiMove = successorMove;
                aiMove.move.column = i;
            }
        }
    }
    return aiMove;
}

int heuristic(GameState gameState) {
    char symbol = getSymbol(gameState.turn);
    printf("SYMBOL: %c \n", symbol);
    // check for guaranteed winning scenarios
    // check for guaranteed losing scenarios
    // check for 3 in a rows (agent and opponent)
    // check for 2 in a rows (agent and opponent)
    //for (gameState.board)
}

// Returns the number of symbols in a row adjacent to the current position 
// Takes symbol, the board, and the position (row and column)
int threeInARowCount(int turn, char board[6][7], int row, int column) {
    int count = 0;
    char symbol = getSymbol(turn);

    printf("SYMBOL: %c: %c, %c, %c \n", symbol, board[column + 1][row], board[column + 2][row], board[column + 3][row]);

    // down
    if (board[column + 1][row] == symbol && board[column + 2][row] == symbol&& board[column + 3][row] == symbol) {
        printf("COUNT++ \n");
        count++;
    }

    /*
    // left
    if (board[column + 1][row] == symbol && board[column + 2][row] == symbol&& board[column + 3][row] == symbol) {
        count++;
    }

    // right
    if (board[column + 1][row] == symbol && board[column + 2][row] == symbol&& board[column + 3][row] == symbol) {
        count++;
    }

    // down-left
    if (board[column + 1][row] == symbol && board[column + 2][row] == symbol&& board[column + 3][row] == symbol) {
        count++;
    }

    // down-right
    if (board[column + 1][row] == symbol && board[column + 2][row] == symbol&& board[column + 3][row] == symbol) {
        count++;
    }
    */
    return count;
}


void performMove(Move move) {
    gameState.board[gameState.columnHeight[move.column]][move.column] = move.symbol;
    gameState.columnHeight[move.column] = gameState.columnHeight[move.column] - 1; 
}

void performMoveOn(GameState *newGameState, Move move) {
    (*newGameState).board[(*newGameState).columnHeight[move.column]][move.column] = move.symbol;
    (*newGameState).columnHeight[move.column] = (*newGameState).columnHeight[move.column] - 1;
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

    // Test getSuccessors
    GameState successorsTestGameState = (GameState){.turn = 0, .board = 0, .columnHeight = {5, 5, 5, 5, 5, 5, 5}, .valid = true};

    for (i = 0; i < 6; i++) {
        for (j = 0; j < 7; j++) {
            successorsTestGameState.board[i][j] = ' ';
        }
    }

    GameState successors[7];

    /*
    // Test successors of empty board
    getSuccessors(successors, successorsTestGameState);

    printf("Empty board game state: \n");
    printBoard2(successorsTestGameState.board);

    printf("Empty board successor[0] game state: \n");
    printBoard2(successors[0].board);
    printf("\n");

    printf("Empty board successor[1] game state: \n");
    printBoard2(successors[1].board);
    printf("\n");

    printf("Empty board successor[2] game state: \n");
    printBoard2(successors[2].board);
    printf("\n");

    printf("Empty board successor[3] game state: \n");
    printBoard2(successors[3].board);
    printf("\n");

    printf("Empty board successor[4] game state: \n");
    printBoard2(successors[4].board);
    printf("\n");

    printf("Empty board successor[5] game state: \n");
    printBoard2(successors[5].board);
    printf("\n");

    printf("Empty board successor[6] game state: \n");
    printBoard2(successors[6].board);
    printf("\n");

    */


    successorsTestGameState.board[5][0] = 'X';
    successorsTestGameState.columnHeight[0] = 4;
    successorsTestGameState.board[5][1] = 'O';
    successorsTestGameState.columnHeight[1] = 4;
    successorsTestGameState.board[5][2] = 'X';
    successorsTestGameState.columnHeight[2] = 4;
    successorsTestGameState.board[5][3] = 'O';
    successorsTestGameState.columnHeight[3] = 4;
    successorsTestGameState.board[5][4] = 'X';
    successorsTestGameState.columnHeight[4] = 4;
    successorsTestGameState.board[5][5] = 'O';
    successorsTestGameState.columnHeight[5] = 4;
    successorsTestGameState.board[5][6] = 'X';
    successorsTestGameState.columnHeight[6] = 4;

    // Test successors of board with 1 symbol in each column
    /*
    getSuccessors(successors, successorsTestGameState);

    printf("Board game state: \n");
    printBoard2(successorsTestGameState.board);

    printf("Empty board successor[0] game state: \n");
    printBoard2(successors[0].board);
    printf("\n");

    printf("Empty board successor[1] game state: \n");
    printBoard2(successors[1].board);
    printf("\n");

    printf("Empty board successor[2] game state: \n");
    printBoard2(successors[2].board);
    printf("\n");

    printf("Empty board successor[3] game state: \n");
    printBoard2(successors[3].board);
    printf("\n");

    printf("Empty board successor[4] game state: \n");
    printBoard2(successors[4].board);
    printf("\n");

    printf("Empty board successor[5] game state: \n");
    printBoard2(successors[5].board);
    printf("\n");

    printf("Empty board successor[6] game state: \n");
    printBoard2(successors[6].board);
    printf("\n");

    */

    successorsTestGameState.board[4][0] = 'O';
    successorsTestGameState.board[4][1] = 'O';
    successorsTestGameState.board[4][2] = 'X';
    successorsTestGameState.board[4][3] = 'X';
    successorsTestGameState.board[4][4] = 'O';
    successorsTestGameState.board[4][5] = 'O';

    successorsTestGameState.board[3][0] = 'X';
    successorsTestGameState.board[3][1] = 'X';
    successorsTestGameState.board[3][2] = 'O';
    successorsTestGameState.board[3][3] = 'X';
    successorsTestGameState.board[3][4] = 'X';

    successorsTestGameState.board[2][0] = 'O';
    successorsTestGameState.board[2][1] = 'X';
    successorsTestGameState.board[2][2] = 'O';
    successorsTestGameState.board[2][3] = 'X';

    successorsTestGameState.board[1][0] = 'X';
    successorsTestGameState.board[1][1] = 'O';
    successorsTestGameState.board[1][2] = 'X';

    successorsTestGameState.board[0][0] = 'O';
    successorsTestGameState.board[0][1] = 'O';

    successorsTestGameState.columnHeight[0] = 0;
    successorsTestGameState.columnHeight[1] = 0;
    successorsTestGameState.columnHeight[2] = 0;
    successorsTestGameState.columnHeight[3] = 1;
    successorsTestGameState.columnHeight[4] = 2;
    successorsTestGameState.columnHeight[5] = 3;

    /*
    // Test successors with varying column heights
    getSuccessors(successors, successorsTestGameState);

    printf("Board game state: \n");
    printBoard2(successorsTestGameState.board);

    printf("Empty board successor[0] game state: valid: %i \n", successors[0].valid);
    printBoard2(successors[0].board);
    printf("\n");

    printf("Empty board successor[1] game state: valid: %i \n", successors[1].valid);
    printBoard2(successors[1].board);
    printf("\n");

    printf("Empty board successor[2] game state: valid: %i \n", successors[2].valid);
    printBoard2(successors[2].board);
    printf("\n");

    printf("Empty board successor[3] game state: valid: %i \n", successors[3].valid);
    printBoard2(successors[3].board);
    printf("\n");

    printf("Empty board successor[4] game state: valid: %i \n", successors[4].valid);
    printBoard2(successors[4].board);
    printf("\n");

    printf("Empty board successor[5] game state: valid: %i \n", successors[5].valid);
    printBoard2(successors[5].board);
    printf("\n");

    printf("Empty board successor[6] game state: valid: %i \n", successors[6].valid);
    printBoard2(successors[6].board);
    printf("\n");
    */

    // Test value
    GameState valueTestGameState = (GameState){.turn = 0, .board = 0, .columnHeight = {5, 5, 5, 5, 5, 5, 5}, .valid = true};

    for (i = 0; i < 6; i++) {
        for (j = 0; j < 7; j++) {
            valueTestGameState.board[i][j] = ' ';
        }
    }

    valueTestGameState.board[5][0] = 'O';
    valueTestGameState.board[5][1] = 'O';
    valueTestGameState.board[5][2] = 'O';
    valueTestGameState.columnHeight[0] = 4;
    valueTestGameState.columnHeight[1] = 4;
    valueTestGameState.columnHeight[2] = 4;
 
    AIMove aiMove = value(1, valueTestGameState, 1);   
    printf("TEST VALUE: \n");
    printBoard2(valueTestGameState.board);
    printf("WINNER %c \n", checkWinner(valueTestGameState.board));
    printf("VALUE: %i, COLUMN: %i, SYMBOL: %c \n", aiMove.value, aiMove.move.column, aiMove.move.symbol);

    // Test threeInARow function
    GameState threeInARowGameState = (GameState){.turn = 0, .board = 0, .columnHeight = {5, 5, 5, 5, 5, 5, 5}, .valid = true};

    for (i = 0; i < 6; i++) {
        for (j = 0; j < 7; j++) {
            threeInARowGameState.board[i][j] = ' ';
        }
    }

    threeInARowGameState.board[5][0] = 'X';
    threeInARowGameState.board[4][0] = 'X';
    threeInARowGameState.board[3][0] = 'X';

    printf("THREE IN A ROW: %i \n", threeInARowCount(threeInARowGameState.turn, threeInARowGameState.board, 0, 2));

    return 0;
}
