""" 
The purpose of the task was to create a player who will
participate in Iterated Prisoner's Dilemma tournament 
and will maximize profit throughout the tournament.
Payoff matrix is known in the beginning of the game.

Implemented player can remember decisions of his opponent
and decides his move based on them.

Result: the middle of the ranking table.
"""

class MyPlayer:
    """Player cooperates, but revenges if the opponent rejects mutual cooperation"""
    def __init__(self, payoff_matrix, number_of_iterations=None):
        self.payoff_matrix = payoff_matrix
        if self.payoff_matrix[0][0][0] > self.payoff_matrix[1][1][0]:
            self.var = 0
        else:
            self.var = 1
 
        self.number_of_iterations = number_of_iterations
        self.history = 2 * [None]
 
    def move(self):
        if None in self.history:
            self.variant = self.var
        else:
            if self.payoff_matrix[0][0][0] < self.payoff_matrix[1][1][0]:
                self.variant = 1
            else:
                self.variant = self.history[1]
         
        if self.variant == 0:
            return False
        else:
            return True
 
    def record_last_moves(self, my_last_move, opponent_last_move):
        del self.history[0]
        del self.history[-1]
        self.history.insert(0, my_last_move)
        self.history.insert(1, opponent_last_move)
        