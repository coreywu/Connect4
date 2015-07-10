#include "connect4.c"

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
 
    printBoard2(valueTestGameState.board);
    AIMove aiMove = value(1, valueTestGameState, 1);   
    printf("\n");
    printf("TEST VALUE: \n");
    printf("WINNER %c \n", checkWinner(valueTestGameState.board));
    printf("VALUE OF X: %f, COLUMN: %i, SYMBOL: %c \n", aiMove.value, aiMove.move.column, aiMove.move.symbol);

    AIMove aiMove2 = value(0, valueTestGameState, 1);   
    printf("VALUE OF O: %f, COLUMN: %i, SYMBOL: %c \n", aiMove2.value, aiMove2.move.column, aiMove2.move.symbol);

    /*
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
    threeInARowGameState.board[5][1] = 'X';
    threeInARowGameState.board[5][2] = 'X';
    threeInARowGameState.board[4][1] = 'X';
    threeInARowGameState.board[4][2] = 'X';
    threeInARowGameState.board[3][1] = 'X';
    threeInARowGameState.board[3][2] = 'X';
    
    printBoard2(threeInARowGameState.board);

    printf("HEURISTIC: expected 3 in a row: 7, score: %f \n", heuristic(threeInARowGameState));

    // Test heuristic function
    printf("\n");
    printf("TEST HEURISTIC FUNCTION 1 \n");
    GameState heuristicGameState = (GameState){.turn = 0, .board = 0, .columnHeight = {5, 5, 5, 5, 5, 5, 5}, .valid = true};

    for (i = 0; i < 6; i++) {
        for (j = 0; j < 7; j++) {
            heuristicGameState.board[i][j] = ' ';
        }
    }

    heuristicGameState.board[5][0] = 'X';
    heuristicGameState.board[4][0] = 'X';
    heuristicGameState.board[3][0] = 'X';
    heuristicGameState.board[5][1] = 'O';
    heuristicGameState.board[5][2] = 'O';
    heuristicGameState.board[4][1] = 'O';
    heuristicGameState.board[4][2] = 'X';
    heuristicGameState.board[3][1] = 'X';
    heuristicGameState.board[3][2] = 'X';
    
    printBoard2(heuristicGameState.board);

    printf("HEURISTIC: score: %f \n", heuristic(heuristicGameState));

    printf("\n");
    printf("TEST HEURISTIC FUNCTION 2 \n");

    heuristicGameState.board[2][2] = 'O';
    heuristicGameState.board[5][4] = 'O';
    heuristicGameState.board[5][5] = 'O';

    printBoard2(heuristicGameState.board);

    printf("HEURISTIC: score: %f \n", heuristic(heuristicGameState));

    printf("\n");
    printf("TEST HEURISTIC FUNCTION GUARANTEED WIN \n");

    heuristicGameState.board[5][3] = 'X';
    heuristicGameState.board[4][3] = 'X';

    heuristicGameState.columnHeight[0] = 2;
    heuristicGameState.columnHeight[1] = 2;
    heuristicGameState.columnHeight[2] = 1;
    heuristicGameState.columnHeight[3] = 3;
    heuristicGameState.columnHeight[4] = 4;
    heuristicGameState.columnHeight[5] = 4;

    printBoard2(heuristicGameState.board);
    printf("HEURISTIC: score: %f \n", heuristic(heuristicGameState));
    */

    return 0;
}

