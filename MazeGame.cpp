#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <fstream>

using namespace std;

const int SIZE = 10;

class Entity
{
protected:
    int x, y;
public:
    Entity(int startX, int startY) : x(startX), y(startY) {}
    virtual void move(vector<vector<char>>& grid) = 0;
    int getX() { return x; }
    int getY() { return y; }
};

class Enemy :
public Entity
{
public:
    Enemy(int startX, int startY) : Entity(startX, startY) {}
    void move(vector<vector<char>>& grid) override;
};

class Game
{
private:
    vector<vector<char>> grid;
    int playerX, playerY;
    int exitX, exitY;
    int score;
    bool gameOver;
    vector<Enemy*> enemies;
public:
    Game();
    ~Game();
    void generateMaze();
    void displayMaze();
    void movePlayer(char direction);
    void playGame();
    void saveMaze();
    void loadMaze();
};

Game::Game()
{
    playerX = 1; playerY = 1;
    exitX = SIZE - 2; exitY = SIZE - 2;
    score = 0;
    gameOver = false;
    grid.resize(SIZE, vector<char>(SIZE, ' '));
}

Game::~Game()
{
    for (auto enemy : enemies) {
        delete enemy;
    }
}

void Game::generateMaze()
{
    srand(time(0));
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (i == 0 || i == SIZE - 1 || j == 0 || j == SIZE - 1)
                grid[i][j] = '#';
            else
                grid[i][j] = (rand() % 8 == 0) ? '*' : ' ';
        }
    }
    grid[playerX][playerY] = 'P';
    grid[exitX][exitY] = 'E';

    for (int i = 0; i < 4; i++) {
        int ex = rand() % (SIZE - 2) + 1;
        int ey = rand() % (SIZE - 2) + 1;
        if (grid[ex][ey] == ' ') {
            grid[ex][ey] = 'X';
        }
    }
}

void Game::displayMaze()
{
    cout << "\x1B[H"; 
    for (const auto& row : grid) {
        for (char cell : row) {
            cout << cell << " ";
        }
        cout << endl;
    }
    cout << "Score: " << score << "\n";
}

void Game::movePlayer(char direction)
{
    int newX = playerX, newY = playerY;
    switch (direction) {
        case 'W': newX--; break;
        case 'S': newX++; break;
        case 'A': newY--; break;
        case 'D': newY++; break;
    }

    if (grid[newX][newY] == '#') return;

    if (grid[newX][newY] == '*') {
        score += 10;
    }

    if (grid[newX][newY] == 'X') {
        gameOver = true;
        cout << "Game Over! You were caught by an enemy.\n";
        return;
    }

    grid[playerX][playerY] = ' ';
    playerX = newX;
    playerY = newY;
    grid[playerX][playerY] = 'P';

    if (playerX == exitX && playerY == exitY) {
        gameOver = true;
        cout << "Congratulations! You reached the exit!\n";
    }
}

void Game::saveMaze()
{
    ofstream file("maze.txt");
    for (const auto& row : grid) {
        for (char cell : row) {
            file << cell;
        }
        file << "\n";
    }
    file.close();
}

void Game::loadMaze()
{
    ifstream file("maze.txt");
    for (auto& row : grid) {
        for (char& cell : row) {
            file >> cell;
        }
    }
    file.close();
}

void Game::playGame()
{
    generateMaze();
    while (!gameOver) {
        displayMaze();
        cout << "Use W, A, S, D to move. Reach 'E' to win. Press Q to save and exit.\n";
        char input = _getch();
        if (toupper(input) == 'Q') {
            saveMaze();
            break;
        }
        movePlayer(toupper(input));

        for (auto& enemy : enemies) {
            enemy->move(grid);
        }
    }
}

void Enemy::move(vector<vector<char>>& grid)
{
    int direction = rand() % 4;
    int newX = x, newY = y;
    switch (direction) {
        case 0: newX--; break;
        case 1: newX++; break;
        case 2: newY--; break;
        case 3: newY++; break;
    }
    if (grid[newX][newY] == ' ') {
        grid[x][y] = ' ';
        x = newX;
        y = newY;
        grid[x][y] = 'X';
    }
}

int main() {
    Game game;
    game.playGame();
    return 0;
}
