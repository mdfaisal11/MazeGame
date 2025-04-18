This is a console-based maze game where you control a player (P) navigating a randomly generated maze. The goal is to collect items (*), avoid enemies (X), and reach the exit (E) to win. The game includes real-time movement, color output, score tracking, and a save feature.

1. Maze Generation
•	The maze uses a 20x20 grid (set via the SIZE constant).
•	The outer borders (#) are solid walls.
•	The inner area contains:
o	Empty spaces ( )
o	Collectibles (*), randomly placed with a 1-in-8 chance.
•	The player starts at position (1,1).
•	The exit is at (18,18) (bottom-right corner inside the walls).
•	The number of enemies (X) increases with levels, starting at 3 + level * 2.

2. Game Entities
•	Player (P):
o	Controlled using WASD keys.
o	Can move freely unless blocked by a wall.
o	Collects collectibles and tries to reach the exit.
•	Walls (#):
o	Surround the maze.
o	Block movement.
•	Collectibles (*):
o	Give +10 points when collected.
•	Enemies (X):
o	Move randomly each turn.
o	Touching one ends the game.
•	Exit (E):
o	Reaching it completes the level and generates a new maze.

3. Game Mechanics
•	Movement:
o	Player uses W, A, S, D.
o	Enemies move in random directions.
•	Collision Handling:
o	Walls (#): Cannot be moved through.
o	Collectibles (*): Picked up, score increases.
o	Enemies (X): If player collides — Game Over.
•	Scoring:
o	+10 points for each collectible.
•	Winning Condition:
o	Reach the Exit (E).
•	Losing Condition:
o	Collide with an Enemy (X).

4. Special Features
•	Real-Time Input:
o	Uses _getch() to read movement keys instantly.
•	Screen Refresh:
o	Uses \x1B[H (ANSI escape code) for smooth updates (less flickering).
•	Color Output:
o	Player = Green, Enemy = Red, Exit = Blue, Collectibles = Yellow.
•	Save System:
o	Press Q anytime to save game state to maze.txt.
•	OOP Design:
o	Clean separation using Entity, Enemy, and Game classes.

 How to Play
Controls
•	W: Move Up
•	A: Move Left
•	S: Move Down
•	D: Move Right
•	Q: Save and Quit

Game Flow
1.	Launch the game, choose 1 to play or 2 to exit.
2.	Maze is randomly generated:
o	Player (P), Collectibles (*), Enemies (X), Exit (E) placed.
3.	Navigate the player to the exit while:
o	Collecting * for points.
o	Avoiding enemies.
4.	Game ends when:
o	Player reaches the Exit (win, level up).
o	Player collides with an Enemy (lose).
o	Player presses Q (save and quit).

Technical Details
•	Grid: Implemented as a 2D vector<vector<char>> (grid).
•	Enemy Movement:
o	Randomly selected direction (up, down, left, right).
o	Movement only valid if the cell is empty.
•	Display:
o	Clears and redraws the screen after each move.
•	File I/O:
o	Saves full maze layout, player/enemy positions, score, and state to maze.txt.

 Code Structure
1. Entity Class
•	Base class for movable entities.
•	Stores x, y position.
•	Declares a pure virtual move() method for polymorphic behavior.
2. Enemy Class
•	Inherits from Entity.
•	Implements random movement logic.
•	Updates the grid to reflect new positions.
3. Game Class
•	Central class for the entire game.
•	Responsibilities include:
o	Maze generation
o	Player/enemy movement
o	Grid display and color output
o	Score tracking and level progression
o	File saving (saveGame())

