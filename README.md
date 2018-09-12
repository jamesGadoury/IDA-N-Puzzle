# IDA-N-Puzzle
Application of iterative depth a * search used to solve classic N puzzle. Can solve 9, 15, and 24 puzzles.

First line of input is N, followed by N x N lines of input of N puzzle that needs to be solved
Output is whether or not goal was reached, followed by number of moves required, followed by the moves required, followed by finished board

Example:

Input:
3
3
2
5
0
1
7
6
4
8

Output:
goal reached
17
RIGHT
RIGHT
DOWN
LEFT
UP
LEFT
DOWN
RIGHT
RIGHT
UP
UP
LEFT
DOWN
DOWN
LEFT
UP
UP
 0  1  2 
 3  4  5 
 6  7  8 
