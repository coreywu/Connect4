import sys


class Game:
    def __init__(self, players):
        self.gameState = GameState()
        self.turn = 0
        self.players = players
        self.gameOver = False

    def play(self):
        while self.gameOver is False:
            self.printTurn()
            self.getMove()
            if self.gameState.checkWinner(self.players[self.turn].getPlayerSymbol()):
                self.declareWinner()
                self.gameOver = True
            self.nextTurn()

    def getMove(self):
        self.players[self.turn].selectMove(self.turn, self)

    def nextTurn(self):
        self.turn += 1
        self.turn %= 2

    def declareWinner(self):
        print "Player: {0} won!".format(self.players[self.turn].getPlayerSymbol())

    def printTurn(self):
        print
        print self.players[self.turn].getPlayerSymbol(), "'s Turn:"
        print
        print "      Board   "
        self.gameState.printBoard()


class GameState():
    def __init__(self, state=None):
        self.state = [[" "] * 3 for i in range(3)]
        if state is not None:
            for i in range(len(state)):
                for j in range(len(state[i])):
                    self.state[i][j] = state[i][j]

    def validMove(self, move):
        return self.state[move.row][move.column] == " "

    def checkWinner(self, playerSymbol):
        state = self.state
        # Horizontal
        if (state[0][0] == state[0][1] == state[0][2] == playerSymbol != " "
             or state[1][0] == state[1][1] == state[1][2] == playerSymbol != " "
             or state[2][0] == state[2][1] == state[2][2] == playerSymbol != " "
             # Vertical
             or state[0][0] == state[1][0] == state[2][0] == playerSymbol != " "
             or state[0][1] == state[1][1] == state[2][1] == playerSymbol != " "
             or state[0][2] == state[1][2] == state[2][2] == playerSymbol != " "
             # Diagonal
             or state[0][0] == state[1][1] == state[2][2] == playerSymbol != " "
             or state[0][2] == state[1][1] == state[2][0] == playerSymbol != " "):
            return "winner"
        elif (state[0][0] != " " and state[0][1] != " " and state[0][2] != " " and state[1][0] != " " and
              state[1][1] != " " and state[1][2] != " " and state[2][0] != " " and state[2][1] != " " and
              state[2][2] != " "):
            return "draw"

    def getSuccessors(self, symbol):
        successors = []
        for row in range(3):
            for column in range(3):
                if self.state[row][column] == " ":
                    newSuccessor = (self.getNewState(Move(row, column, symbol)), Move(row, column, symbol))
                    successors.append(newSuccessor)
        return successors

    def getNewState(self, move):
        newState = GameState(self.state)
        newState.setMove(move)
        return newState

    def setMove(self, move):
        self.state[move.row][move.column] = move.symbol

    def printBoard(self):
        print "    0 | 1 | 2 "
        print
        print "0   {0} | {1} | {2} ".format(self.state[0][0], self.state[0][1], self.state[0][2])
        print "    --------- "
        print "1   {0} | {1} | {2} ".format(self.state[1][0], self.state[1][1], self.state[1][2])
        print "    --------- "
        print "2   {0} | {1} | {2} ".format(self.state[2][0], self.state[2][1], self.state[2][2])
        print


class Move():
    def __init__(self, row, column, symbol):
        self.row = row
        self.column = column
        self.symbol = symbol

    def __str__(self):
        return "{0} : ({1},{2})".format(self.symbol, self.row, self.column)

    def __repr__(self):
        return self.__str__()


class Player:
    def __init__(self, playerSymbol, opponentSymbol):
        self.playerSymbol = playerSymbol
        self.opponentSymbol = opponentSymbol

    def selectMove(self, turn, state):
        raise NotImplementedError("Error - method must be implemented")

    def getPlayerSymbol(self):
        return self.playerSymbol


class HumanPlayer(Player):
    def selectMove(self, turn, game):
        state = game.gameState.state
        valid = False
        while valid is False:
            move = raw_input("Select row and column for next move (eg. 1 2): ")
            moves = move.split(" ")
            moves[0] = int(moves[0])
            moves[1] = int(moves[1])
            if len(moves) is 2 and 0 <= moves[0] < 3 and 0 <= moves[1] < 3:
                if state[moves[0]][moves[1]] == " ":
                    state[moves[0]][moves[1]] = self.playerSymbol
                    valid = True
            if valid is False:
                print "Invalid input"


class ComputerPlayer(Player):
    def selectMove(self, turn, game):
        successor, move = self.value(self.playerSymbol, game.gameState)
        game.gameState.state[move.row][move.column] = self.playerSymbol

    def value(self, turn, state):
        if state.checkWinner(self.playerSymbol) == "draw":
            return 0, None
        elif state.checkWinner(self.playerSymbol) == "winner":
            return 1, None
        elif state.checkWinner(self.opponentSymbol) == "winner":
            return -1, None
        else:
            if turn == self.playerSymbol:
                return self.maxValue(self.playerSymbol, state)
            else:
                return self.minValue(self.opponentSymbol, state)

    def maxValue(self, turn, state):
        value = -sys.maxsize - 1
        move = None
        for (successor, newMove) in state.getSuccessors(turn):
            successorValue = self.value(self.opponentSymbol, successor)[0]
            if successorValue > value:
                value = successorValue
                move = newMove
            # value = max(value, self.value(self.opponentSymbol, successor[0]))
        return value, move

    def minValue(self, turn, state):
        value = sys.maxsize
        move = None
        for (successor, newMove) in state.getSuccessors(turn):
            successorValue = self.value(self.playerSymbol, successor)[0]
            if successorValue < value:
                value = successorValue
                move = newMove
        # for successor in state.getSuccessors(turn):
        #     value = min(value, self.value(self.playerSymbol, successor))
        return value, move

#Test
def test():
    p1 = ComputerPlayer("X", "O")
    p2 = ComputerPlayer("O", "X")

    # Test Win
    testGame = Game([p1, p2])
    testGame.gameState.setMove(Move(0, 0, "X"))
    testGame.gameState.setMove(Move(0, 1, "O"))
    testGame.gameState.setMove(Move(1, 1, "X"))
    testGame.gameState.setMove(Move(2, 1, "O"))
    testGame.gameState.printBoard()
    print "VALUE: ", p1.value("X", testGame.gameState)

    # Test Loss
    testGame = Game([p1, p2])
    testGame.gameState.setMove(Move(0, 0, "X"))
    testGame.gameState.setMove(Move(0, 1, "O"))
    testGame.gameState.setMove(Move(1, 0, "X"))
    testGame.gameState.setMove(Move(2, 1, "O"))
    testGame.gameState.setMove(Move(2, 2, "X"))
    testGame.gameState.printBoard()
    print "VALUE: ", p1.value("O", testGame.gameState)

    # Test Draw
    testGame = Game([p1, p2])
    testGame.gameState.setMove(Move(0, 0, "X"))
    testGame.gameState.setMove(Move(1, 1, "O"))
    testGame.gameState.setMove(Move(2, 2, "X"))
    testGame.gameState.setMove(Move(1, 2, "O"))
    testGame.gameState.setMove(Move(1, 0, "X"))
    testGame.gameState.setMove(Move(2, 0, "O"))
    testGame.gameState.printBoard()
    print "VALUE: ", p1.value("X", testGame.gameState)

    # Test New Game - Player X
    testGame = Game([p1, p2])
    print "VALUE: ", p1.value("X", testGame.gameState)

    # Test New Game - Player O
    testGame = Game([p1, p2])
    print "VALUE: ", p1.value("O", testGame.gameState)

    # Test
    testGame = Game([p1, p2])
    testGame.gameState.setMove(Move(1, 1, "X"))
    testGame.gameState.setMove(Move(0, 0, "O"))
    testGame.gameState.setMove(Move(1, 0, "X"))
    testGame.gameState.printBoard()
    print "VALUE: ", p1.value("O", testGame.gameState)


def main():
    test()

    p1 = HumanPlayer("X", "O")
    p2 = ComputerPlayer("O", "X")
    game = Game([p1, p2])
    game.play()


if __name__ == "__main__":
    main()