#include "minunit.h"
#include "connect4.c"

MU_TEST(test_checkWinnerVerticalBoard) {
    int i, j;
    char verticalBoard[6][7];
    for (i = 0; i < 6; i++) {
        for (j = 0; j < 7; j++) {
            verticalBoard[i][j] = ' ';
        }
    }
    verticalBoard[2][6] = 'X';
    verticalBoard[3][6] = 'X';
    verticalBoard[4][6] = 'X';
    verticalBoard[5][6] = 'X';
    mu_check(checkWinner(verticalBoard) == 'X');
}

MU_TEST(test_checkWinnerHorizontalBoard) {
    int i, j;
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
    mu_check(checkWinner(horizontalBoard) == 'O');
}

MU_TEST(test_checkWinnerHorizontalBoard2) {
    int i, j;
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
    mu_check(checkWinner(horizontalBoard2) == 'O');
}

MU_TEST(test_checkWinnerdiagonalBoard) {
    int i, j;
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
    mu_check(checkWinner(diagonalBoard) == 'X');
}

MU_TEST(test_checkWinnerDiagonalBoard2) {
    int i, j;
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
    mu_check(checkWinner(diagonalBoard2) == 'O');
}

MU_TEST(test_checkWinnerDrawBoard2) {
    int i, j;
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
    mu_check(checkWinner(drawBoard) == '-');
}

GameState successorsTestGameState;
GameState successors[7];
GameState expectedGameState;

/*
MU_TEST(test_getSuccessors) {
    int i, j;
    successorsTestGameState = (GameState){.turn = 0, .board = 0, .columnHeight = {5, 5, 5, 5, 5, 5, 5}, .valid = true};
    expectedGameState = (GameState){.turn = 0, .board = 0, .columnHeight = {5, 5, 5, 5, 5, 5, 5}, .valid = true};

    for (i = 0; i < 6; i++) {
        for (j = 0; j < 7; j++) {
            successorsTestGameState.board[i][j] = ' ';
            expectedGameState.board[i][j] = ' ';
        }
    }

    // Test successors of empty board
    getSuccessors(successors, successorsTestGameState);

    printf("Empty board game state: \n");
    printBoard2(successorsTestGameState.board);

    printf("Empty board successor[0] game state: \n");
    printBoard2(successors[0].board);
    printf("\n");

    performMoveOnExplicit(&expectedGameState, 0, 'X');
    mu_check(successors[0] == expectedGameState);

    printf("Empty board successor[1] game state: \n");
    printBoard2(successors[1].board);
    printf("\n");

    expectedGameState.board[5][1] = ' ';
    expectedGameState.columnHeight[1] = 5;
    performMoveOnExplicit(&expectedGameState, 0, 'X');
    mu_check(successors[1] == expectedGameState);

    printf("Empty board successor[2] game state: \n");
    printBoard2(successors[2].board);
    printf("\n");

    expectedGameState.board[5][2] = ' ';
    expectedGameState.columnHeight[2] = 5;
    performMoveOnExplicit(&expectedGameState, 0, 'X');
    mu_check(successors[2] == expectedGameState);

    printf("Empty board successor[3] game state: \n");
    printBoard2(successors[3].board);
    printf("\n");

    expectedGameState.board[5][3] = ' ';
    expectedGameState.columnHeight[3] = 5;
    performMoveOnExplicit(&expectedGameState, 0, 'X');
    mu_check(successors[3] == expectedGameState);

    printf("Empty board successor[4] game state: \n");
    printBoard2(successors[4].board);
    printf("\n");

    expectedGameState.board[5][4] = ' ';
    expectedGameState.columnHeight[4] = 5;
    performMoveOnExplicit(&expectedGameState, 0, 'X');
    mu_check(successors[4] == expectedGameState);

    printf("Empty board successor[5] game state: \n");
    printBoard2(successors[5].board);
    printf("\n");

    expectedGameState.board[5][5] = ' ';
    expectedGameState.columnHeight[5] = 5;
    performMoveOnExplicit(&expectedGameState, 0, 'X');
    mu_check(successors[5] == expectedGameState);

    printf("Empty board successor[6] game state: \n");
    printBoard2(successors[6].board);
    printf("\n");

    expectedGameState.board[5][6] = ' ';
    expectedGameState.columnHeight[6] = 5;
    performMoveOnExplicit(&expectedGameState, 0, 'X');
    mu_check(successors[6] == expectedGameState);
}

MU_TEST(test_getSuccessors2) {
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
}

MU_TEST(test_getSuccessors3) {
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
}
*/

MU_TEST(test_value) {
    int i, j;
    // Test value
    GameState valueTestGameState = (GameState){.turn = 0, .board = 0, .columnHeight = {5, 5, 5, 5, 5, 5, 5}, .valid = true};

    for (i = 0; i < 6; i++) {
        for (j = 0; j < 7; j++) {
            valueTestGameState.board[i][j] = ' ';
        }
    }

    valueTestGameState.board[5][0] = 'X';
    valueTestGameState.board[5][1] = 'X';
    valueTestGameState.board[5][2] = 'X';
    valueTestGameState.columnHeight[0] = 4;
    valueTestGameState.columnHeight[1] = 4;
    valueTestGameState.columnHeight[2] = 4;
 
    printBoard2(valueTestGameState.board);
    valueTestGameState.turn = 0;
    AIMove aiMove = value(valueTestGameState, 1);   
    printf("\n");
    printf("TEST VALUE: \n");
    printf("VALUE OF X IF IT IS X'S TURN: %f, COLUMN: %i, SYMBOL: %c \n", aiMove.value, aiMove.move.column, aiMove.move.symbol);
    mu_check(aiMove.value == 100);

    valueTestGameState.turn = 1;
    AIMove aiMove2 = value(valueTestGameState, 1);   
    printf("VALUE OF X IF IT IS O's TURN: %f, COLUMN: %i, SYMBOL: %c \n", aiMove2.value, aiMove2.move.column, aiMove2.move.symbol);
    mu_check(aiMove2.value == 0);
}

MU_TEST(test_threeInARow) {
    int i, j;
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
    //mu_check(heuristic(threeInARowGameState) == 0);
}

GameState heuristicGameState;

MU_TEST(test_heuristic) {
    int i, j;
    heuristicGameState = (GameState){.turn = 0, .board = 0, .columnHeight = {5, 5, 5, 5, 5, 5, 5}, .valid = true};

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
    //mu_check(heuristic(heuristicGameState) == 100);
}

MU_TEST(test_heuristic2) {
    heuristicGameState.board[2][2] = 'O';
    heuristicGameState.board[5][4] = 'O';
    heuristicGameState.board[5][5] = 'O';

    printBoard2(heuristicGameState.board);

    printf("HEURISTIC: score: %f \n", heuristic(heuristicGameState));
    //mu_check(heuristic(heuristicGameState) == 100);
}

MU_TEST(test_heuristicGuaranteedWin) {
    printf("TEST HEURISTIC FUNCTION GUARANTEED WIN \n");

    heuristicGameState.board[5][3] = 'X';
    heuristicGameState.board[4][3] = 'X';

    heuristicGameState.columnHeight[0] = 2;
    heuristicGameState.columnHeight[1] = 2;
    heuristicGameState.columnHeight[2] = 1;
    heuristicGameState.columnHeight[3] = 3;
    heuristicGameState.columnHeight[4] = 4;
    heuristicGameState.columnHeight[5] = 4;

    // printBoard2(heuristicGameState.board);
    printf("HEURISTIC: score: %f \n", heuristic(heuristicGameState));
    mu_check(heuristic(heuristicGameState) == 100);
}

MU_TEST_SUITE(test_suite) {
    MU_RUN_TEST(test_checkWinnerVerticalBoard);
    MU_RUN_TEST(test_checkWinnerHorizontalBoard);
    MU_RUN_TEST(test_checkWinnerHorizontalBoard2);
    MU_RUN_TEST(test_checkWinnerdiagonalBoard);
    MU_RUN_TEST(test_checkWinnerDiagonalBoard2);
    MU_RUN_TEST(test_checkWinnerDrawBoard2);
    /*
    MU_RUN_TEST(test_getSuccessors);
    MU_RUN_TEST(test_getSuccessors2);
    MU_RUN_TEST(test_getSuccessors3);
    */
    /*
    MU_RUN_TEST(test_value);
    MU_RUN_TEST(test_threeInARow);
    MU_RUN_TEST(test_heuristic);
    */
}

int main(int argc, char *argv[]) {
    MU_RUN_SUITE(test_suite);
    MU_REPORT();
    return 0;
}
