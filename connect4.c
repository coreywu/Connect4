#include "connect4.h"

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

bool gameStateEquals(GameState gameState1, GameState gameState2) {
    /*
    printf("EQUALS TURN: %i \n", gameState1.turn == gameState2.turn);
    printf("EQUALS BOARD: %i \n", boardEquals(gameState1.board, gameState2.board));
    printf("EQUALS COLUMNHEIGHTS: %i \n", columnHeightEquals(gameState1.columnHeight, gameState2.columnHeight));
    printf("EQUALS VALID: %i \n", gameState1.valid == gameState2.valid);
    */
    return gameState1.turn == gameState2.turn
        && boardEquals(gameState1.board, gameState2.board)
        && columnHeightEquals(gameState1.columnHeight, gameState2.columnHeight)
        && gameState1.valid == gameState2.valid;
}

bool boardEquals(char board1[6][7], char board2[6][7]) {
    int i, j;
    for (i = 0; i < 6; i++) {
        for (j = 0; j < 7; j++) {
            if (board1[i][j] != board2[i][j]) {
                //printf("NOT EQUALS: row: %i, col: %i, 1: %i, 2: %i \n", i, j, board1[i][j],board2[i][j]);
                return false;
            }   
        }
    }
    return true;
}

bool columnHeightEquals(int columnHeight1[7], int columnHeight2[7]) {
    int i;
    for (i = 0; i < 7; i++) {
        if (columnHeight1[i] != columnHeight2[i]) {
            //printf("NOT EQUALS: col: %i, 1: %i, 2: %i \n", i, columnHeight1[i], columnHeight2[i]);
            return false;
        }   
    }
    return true;
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

AIMove getAIMoveOn(GameState gameState) {
    return value(gameState, 6);
}

void getSuccessors(GameState successors[7], GameState newGameState) {
    int i;
    for (i = 0; i < 7; i++) {
	successors[i] = newGameState;
        if (newGameState.board[0][i] != ' ') {
	        successors[i].valid = false;
	    } else {
            Move move = {getSymbol(successors[i].turn), i};
            performMoveOn(&successors[i], move);
            successors[i].turn = !successors[i].turn;
        }
    }
}

/**
 * Minimax algorithm implementation of AI. The value calculated is the value
 * of X. Positive values indicate that X is in a better position.
 * If there is a winner/loser return a large number that should be larger
 * than any possible value from maxValue/minValue.
 **/
AIMove value(GameState gameState, int depth) {
    if (checkWinner(gameState.board) == 'X') {
        AIMove aiMove = {.value = 100, .move = 0};
        return aiMove;
    } else if (checkWinner(gameState.board) == 'O') {
        AIMove aiMove = {.value = -100, .move = 0};
        return aiMove;
    } else if (checkWinner(gameState.board) == '-') {
        AIMove aiMove = {.value = 0, .move = 0};
        return aiMove;
    } else if (depth == 0) {
        double value = heuristic(gameState);
        AIMove aiMove = {.value = value, .move = 0};
        return aiMove;
    } else {
        if (!gameState.turn) {
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
            successorMove = value(successors[i], depth - 1);
            if (successorMove.value > aiMove.value) {
                aiMove = successorMove;
                aiMove.move.column = i;
            }
        }
    }
    //printf("MAX VALUE: %f, %i \n", aiMove.value, aiMove.move.column);
    aiMove.move.symbol = 'X';
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
            successorMove = value(successors[i], depth - 1);
            if (successorMove.value < aiMove.value) {
                aiMove = successorMove;
                aiMove.move.column = i;
            }
        }
    }
    //printf("MIN VALUE: %f, %i \n", aiMove.value, aiMove.move.column);
    aiMove.move.symbol = 'O';
    return aiMove;
}

double heuristic(GameState gameState) {
    int i, j;
    double score = 0;
    /*
    char symbol = getSymbol(gameState.turn);
    char opponentSymbol = getSymbol(!gameState.turn);
    */
    char agentSymbol = 'X';
    char opponentSymbol = 'O';
    // check for guaranteed winning scenarios
    // check for 3 in a rows (agent and opponent)
    // check for 2 in a rows (agent and opponent)

    // Create a board that stores whether a threeInARow exists in that
    // position. Positions with threeInARows do not gain value from also
    // having twoInARows (which is a given).
    char agentThreeInARowBoard[6][7];
    char opponentThreeInARowBoard[6][7];

    for (i = 0; i < 6; i++) {
        for (j = 0; j < 7; j++) {
            agentThreeInARowBoard[i][j] = ' ';
            opponentThreeInARowBoard[i][j] = ' ';
        }
    }

    int agentThreeInARowCount = 0;
    int opponentThreeInARowCount = 0;

    // Three in a rows that can be attainable on the next turn
    // If there are 2 or more of these, it is a guaranteed win/loss
    int agentAttainableThreeInARowCount = 0;
    int opponentAttainableThreeInARowCount = 0;

    // Array of calues chosen to score threeInARows.
    // 0 three-in-a-rows is worth 0, 1 is worth 0.2, etc
    // Function increases quadradically to 3.5 then increases at a lesser 
    // rate 
    double threeInARowValues[8] = {0, 0.2, 0.4, 0.8, 1.2, 1.3, 1.4, 1.45};

    // TODO: Add a smarter check to not check every position
    for (i = 0; i < 6; i++) {
        for (j = 0; j < 7; j++) {
            if (gameState.board[i][j] == ' ') {
                if (threeInARow(agentSymbol, gameState.board, i, j)) {
                    agentThreeInARowCount++;
                    agentThreeInARowBoard[i][j] = agentSymbol;
                    if (gameState.columnHeight[j] == i) {
                        agentAttainableThreeInARowCount += 1;
                    }
                }
                if (threeInARow(opponentSymbol, gameState.board, i, j)) {
                    opponentThreeInARowCount++;
                    opponentThreeInARowBoard[i][j] = opponentSymbol;
                    if (gameState.columnHeight[j] == i) {
                        opponentAttainableThreeInARowCount += 1;
                    }
                }
            }
        }
    }

    //printf("AGENT THREE IN A ROW COUNT: %i \n", agentThreeInARowCount);

    // TODO: determine when a win is guaranteed and ensure that the 
    // moves to achieve it are taken (certain 3 in a rows are 'attainable')
    int netThreeInARowCount = agentThreeInARowCount - opponentThreeInARowCount;
    int netAttainableThreeInARowCount = agentAttainableThreeInARowCount - opponentAttainableThreeInARowCount;

    //printf("NET ATTAINABLE THREE IN A ROW COUNT: %i \n", netAttainableThreeInARowCount);

    // guaranteed win/loss when the net attainable three in a row count is 
    // two or more; return a number slightly less than a win/loss
    if (netAttainableThreeInARowCount >= 2) {
        return 99.9;
    } else if (netAttainableThreeInARowCount <= -2) {
        return -99.9;
    }

    if (netThreeInARowCount < 0) {
        if (netThreeInARowCount < -7) {
            netThreeInARowCount = -7;
        }
        score -= threeInARowValues[-1 * netThreeInARowCount];
    } else {
        if (netThreeInARowCount > 7) {
            netThreeInARowCount = 7;
        }
        score += threeInARowValues[netThreeInARowCount];
    }

    //printf("NET THREE IN A ROW COUNT: %i \n", netThreeInARowCount);

    int agentTwoInARowCount = 0;
    int opponentTwoInARowCount = 0;

    // Values chosen to score twoInARows
    // 0 two in a rows is worth 0, 1 is worth 0.2, etc
    // Function increases quadradically to 3.5 then increases at a lesser 
    // rate 
    double twoInARowValues[8] = {0, 0.1, 0.2, 0.4, 0.6, 0.7, 0.8, 0.85};

    // TODO: Add a smarter check to not check every position
    for (i = 0; i < 6; i++) {
        for (j = 0; j < 7; j++) {
            if (gameState.board[i][j] == ' ') {
                if (agentThreeInARowBoard[i][j] == ' ' && twoInARow(agentSymbol, gameState.board, i, j)) {
                    agentTwoInARowCount++;
                }
                if (opponentThreeInARowBoard[i][j] == ' ' && twoInARow(opponentSymbol, gameState.board, i, j)) {
                    opponentTwoInARowCount++;
                }
            }
        }
    }

    //printf("AGENT TWO IN A ROW COUNT: %i \n", agentTwoInARowCount);

    int netTwoInARowCount = agentTwoInARowCount - opponentTwoInARowCount;
    if (netTwoInARowCount < 0) {
        if (netTwoInARowCount < -7) {
            netTwoInARowCount = -7;
        }
        score -= twoInARowValues[-1 * netTwoInARowCount];
    } else {
        if (netTwoInARowCount > 7) {
            netTwoInARowCount = 7;
        }
        score += twoInARowValues[netTwoInARowCount];
    }
    //printf("NET TWO IN A ROW COUNT: %i \n", netTwoInARowCount);

    return score;
}

// Returns whether there is three in a row adjacent to the current position 
// Takes symbol, the board, and the position (row and column)
bool threeInARow(char symbol, char board[6][7], int row, int column) {
    // down
    if (row < 3) {
        if (board[row + 1][column] == symbol && board[row + 2][column] == symbol&& board[row + 3][column] == symbol) {
            return true;
        }
    }

    // left (XXX-)
    if (column >= 3) {
        if (board[row][column - 1] == symbol && board[row][column - 2] == symbol&& board[row][column - 3] == symbol) {
            return true;
        }
    }

    // right
    if (column <= 3) {
        if (board[row][column + 1] == symbol && board[row][column + 2] == symbol&& board[row][column + 3] == symbol) {
            return true;
        }
    }

    // down-left
    if (row < 3 && column >= 3) {
        if (board[row + 1][column - 1] == symbol && board[row + 2][column - 2] == symbol&& board[row + 3][column - 3] == symbol) {
            return true;
        }
    }

    // down-right
    if (row < 3 && column <= 3) {
        if (board[row + 1][column + 1] == symbol && board[row + 2][column + 2] == symbol&& board[row + 3][column + 3] == symbol) {
            return true;
        }
    }

    // up-left
    if (row > 2 && column >= 3) {
        if (board[row - 1][column - 1] == symbol && board[row - 2][column - 2] == symbol && board[row - 3][column - 3] == symbol) {
            return true;
        }
    }

    // up-right
    if (row > 2 && column <= 3) {
        if (board[row - 1][column + 1] == symbol && board[row - 2][column + 2] == symbol && board[row - 3][column + 3] == symbol) {
            return true;
        }
    }

    // around (XX-X)
    if (column >= 2) {
        if (board[row][column - 1] == symbol && board[row][column - 2] == symbol&& board[row][column + 1] == symbol) {
            return true;
        }
    }

    // around (X-XX)
    if (column <= 4) {
        if (board[row][column + 1] == symbol && board[row][column + 2] == symbol&& board[row][column - 1] == symbol) {
            return true;
        }
    }

    return false;
}

// Returns whether there is two in a row adjacent to the current position 
// Takes symbol, the board, and the position (row and column)
// Accounts for useless twoInARows (XX-O is not useful because the empty position can never result in a 
// four-in-a-row horizontally)
bool twoInARow(char symbol, char board[6][7], int row, int column) {
    // down
    if (row < 4) {
        if (board[row + 1][column] == symbol && board[row + 2][column] == symbol && board[row + 3][column] == ' ') {
            return true;
        }
    }

    // left
    if (column >= 2) {
        if (board[row][column - 1] == symbol && board[row][column - 2] == symbol && board[row][column - 3] == ' ') {
            return true;
        }
    }

    // right
    if (column <= 4) {
        if (board[row][column + 1] == symbol && board[row][column + 2] == symbol && board[row][column + 3] == ' ') {
            return true;
        }
    }

    // down-left
    if (row < 4 && column >= 2) {
        if (board[row + 1][column - 1] == symbol && board[row + 2][column - 2] == symbol && board[row + 3][column - 3] == ' ') {
            return true;
        }
    }

    // down-right
    if (row < 4 && column <= 4) {
        if (board[row + 1][column + 1] == symbol && board[row + 2][column + 2] == symbol && board[row + 3][column + 3] == ' ') {
            return true;
        }
    }

    // up-left
    if (row > 1 && column >= 2) {
        if (board[row - 1][column - 1] == symbol && board[row - 2][column - 2] == symbol && board[row - 3][column - 3] == ' ') {
            return true;
        }
    }

    // up-right
    if (row > 1 && column <= 4) {
        if (board[row - 1][column + 1] == symbol && board[row - 2][column + 2] == symbol && board[row - 3][column + 3] == ' ') {
            return true;
        }
    }

    // around (X-X)
    if (column <= 5 && column >= 1) {
        if (board[row][column + 1] == symbol && board[row][column - 1] == symbol && (board[row][column + 2] == ' ' || board[row][column - 2] == ' ')) {
            return true;
        }
    }

    return false;
}

void performMove(Move move) {
    if (gameState.columnHeight[move.column] > -1) {
        gameState.board[gameState.columnHeight[move.column]][move.column] = move.symbol;
        gameState.columnHeight[move.column] = gameState.columnHeight[move.column] - 1; 
    }
}

void performMoveOn(GameState *newGameState, Move move) {
    if ((*newGameState).columnHeight[move.column] > -1) {
        (*newGameState).board[(*newGameState).columnHeight[move.column]][move.column] = move.symbol;
        (*newGameState).columnHeight[move.column] = (*newGameState).columnHeight[move.column] - 1;
    }
}

void performMoveOnExplicit(GameState *newGameState, int column, char symbol) {
    if ((*newGameState).columnHeight[column] > -1) {
        (*newGameState).board[(*newGameState).columnHeight[column]][column] = symbol;
        (*newGameState).columnHeight[column] = (*newGameState).columnHeight[column] - 1;
    }
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
