Explanation:
This is a console-based maze game where you control a player (P) to navigate through a randomly generated maze, collect items (Collectibles), avoid enemies (X), and reach the exit (E). The game features real-time movement, score tracking, and the ability to save your progress.
Game Features
1. Maze Generation
•	The maze is a 10x10 grid (adjustable via the SIZE constant)
•	Outer borders are solid Walls
•	Inner spaces randomly contain Collectibles (with a 1 in 8 chance)
•	The player starts at position (1,1) — top-left corner inside the walls
•	The exit is at position (SIZE-2,SIZE-2) — bottom-right corner inside the walls
•	4 Enemies are randomly placed in empty spaces
2. Game Entities
•	Player (P): Controlled by the user using WASD keys
•	Walls: Impassable barriers
•	Collectibles: Worth 10 points each when collected
•	Enemies (X): Move randomly each turn, game ends if they touch the player
•	Exit (E): Winning condition — game ends successfully when reached
3. Game Mechanics
•	Movement: Players and enemies can move up, down, left, or right
•	Collision:
o	Walls block movement
o	Collectibles are picked up when moved over
o	Enemies trigger game over on contact
•	Scoring: Each Collectible gives +10 points
•	Win Condition: Reach the Exit
•	Lose Condition: Touch an Enemy
4. Special Features
•	Real-time Input: Uses _getch() to read keys without needing Enter
•	Screen Refresh: Uses ANSI escape codes to clear/update the display
•	Save System: Can save game state to "maze.txt" (press Q)
•	Object-Oriented Design: Uses classes for game entities and logic
How to Play
Controls
•	W: Move Up
•	A: Move Left
•	S: Move Down
•	D: Move Right
•	Q: Save Game and Exit
Game Flow
1.	At startup, choose option 1 to play or 2 to exit
2.	The maze generates with random Walls, Collectibles, and Enemy positions
3.	Navigate your Player (P) to the Exit (E) while:
o	Collecting Collectibles for points
o	Avoiding Enemies (X) that move randomly each turn
4.	The game ends when you:
o	Reach the Exit (win)
o	Touch an Enemy (lose)
o	Press Q to save and quit
Technical Details
•	The game uses a 2D vector (grid) to represent the maze state
•	Enemy movement is randomized but validated to prevent wall-clipping
•	The display updates after each move to show new positions
•	Game state (maze layout, positions, score) can be saved to file
Code Structure
1.	Entity Class: Base class for all moving objects
o	Tracks position (x, y)
o	Defines pure virtual move() function
2.	Enemy Class: Inherits from Entity
o	Implements random movement algorithm
o	Updates grid when moving
3.	Game Class: Manages all game components
o	Maze generation
o	Player movement
o	Game state tracking
o	Display rendering
o	File I/O for saving
Potential Enhancements
1.	Add multiple levels with increasing difficulty
2.	Implement power-ups or special abilities
3.	Add a time limit or move counter
4.	Improve enemy AI (pathfinding toward player)
5.	Add sound effects and more visual feedback

# MazeGame
