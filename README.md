Introduction
This project is a 2D maze game developed in C++. It runs in the console and includes key features such as player navigation, enemy AI that moves randomly, collectible items, and level progression. Additionally, it allows the game state to be saved to a text file, which is helpful for continuing later.

Libraries and Constants
To build this game, we’ve used multiple standard C++ libraries:
- `iostream` for input and output,
- `vector` for managing the 2D grid,
- `ctime` to generate random directions for enemy movement,
- `conio.h` to detect keyboard inputs without pressing Enter,
- and `fstream` for reading and writing the game state to a file.

We’ve also used ANSI escape sequences to color different elements in the console, making the game visually clearer.

Entity Class (Base Class)
This is the base class for all moving entities in the game, like the player and enemies. It holds their `x` and `y` positions and has a virtual `move()` function. This allows us to define unique movement logic for enemies and potentially other future entities by overriding this function in derived classes.

Enemy Class
The `Enemy` class inherits from `Entity`. It implements the `move()` function, allowing the enemy to move randomly in one of four directions. But it only moves if the next space is empty. This prevents enemies from walking through walls or overlapping each other.

Game Class - Overview
This class handles the entire game logic. It maintains the grid (the maze), tracks the player and exit positions, and manages the score, level, and game status. It also holds a dynamic list of enemies that interact with the player during the game.

Maze Generation
Every time a level is started or completed, a new maze is generated. The grid is filled with walls on the borders, and collectibles are placed randomly. Enemies are also added depending on the level. The maze always ensures the player starts at the top-left, and the exit is near the bottom-right.

Displaying the Maze
"The game uses a color-coded display in the console for better visibility. Players, enemies, exits, walls, and collectibles are each shown in different colors. The maze is printed row by row, and the current level and score are shown at the bottom."

Player Movement
The `movePlayer()` function handles movement using `W`, `A`, `S`, and `D` keys. The player can’t go through walls. If the player touches a collectible, the score increases. If they touch an enemy, it’s game over. Reaching the exit moves the player to the next level, where a new maze is generated.

Game Loop
The core gameplay happens in the `playGame()` loop. It continues until the game is over. In each cycle, it displays the maze, waits for a keypress, moves the player accordingly, and then moves the enemies. Pressing 'Q' allows the user to save and quit.

Saving the Game
When the player presses 'Q' or loses, the game is saved to a file called `maze.txt`. This file stores the entire grid, player and exit positions, current score, and whether the game is over. This allows players to resume where they left off.

Main Function
The `main()` function is the starting point of the game. It displays a menu where users can either play or exit. If they choose to play, the game loop begins.

Summary
In summary, this project applies Object-Oriented Programming concepts like inheritance and polymorphism. It uses real-time key detection, file handling, and randomized behavior for enemies. The code is modular, which makes it easy to extend in the future with more features.
