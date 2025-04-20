#include <iostream>     // For input/output
#include <vector>       // For using 2D vector grid
#include <ctime>        // For random enemy movement
#include <conio.h>      // For reading keypress (_getch)
#include <fstream>      // For saving game state

using namespace std;
// Set maze size (constant size for grid)
int SIZE = 20;
// Define colors using ANSI escape sequences
#define RESET_COLOR "\x1B[0m"
#define PLAYER_COLOR "\x1B[32m" // Green for player
#define WALL_COLOR "\x1B[31m"   // Red for walls
#define ENEMY_COLOR "\x1B[31m"  // Red for enemies
#define EXIT_COLOR "\x1B[34m"   // Blue for exit
#define COLLECTIBLE_COLOR "\x1B[33m"  // Yellow for collectibles

// This is the base class for all entities like the player and enemies.
class Entity
{
protected:
    int x, y;  // Position of entity (x and y coordinates)

public:
    // Constructor to initialize position of the entity
    Entity(int startX, int startY)
    {
        x = startX;
        y = startY;
    }

    // Virtual method for movement, needs to be overridden by derived classes
    virtual void move(vector<vector<char>>& grid) = 0;

    // Getter for X position
    int getX()
    {
        return x;
    }

    // Getter for Y position
    int getY()
    {
        return y;
    }
};

// Enemy class inherits from Entity. It represents the enemies in the game.
class Enemy : public Entity
{
public:
    // Constructor that passes start positions to the Entity class
    Enemy(int startX, int startY) : Entity(startX, startY) {}

    // Overriden method to move the enemy randomly
    void move(vector<vector<char>>& grid) override
    {
        int direction = rand() % 4; // Randomly choose one of the 4 directions
        int newX = x;
        int newY = y;

        // 0-Up, 1-Down, 2-Left, 3-Right
        if (direction == 0) newX--;  // Move up
        else if (direction == 1) newX++;  // Move down
        else if (direction == 2) newY--;  // Move left
        else if (direction == 3) newY++;  // Move right

        // Move only if the new position is empty
        if (grid[newX][newY] == ' ')
        {
            grid[x][y] = ' ';    // Clear old position
            x = newX;            // Update position
            y = newY;
            grid[x][y] = 'X';    // Place enemy in new position
        }
    }
};

// This is the main game class which handles the game mechanics and logic.
class Game
{
private:
    vector<vector<char>> grid; // 2D grid representing the maze
    int playerX, playerY;      // Player position (x and y)
    int exitX, exitY;          // Exit position (x and y)
    int score;                 // Player's score
    int level;                 // Current level
    bool gameOver;             // Flag to track if the game is over
    vector<Enemy*> enemies;    // List of enemies in the game

public:
    // Constructor: Initializes the game with default values
    Game()
    {
        srand(time(0));         // Seed for random number generation (for random enemy movement)
        grid.resize(SIZE, vector<char>(SIZE, ' ')); // Create grid with empty spaces
        playerX = 1; // Player's starting X position
        playerY = 1; // Player's starting Y position
        exitX = SIZE - 2;  // Exit's X position (near bottom-right corner)
        exitY = SIZE - 2;  // Exit's Y position (near bottom-right corner)
        score = 0; // Initial score
        level = 1; // Initial level
        gameOver = false; // The game is not over initially
    }

    // Destructor: Cleans up the dynamically allocated memory for enemies
    ~Game()
    {
        for (auto enemy : enemies)
        {
            delete enemy; // Delete each enemy object
        }
    }

    // Method to generate a new maze
    void generateMaze()
    {
        playerX = 1;
        playerY = 1;
        enemies.clear(); // Clear the previous enemies list

        // Fill grid with walls ('#'), empty spaces (' '), and collectibles ('*')
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                if (i == 0 || j == 0 || i == SIZE - 1 || j == SIZE - 1)
                    grid[i][j] = '#'; // Set walls at the borders
                else if (rand() % 8 == 0)
                    grid[i][j] = '*'; // Randomly place collectibles
                else
                    grid[i][j] = ' '; // Empty space
            }
        }

        // Set the player's initial position (P) and the exit position (E)
        grid[playerX][playerY] = 'P'; // Player
        grid[exitX][exitY] = 'E'; // Exit

        // Add enemies (more enemies appear as the level increases)
        int enemyCount = 3 + level * 2; // Number of enemies increases with the level
        for (int i = 0; i < enemyCount; i++)
        {
            int ex, ey;
            do
            {
                ex = rand() % (SIZE - 2) + 1;  // Random X position (within bounds)
                ey = rand() % (SIZE - 2) + 1;  // Random Y position (within bounds)
            }
        while (grid[ex][ey] != ' '); // Ensure enemy is placed on an empty space
            grid[ex][ey] = 'X'; // Mark enemy's position on the grid
        }
    }

    // Display the current maze in the console
    void displayMaze()
    {
        cout << "\x1B[H";  // Clear the console (only works on Windows)

        // Print the grid to the console with colors
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                if (grid[i][j] == '#')
                    cout << WALL_COLOR << "# " << RESET_COLOR; // Print wall in red
                else if (grid[i][j] == 'P')
                    cout << PLAYER_COLOR << "P " << RESET_COLOR; // Print player in green
                else if (grid[i][j] == 'X')
                    cout << ENEMY_COLOR << "X " << RESET_COLOR; // Print enemy in red
                else if (grid[i][j] == 'E')
                    cout << EXIT_COLOR << "E " << RESET_COLOR; // Print exit in blue
                else if (grid[i][j] == '*')
                    cout << COLLECTIBLE_COLOR << "* " << RESET_COLOR; // Print collectible in yellow
                else
                    cout << "  "; // Empty space
            }
            cout << endl; // New line after each row
        }

        // Display the current level and score
        cout << "Level: " << level << "  Score: " << score << endl;
    }

    // Move the player based on input (W, A, S, D)
    void movePlayer(char key)
    {
        int newX = playerX;
        int newY = playerY;

        // Change player's position based on the key input
        if (key == 'w') newX--;  // Move up
        else if (key == 's') newX++;  // Move down
        else if (key == 'a') newY--;  // Move left
        else if (key == 'd') newY++;  // Move right

        // Check if the new position is a wall ('#')
        if (grid[newX][newY] == '#') return;

        // Check if the player is collecting an item ('*')
        if (grid[newX][newY] == '*') score += 10;

        // If player collides with an enemy ('X'), game over
        if (grid[newX][newY] == 'X')
        {
            cout << "Game Over caught by an enemy!"<<endl;
            gameOver = true;
            saveGame(); // Save the game state
            return;
        }

        // Move player to the new position
        grid[playerX][playerY] = ' '; // Clear old position
        playerX = newX;  // Update player's X position
        playerY = newY;  // Update player's Y position
        grid[playerX][playerY] = 'P'; // Place player in new position

        // If the player reaches the exit ('E'), level up
        if (playerX == exitX && playerY == exitY)
        {
            level++;  // Increase level
            cout << "Level Complete! Next level loading...\n";
            _sleep(50); // Pause before next level
            generateMaze(); // Generate a new maze for the next level
        }
    }

    // Main game loop
    void playGame()
    {
        generateMaze(); // Generate the first maze

        // Game loop runs until the game is over
        while (!gameOver)
        {
            displayMaze();  // Display the current maze

            // Instructions to the player
            cout << "Use W, A, S, D to move. Reach 'E' to win. Press Q to save and exit."<<endl;

            // Read user input (keypress)
            char input = _getch(); // Non-blocking key input

            if (input == 'q' || input == 'Q')
            {
                saveGame(); // Save game if 'Q' is pressed
                break;  // Exit the game
            }

            // Move the player based on the key pressed
            movePlayer(tolower(input));

            // Move all enemies in the game
            for (auto& enemy : enemies)
            {
                enemy->move(grid); // Move each enemy randomly
            }
        }
    }

    // Save the game state to a file
    void saveGame()
    {
        ofstream file("maze.txt");  // Open the file to save the game state
        if (!file)
        {
            cout << "Error saving game!"<<endl;
            return;  // If file couldn't be opened, print error and exit
        }

        // Save the current grid to the file
        for (auto row : grid)
        {
            for (char cell : row) file << cell;  // Write each cell to file
            file << "\n";  // New line after each row
        }

        // Save player position, exit position, score, and game over flag
        file << playerX << " " << playerY << endl;
        file << exitX << " " << exitY << endl;
        file << score << endl;
        file << gameOver << endl;

        file.close();  // Close the file
        cout << "Game saved to maze.txt"<<endl;
    }
};

// The entry point of the program
int main()
{
    Game myGame;  // Create a Game object

    char choice;
    cout << "MAZE GAME"<<endl;  // Game title
    cout << "1. Play Game"<<endl;  // Option to play
    cout << "2. Exit"<<endl;  // Option to quit
    cout << "Choose option: ";
    cin >> choice;  // Read user's choice

    if (choice == '1')
    {
        myGame.playGame();  // Start the game
    }
    else
    {
        cout << "See You Soon."<<endl;  // Exit message
    }

    return 0;  // End the program
}
