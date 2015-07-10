#include "minunit.h"
#include "connect4.c"

MU_TEST(test_checkWinnerVerticalBoard) {
    int i,j;
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
    int i,j;
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

MU_TEST_SUITE(test_suite) {
    MU_RUN_TEST(test_checkWinnerVerticalBoard);
    MU_RUN_TEST(test_checkWinnerHorizontalBoard);
}

int main(int argc, char *argv[]) {
    MU_RUN_SUITE(test_suite);
    MU_REPORT();
    return 0;
}
