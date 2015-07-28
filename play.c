#include "connect4.c"

int main(void) {
    int i, j;

    //playGame();

    // Testing

    // Test heuristic function
    printf("\n");
    GameState gameState = (GameState){.turn = 0, .board = 0, .columnHeight = {5, 5, 5, 5, 5, 5, 5}, .valid = true};

    for (i = 0; i < 6; i++) {
        for (j = 0; j < 7; j++) {
            gameState.board[i][j] = ' ';
        }
    }

    /*
    gameState.board[5][0] = 'X';
    gameState.board[4][0] = 'X';
    gameState.board[3][0] = 'X';
    gameState.board[5][1] = 'O';
    gameState.board[5][2] = 'O';
    gameState.board[4][1] = 'O';
    gameState.board[4][2] = 'X';
    gameState.board[3][1] = 'X';
    gameState.board[3][2] = 'X';
    
    printBoard2(gameState.board);

    gameState.columnHeight[0] = 2;
    gameState.columnHeight[1] = 2;
    gameState.columnHeight[2] = 1;
    gameState.columnHeight[3] = 3;
    gameState.columnHeight[4] = 4;
    gameState.columnHeight[5] = 4;

    printBoard2(gameState.board);
    */


    performMoveOnExplicit(&gameState, 3, 'X');
    gameState.turn = !gameState.turn;

    printf("Turn: %i, symbol: %c \n", gameState.turn, getSymbol(gameState.turn));
    printBoard2(gameState.board);

    printf("VALUE: %f \n", heuristic(gameState));

    AIMove aiMove = getAIMoveOn(gameState);
    performMoveOn(&gameState, aiMove.move);

    printf("Turn: %i, symbol: %c \n", gameState.turn, getSymbol(gameState.turn));
    printBoard2(gameState.board);

    printf("VALUE: %f \n", heuristic(gameState));
    //printf("AIMOVE: value: %f, symbol: %c, column: %i \n", aiMove.value, aiMove.move.symbol, aiMove.move.column);

    performMoveOnExplicit(&gameState, 2, 'X');

    printf("Turn: %i, symbol: %c \n", gameState.turn, getSymbol(gameState.turn));
    printBoard2(gameState.board);

    printf("VALUE: %f \n", heuristic(gameState));

    aiMove = getAIMoveOn(gameState);
    performMoveOn(&gameState, aiMove.move);

    printf("Turn: %i, symbol: %c \n", gameState.turn, getSymbol(gameState.turn));
    printBoard2(gameState.board);

    printf("VALUE: %f \n", heuristic(gameState));
    //printf("AIMOVE: value: %f, symbol: %c, column: %i \n", aiMove.value, aiMove.move.symbol, aiMove.move.column);

    performMoveOnExplicit(&gameState, 3, 'X');

    printf("Turn: %i, symbol: %c \n", gameState.turn, getSymbol(gameState.turn));
    printBoard2(gameState.board);

    printf("VALUE: %f \n", heuristic(gameState));

    aiMove = getAIMoveOn(gameState);
    performMoveOn(&gameState, aiMove.move);

    printf("Turn: %i, symbol: %c \n", gameState.turn, getSymbol(gameState.turn));
    printBoard2(gameState.board);

    printf("VALUE: %f \n", heuristic(gameState));
    //printf("AIMOVE: value: %f, symbol: %c, column: %i \n", aiMove.value, aiMove.move.symbol, aiMove.move.column);

    return 0;
}

