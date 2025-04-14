#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <conio.h>      // For capturing user input without Enter key
#include <fstream>      // For reading/writing to files

using namespace std;

const int SIZE = 10;    // Size of the maze grid (10x10)

// Entity base class
// Represents any object that occupies space in the maze.
// Can be extended to define specific behavior (like enemy movement).
class Entity {
protected:
    int x, y;   // Coordinates of the entity in the maze
public:
    Entity(int startX, int startY) : x(startX), y(startY) {}
    virtual void move(vector<vector<char>>& grid) = 0;  // Pure virtual function for movement
    int getX() { return x; }
    int getY() { return y; }
};

// Enemy class (inherits from Entity)
// Randomly moves around the maze and ends the game if it touches the player
class Enemy : public Entity {
public:
    Enemy(int startX, int startY) : Entity(startX, startY) {}
    void move(vector<vector<char>>& grid) override;
};

// Game class
// Manages the maze, player, enemies, score, game logic, and display
class Game {
private:
    vector<vector<char>> grid;   // 2D grid representing the maze
    int playerX, playerY;        // Player's position
    int exitX, exitY;            // Exit position
    int score;                   // Player's score
    bool gameOver;               // Flag to track game state
    vector<Enemy*> enemies;      // List of dynamically created enemies

public:
    Game();
    ~Game();

    void generateMaze();                 // Generates walls, collectibles, player, exit, and enemies
    void displayMaze();                  // Displays the current maze
    void movePlayer(char direction);     // Handles player movement
    void playGame();                     // Main game loop
    void saveMaze();                     // Saves current game state to file
    void loadMaze();                     // (Unused here but declared for future expansion)
};

// Constructor: Set initial game state
Game::Game() {
    playerX = 1; playerY = 1;
    exitX = SIZE - 2; exitY = SIZE - 2;
    score = 0;
    gameOver = false;
    grid.resize(SIZE, vector<char>(SIZE, ' '));
}

// Destructor: Delete all enemies from heap
Game::~Game() {
    for (auto enemy : enemies) {
        delete enemy;
    }
}

// generateMaze(): Builds new maze layout with walls, enemies, collectibles
void Game::generateMaze() {
    srand(time(0)); // Seed RNG

    // Fill grid with walls on borders and space inside
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (i == 0 || i == SIZE - 1 || j == 0 || j == SIZE - 1)
                grid[i][j] = '#'; // Maze boundary
            else
                grid[i][j] = (rand() % 8 == 0) ? '*' : ' '; // Random collectibles or empty space
        }
    }

    // Place player and exit
    grid[playerX][playerY] = 'P';
    grid[exitX][exitY] = 'E';

    // Add random enemies to the maze
    for (int i = 0; i < 4; i++) {
        int ex = rand() % (SIZE - 2) + 1;
        int ey = rand() % (SIZE - 2) + 1;
        if (grid[ex][ey] == ' ') {
            grid[ex][ey] = 'X';
        }
    }
}

// displayMaze(): Print the current state of the maze
void Game::displayMaze() {
    cout << "\x1B[H"; // Moves cursor to top-left (for smoother screen updates)
    for (const auto& row : grid) {
        for (char cell : row) {
            cout << cell << " ";
        }
        cout << endl;
    }
    cout << "Score: " << score << "\n";
}

// movePlayer(): Update player position based on input
void Game::movePlayer(char direction) {
    int newX = playerX, newY = playerY;

    // Determine direction
    switch (direction) {
        case 'W': newX--; break;
        case 'S': newX++; break;
        case 'A': newY--; break;
        case 'D': newY++; break;
    }

    // Blocked by wall
    if (grid[newX][newY] == '#') return;

    // Collect collectible
    if (grid[newX][newY] == '*') {
        score += 10;
    }

    // Hit enemy
    if (grid[newX][newY] == 'X') {
        gameOver = true;
        cout << "Game Over! You were caught by an enemy.\n";
        return;
    }

    // Move player
    grid[playerX][playerY] = ' ';
    playerX = newX;
    playerY = newY;
    grid[playerX][playerY] = 'P';

    // Reached the exit
    if (playerX == exitX && playerY == exitY) {
        gameOver = true;
        cout << "Congratulations! You reached the exit!\n";
    }
}

// saveMaze(): Save maze layout and player state to a text file
void Game::saveMaze() {
    ofstream file("maze.txt");
    if (!file) {
        cerr << "Error saving the maze!" << endl;
        return;
    }

    // Save grid layout
    for (const auto& row : grid) {
        for (char cell : row) {
            file << cell;
        }
        file << "\n";
    }

    // Save game state
    file << playerX << " " << playerY << "\n";
    file << exitX << " " << exitY << "\n";
    file << score << "\n";
    file << gameOver << "\n";

    file.close();
    cout << "Game saved successfully!\n";
}

// playGame(): Runs the main game loop until player wins or loses
void Game::playGame() {
    while (!gameOver) {
        displayMaze();
        cout << "Use W, A, S, D to move. Reach 'E' to win. Press Q to save and exit.\n";

        char input = _getch(); // Read a single character
        if (toupper(input) == 'Q') {
            saveMaze();
            break;
        }

        movePlayer(toupper(input));

        // Move each enemy after player moves
        for (auto& enemy : enemies) {
            enemy->move(grid);
        }

        // Auto-save on game over
        if (gameOver) {
            saveMaze();
        }
    }
}

// Enemy::move(): Move enemies randomly if next space is walkable
void Enemy::move(vector<vector<char>>& grid) {
    int direction = rand() % 4;
    int newX = x, newY = y;

    // Choose a random direction
    switch (direction) {
        case 0: newX--; break;
        case 1: newX++; break;
        case 2: newY--; break;
        case 3: newY++; break;
    }

    // Move only if next cell is walkable (empty)
    if (grid[newX][newY] == ' ') {
        grid[x][y] = ' ';        // Clear old position
        x = newX; y = newY;      // Update position
        grid[x][y] = 'X';        // Mark new enemy position
    }
}


// main(): Game entry point
int main() {
    Game game;
    char ch;

    cout << "Welcome to Maze Game!\n";
    cout << "1. Play Game\n";
    cout << "2. Exit\n";
    cout << "Enter choice: ";
    cin >> ch;

    if (ch == '1') {
        game.generateMaze();  // Set up maze
    } else {
        cout << "Exiting the game. Goodbye!\n";
        return 0;
    }

    game.playGame(); // Start gameplay
    return 0;
}
