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

MU_TEST(test_gameStateEquals) {
    int i, j;
    GameState gameState1 = (GameState){.turn = 0, .board = 0, .columnHeight = {5, 5, 5, 5, 5, 5, 5}, .valid = true};
    GameState gameState2 = (GameState){.turn = 0, .board = 0, .columnHeight = {5, 5, 5, 5, 5, 5, 5}, .valid = true};

    for (i = 0; i < 6; i++) {
        for (j = 0; j < 7; j++) {
            gameState1.board[i][j] = ' ';
            gameState2.board[i][j] = ' ';
        }
    }

    mu_check(gameStateEquals(gameState1, gameState2));

    performMoveOnExplicit(&gameState1, 0, 'X');
    performMoveOnExplicit(&gameState2, 0, 'X');

    performMoveOnExplicit(&gameState1, 0, 'O');
    performMoveOnExplicit(&gameState2, 0, 'O');

    performMoveOnExplicit(&gameState2, 0, 'X');
    performMoveOnExplicit(&gameState1, 0, 'X');
    

    mu_check(gameStateEquals(gameState1, gameState2));
}

GameState successorsTestGameState;
GameState successors[7];
GameState expectedGameState;

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

    expectedGameState.turn = 1;

    performMoveOnExplicit(&expectedGameState, 0, 'X');
    mu_check(gameStateEquals(successors[0], expectedGameState));

    expectedGameState.board[5][0] = ' ';
    expectedGameState.columnHeight[0] = 5;

    performMoveOnExplicit(&expectedGameState, 1, 'X');
    mu_check(gameStateEquals(successors[1], expectedGameState));

    expectedGameState.board[5][1] = ' ';
    expectedGameState.columnHeight[1] = 5;

    performMoveOnExplicit(&expectedGameState, 2, 'X');
    mu_check(gameStateEquals(successors[2], expectedGameState));

    expectedGameState.board[5][2] = ' ';
    expectedGameState.columnHeight[2] = 5;

    performMoveOnExplicit(&expectedGameState, 3, 'X');
    mu_check(gameStateEquals(successors[3], expectedGameState));

    expectedGameState.board[5][3] = ' ';
    expectedGameState.columnHeight[3] = 5;

    performMoveOnExplicit(&expectedGameState, 4, 'X');
    mu_check(gameStateEquals(successors[4], expectedGameState));

    expectedGameState.board[5][4] = ' ';
    expectedGameState.columnHeight[4] = 5;

    performMoveOnExplicit(&expectedGameState, 5, 'X');
    mu_check(gameStateEquals(successors[5], expectedGameState));

    expectedGameState.board[5][5] = ' ';
    expectedGameState.columnHeight[5] = 5;

    performMoveOnExplicit(&expectedGameState, 6, 'X');
    mu_check(gameStateEquals(successors[6], expectedGameState));

    expectedGameState.board[5][6] = ' ';
    expectedGameState.columnHeight[6] = 5;
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

    expectedGameState.board[5][0] = 'X';
    expectedGameState.columnHeight[0] = 4;
    expectedGameState.board[5][1] = 'O';
    expectedGameState.columnHeight[1] = 4;
    expectedGameState.board[5][2] = 'X';
    expectedGameState.columnHeight[2] = 4;
    expectedGameState.board[5][3] = 'O';
    expectedGameState.columnHeight[3] = 4;
    expectedGameState.board[5][4] = 'X';
    expectedGameState.columnHeight[4] = 4;
    expectedGameState.board[5][5] = 'O';
    expectedGameState.columnHeight[5] = 4;
    expectedGameState.board[5][6] = 'X';
    expectedGameState.columnHeight[6] = 4;

    // Test successors of board with 1 symbol in each column
    getSuccessors(successors, successorsTestGameState);

    expectedGameState.turn = 1;

    performMoveOnExplicit(&expectedGameState, 0, 'X');
    mu_check(gameStateEquals(successors[0], expectedGameState));

    expectedGameState.board[4][0] = ' ';
    expectedGameState.columnHeight[0] = 4;

    performMoveOnExplicit(&expectedGameState, 1, 'X');
    mu_check(gameStateEquals(successors[1], expectedGameState));

    expectedGameState.board[4][1] = ' ';
    expectedGameState.columnHeight[1] = 4;

    performMoveOnExplicit(&expectedGameState, 2, 'X');
    mu_check(gameStateEquals(successors[2], expectedGameState));

    expectedGameState.board[4][2] = ' ';
    expectedGameState.columnHeight[2] = 4;

    performMoveOnExplicit(&expectedGameState, 3, 'X');
    mu_check(gameStateEquals(successors[3], expectedGameState));

    expectedGameState.board[4][3] = ' ';
    expectedGameState.columnHeight[3] = 4;

    performMoveOnExplicit(&expectedGameState, 4, 'X');
    mu_check(gameStateEquals(successors[4], expectedGameState));

    expectedGameState.board[4][4] = ' ';
    expectedGameState.columnHeight[4] = 4;

    performMoveOnExplicit(&expectedGameState, 5, 'X');
    mu_check(gameStateEquals(successors[5], expectedGameState));

    expectedGameState.board[4][5] = ' ';
    expectedGameState.columnHeight[5] = 4;

    performMoveOnExplicit(&expectedGameState, 6, 'X');
    mu_check(gameStateEquals(successors[6], expectedGameState));

    expectedGameState.board[4][6] = ' ';
    expectedGameState.columnHeight[6] = 4;
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

    successorsTestGameState.columnHeight[0] = -1;
    successorsTestGameState.columnHeight[1] = -1;
    successorsTestGameState.columnHeight[2] = 0;
    successorsTestGameState.columnHeight[3] = 1;
    successorsTestGameState.columnHeight[4] = 2;
    successorsTestGameState.columnHeight[5] = 3;

    expectedGameState.board[4][0] = 'O';
    expectedGameState.board[4][1] = 'O';
    expectedGameState.board[4][2] = 'X';
    expectedGameState.board[4][3] = 'X';
    expectedGameState.board[4][4] = 'O';
    expectedGameState.board[4][5] = 'O';

    expectedGameState.board[3][0] = 'X';
    expectedGameState.board[3][1] = 'X';
    expectedGameState.board[3][2] = 'O';
    expectedGameState.board[3][3] = 'X';
    expectedGameState.board[3][4] = 'X';

    expectedGameState.board[2][0] = 'O';
    expectedGameState.board[2][1] = 'X';
    expectedGameState.board[2][2] = 'O';
    expectedGameState.board[2][3] = 'X';

    expectedGameState.board[1][0] = 'X';
    expectedGameState.board[1][1] = 'O';
    expectedGameState.board[1][2] = 'X';

    expectedGameState.board[0][0] = 'O';
    expectedGameState.board[0][1] = 'O';

    expectedGameState.columnHeight[0] = -1;
    expectedGameState.columnHeight[1] = -1;
    expectedGameState.columnHeight[2] = 0;
    expectedGameState.columnHeight[3] = 1;
    expectedGameState.columnHeight[4] = 2;
    expectedGameState.columnHeight[5] = 3;

    // Test successors with varying column heights
    getSuccessors(successors, successorsTestGameState);

    // turn is still 0 because successor is invalid
    expectedGameState.turn = 0;
    expectedGameState.valid = 0;
    performMoveOnExplicit(&expectedGameState, 0, 'X');
    mu_check(gameStateEquals(successors[0], expectedGameState));

    // turn is still 0 because successor is invalid
    expectedGameState.turn = 0;
    expectedGameState.valid = 0;
    performMoveOnExplicit(&expectedGameState, 1, 'X');
    mu_check(gameStateEquals(successors[1], expectedGameState));

    expectedGameState.turn = 1;
    expectedGameState.valid = 1;
    performMoveOnExplicit(&expectedGameState, 2, 'X');
    mu_check(gameStateEquals(successors[2], expectedGameState));

    expectedGameState.board[0][2] = ' ';
    expectedGameState.columnHeight[2] = 0;

    expectedGameState.turn = 1;
    expectedGameState.valid = 1;
    performMoveOnExplicit(&expectedGameState, 3, 'X');
    mu_check(gameStateEquals(successors[3], expectedGameState));

    expectedGameState.board[1][3] = ' ';
    expectedGameState.columnHeight[3] = 1;

    expectedGameState.turn = 1;
    expectedGameState.valid = 1;
    performMoveOnExplicit(&expectedGameState, 4, 'X');
    mu_check(gameStateEquals(successors[4], expectedGameState));

    expectedGameState.board[2][4] = ' ';
    expectedGameState.columnHeight[4] = 2;

    expectedGameState.turn = 1;
    expectedGameState.valid = 1;
    performMoveOnExplicit(&expectedGameState, 5, 'X');
    mu_check(gameStateEquals(successors[5], expectedGameState));

    expectedGameState.board[3][5] = ' ';
    expectedGameState.columnHeight[5] = 3;

    expectedGameState.turn = 1;
    expectedGameState.valid = 1;
    performMoveOnExplicit(&expectedGameState, 6, 'X');
    mu_check(gameStateEquals(successors[6], expectedGameState));

    expectedGameState.board[4][6] = ' ';
    expectedGameState.columnHeight[6] = 4;
}

MU_TEST(test_value) {
    int i, j;
    // Test value of a game winning move
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
 
    valueTestGameState.turn = 0;
    AIMove aiMove = value(valueTestGameState, 1);   
    mu_check(aiMove.value == 100);

    valueTestGameState.turn = 1;
    AIMove aiMove2 = value(valueTestGameState, 1);   
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
    
    // Valid threeInARow positions
    mu_check(threeInARow('X', threeInARowGameState.board, 2, 0) == true);
    mu_check(threeInARow('X', threeInARowGameState.board, 2, 1) == true);
    mu_check(threeInARow('X', threeInARowGameState.board, 2, 2) == true);
    mu_check(threeInARow('X', threeInARowGameState.board, 2, 3) == true);
    mu_check(threeInARow('X', threeInARowGameState.board, 3, 3) == true);
    mu_check(threeInARow('X', threeInARowGameState.board, 4, 3) == true);
    mu_check(threeInARow('X', threeInARowGameState.board, 5, 3) == true);

    // Invalid threeInARow positions (outside)
    mu_check(threeInARow('X', threeInARowGameState.board, 1, 0) == false);
    mu_check(threeInARow('X', threeInARowGameState.board, 1, 1) == false);
    mu_check(threeInARow('X', threeInARowGameState.board, 1, 2) == false);
    mu_check(threeInARow('X', threeInARowGameState.board, 1, 3) == false);
    mu_check(threeInARow('X', threeInARowGameState.board, 1, 4) == false);
    mu_check(threeInARow('X', threeInARowGameState.board, 2, 4) == false);
    mu_check(threeInARow('X', threeInARowGameState.board, 3, 4) == false);
    mu_check(threeInARow('X', threeInARowGameState.board, 4, 4) == false);
    mu_check(threeInARow('X', threeInARowGameState.board, 5, 4) == false);

    // TwoInARows are in the same positions as threeInARows
    mu_check(twoInARow('X', threeInARowGameState.board, 2, 0) == true);
    mu_check(twoInARow('X', threeInARowGameState.board, 2, 1) == true);
    mu_check(twoInARow('X', threeInARowGameState.board, 2, 2) == true);
    mu_check(twoInARow('X', threeInARowGameState.board, 2, 3) == true);
    mu_check(twoInARow('X', threeInARowGameState.board, 3, 3) == true);
    mu_check(twoInARow('X', threeInARowGameState.board, 4, 3) == true);
    mu_check(twoInARow('X', threeInARowGameState.board, 5, 3) == true);

    mu_check(twoInARow('X', threeInARowGameState.board, 1, 0) == false);
    mu_check(twoInARow('X', threeInARowGameState.board, 1, 1) == false);
    mu_check(twoInARow('X', threeInARowGameState.board, 1, 2) == false);
    mu_check(twoInARow('X', threeInARowGameState.board, 1, 3) == false);
    mu_check(twoInARow('X', threeInARowGameState.board, 1, 4) == false);
    mu_check(twoInARow('X', threeInARowGameState.board, 2, 4) == false);
    mu_check(twoInARow('X', threeInARowGameState.board, 3, 4) == false);
    mu_check(twoInARow('X', threeInARowGameState.board, 4, 4) == false);
    mu_check(twoInARow('X', threeInARowGameState.board, 5, 4) == false);

    // Value of 1.45 due to a net threeInARowCount of 7 (no additional
    // value from twoInARows because they are all part of the threeInARows
    mu_check(heuristic(threeInARowGameState) == 1.45);
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
    
    // Score is 0.5 (agent3 = 2, opponent3 = 0, agent2 = 2, opponent2 = 1)
    // net3 -> 0.4, net2 -> 0.1
    mu_check(heuristic(heuristicGameState) == 0.5);
}

MU_TEST(test_heuristic2) {
    heuristicGameState.board[2][2] = 'O';
    heuristicGameState.board[5][4] = 'O';
    heuristicGameState.board[5][5] = 'O';

    // Score is 0.2 (agent3 = 2, opponent3 = 1, agent2 = 1, opponent2 = 1)
    // net3 -> 0.2, net2 -> 0
    mu_check(heuristic(heuristicGameState) == 0.2);
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

    // Score is 99.9 because it's a guaranteed win given the correct moves
    mu_check(heuristic(heuristicGameState) == 99.9);
}

MU_TEST_SUITE(test_suite) {
    MU_RUN_TEST(test_checkWinnerVerticalBoard);
    MU_RUN_TEST(test_checkWinnerHorizontalBoard);
    MU_RUN_TEST(test_checkWinnerHorizontalBoard2);
    MU_RUN_TEST(test_checkWinnerdiagonalBoard);
    MU_RUN_TEST(test_checkWinnerDiagonalBoard2);
    MU_RUN_TEST(test_checkWinnerDrawBoard2);
    MU_RUN_TEST(test_gameStateEquals);
    MU_RUN_TEST(test_getSuccessors);
    MU_RUN_TEST(test_getSuccessors2);
    MU_RUN_TEST(test_getSuccessors3);
    MU_RUN_TEST(test_value);
    MU_RUN_TEST(test_threeInARow);
    MU_RUN_TEST(test_heuristic);
    MU_RUN_TEST(test_heuristic2);
    MU_RUN_TEST(test_heuristicGuaranteedWin);
}

int main(int argc, char *argv[]) {
    MU_RUN_SUITE(test_suite);
    MU_REPORT();
    return 0;
}
