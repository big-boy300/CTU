"""
The purpose of the task is to create a player who will participate in
Reversi(https://en.wikipedia.org/wiki/Reversi) tournament. 

Implemented player analyzes the playing board(which is represented as a 2D array) 
and uses local maximization strategy.

Result: the first third of a ranking table.
"""

ROWS = 8
COLUMNS = 8
FREE_SPACE = -1
ALL_DIRECTIONS = ((-1,-1), (-1,0), (-1,1), (0,-1), (0,1), (1,-1), (1,0), (1,1))
BOARD_VALUES = {(0,0):120, (0,1):-20, (0,2):20, (0,3):5,  (0,4):5,  (0,5):20, (0,6):-20, (0,7):120,
                (1,0):-20, (1,1):-40, (1,2):-5, (1,3):-5, (1,4):-5, (1,5):-5, (1,6):-40, (1,7):-20,
                (2,0):20,  (2,1):-5,  (2,2):15, (2,3):3,  (2,4):3,  (2,5):15, (2,6):-5,  (2,7):20,
                (3,0):5,   (3,1):-5,  (3,2):3,  (3,3):3,  (3,4):3,  (3,5):3,  (3,6):-5,  (3,7):5,
                (4,0):5,   (4,1):-5,  (4,2):3,  (4,3):3,  (4,4):3,  (4,5):3,  (4,6):-5,  (4,7):5,
                (5,0):20,  (5,1):-5,  (5,2):15, (5,3):3,  (5,4):3,  (5,5):15, (5,6):-5,  (5,7):20,
                (6,0):-20, (6,1):-40, (6,2):-5, (6,3):-5, (6,4):-5, (6,5):-5, (6,6):-40, (6,7):-20,
                (7,0):120, (7,1):-20, (7,2):20, (7,3):5,  (7,4):5,  (7,5):20, (7,6):-20, (7,7):120
               }
 
class MyPlayer:
    """Player chooses the move with the highest value."""
    def __init__(self, my_color, opponent_color):
        self.name = 'danilrom'
        self.my_color = my_color
        self.opponent_color = opponent_color
        self.possible_moves = []
 
    def find_position(self, board):
        for row in range(ROWS):
            for col in range(COLUMNS):
                if board[row][col] == self.my_color:
                    self.find_possible_moves(board, row, col)
 
    def find_possible_moves(self, board, row, col):
        for direction in ALL_DIRECTIONS:
            counter = 1
            r = row + direction[0]
            c = col + direction[1]
            if is_on_board(r,c):
                if board[r][c] == self.opponent_color:
                    while is_on_board(r,c) and board[r][c] == self.opponent_color:
                        counter += 1
                        r = row + direction[0] * counter 
                        c = col + direction[1] * counter
 
                    if is_on_board(r,c) and board[r][c] == FREE_SPACE:
                        if (r, c) not in self.possible_moves:
                            self.possible_moves.append((r,c))
 
    def move_based_on_value(self, board):
        self.find_position(board)
        values = []
        for value in self.possible_moves:
            values.append(BOARD_VALUES.get(value))
        self.best_moves = []
        for move in self.possible_moves:
            for key in BOARD_VALUES:
                if max(values) == BOARD_VALUES[move] and move in BOARD_VALUES:
                    if move not in self.best_moves:
                        self.best_moves.append(move)
                        break
     
    def move(self, board):
        self.possible_moves = []
        self.best_moves = []
        self.move_based_on_value(board)
        if len(self.best_moves) > 0:
            return (self.best_moves[0][0], self.best_moves[0][1])
        else:
            return None
 
def is_on_board(r, c):
    return 0 <= r <= 7 and 0 <= c <= 7
