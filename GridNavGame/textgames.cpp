#include "textgames.hpp"
#include <algorithm>
#include <queue>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <limits>

using namespace std;

// --- NEW: BFS Pathfinding Helper Method ---
bool GameObject::isPathExist(int startX, int startY, int endX, int endY) {
    // If start or end is a wall, no path exists
    if (grid[startY][startX] == WALL || grid[endY][endX] == WALL) {
        return false;
    }
    // If start is target, path exists (length 0)
    if (startX == endX && startY == endY) {
        return true;
    }

    // BFS setup
    queue<pair<int, int>> q;
    vector<vector<bool>> visited(sizeGridY, vector<bool>(sizeGridX, false));

    q.push({startY, startX});
    visited[startY][startX] = true;

    // Directions for 4-directional movement (up, down, left, right)
    int dy[] = {-1, 1, 0, 0};
    int dx[] = {0, 0, -1, 1};

    while (!q.empty()) {
        pair<int, int> current = q.front();
        q.pop();

        int y = current.first;
        int x = current.second;

        // Explore neighbors
        for (int i = 0; i < 4; ++i) {
            int ny = y + dy[i];
            int nx = x + dx[i];

            // Check bounds
            if (nx >= 0 && nx < sizeGridX && ny >= 0 && ny < sizeGridY) {
                // If not visited and not a wall
                if (!visited[ny][nx] && grid[ny][nx] != WALL) {
                    if (nx == endX && ny == endY) {
                        return true; // Target reached
                    }
                    visited[ny][nx] = true;
                    q.push({ny, nx});
                }
            }
        }
    }
    return false; // Target not reachable
}

GameObject::GameObject(int sizeX, int sizeY)
{
    sizeGridX = sizeX;
    sizeGridY = sizeY;
    grid.resize(sizeGridY, vector<int>(sizeGridX, EMPTY_SPACE));

    PlayerX = 0;
    playerY = 0;
    goalX = sizeGridX - 1;
    goalY = sizeGridY - 1;

    grid[goalY][goalX] = TARGET; // Place target at bottom-right

    moveCount = 0;
    health = 3;
    score = 0; // --- NEW: Initialize score ---
}

void GameObject::display()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

    // --- MODIFIED: Display Score along with Health and Moves ---
    cout << "Health: " << health << " | Moves: " << moveCount << " | Score: " << score << endl;
    cout << "--------------------" << endl;

    for (int y = 0; y < sizeGridY; y++)
    {
        for (int x = 0; x < sizeGridX; x++)
        {
            if (x == PlayerX && y == playerY)
                cout << "P ";
            else if (grid[y][x] == TARGET)
                cout << "T ";
            else if (grid[y][x] == WALL)
                cout << "# ";
            else if (grid[y][x] == COLLECTIBLE) // --- NEW: Display collectibles ---
                cout << "C ";
            else
                cout << ". ";
        }
        cout << endl;
    }
    cout << "--------------------" << endl;
}

// --- MODIFIED: placeObstacles now takes numCollectibles ---
void GameObject::placeObstacles(int numObstacles, int numCollectibles)
{
    // --- Part 1: Place Walls with Solvability Guarantee ---
    int wallsPlaced = 0;
    while (wallsPlaced < numObstacles)
    {
        int x = rand() % sizeGridX;
        int y = rand() % sizeGridY;

        // Attempt to place a wall if the space is empty and not player/target
        if (grid[y][x] == EMPTY_SPACE && !(x == PlayerX && y == playerY) && !(x == goalX && y == goalY))
        {
            grid[y][x] = WALL; // Temporarily place wall

            // Check if maze is still solvable with this new wall
            if (isPathExist(PlayerX, playerY, goalX, goalY)) {
                wallsPlaced++; // Path still exists, keep the wall
            } else {
                grid[y][x] = EMPTY_SPACE; // Path blocked, remove the wall
            }
        }
    }

    // --- Part 2: Place Collectibles ---
    int collectiblesPlaced = 0;
    while (collectiblesPlaced < numCollectibles)
    {
        int x = rand() % sizeGridX;
        int y = rand() % sizeGridY;

        // Ensure collectibles are placed only on empty spaces, not player/target/walls
        if (grid[y][x] == EMPTY_SPACE && !(x == PlayerX && y == playerY) && !(x == goalX && y == goalY))
        {
            grid[y][x] = COLLECTIBLE;
            collectiblesPlaced++;
        }
    }
}

void GameObject::movePlayer(char direction)
{
    int newX = PlayerX;
    int newY = playerY;

    if (direction == 'w') newY--;
    else if (direction == 's') newY++;
    else if (direction == 'a') newX--;
    else if (direction == 'd') newX++;
    else
    {
        cout << "Invalid move. Use 'w', 'a', 's', 'd' to move." << endl;
        return;
    }

    if (newX < 0 || newX >= sizeGridX || newY < 0 || newY >= sizeGridY)
    {
        cout << "Move out of bounds! You cannot go that way." << endl;
        return;
    }

    // --- NEW: Handle collecting an item (must be checked BEFORE wall collision) ---
    if (grid[newY][newX] == COLLECTIBLE) {
        score++; // Increment score
        grid[newY][newX] = EMPTY_SPACE; // Remove the collectible from the grid
        PlayerX = newX; // Update player position
        playerY = newY;
        moveCount++; // Count as a successful move
        cout << "You collected a coin! Current Score: " << score << endl;
        return; // Move handled, no further checks needed for this step
    }

    if( grid[newY][newX] == WALL)
    {
        health--;
        cout << "Ouch! You hit a wall and lost 1 health! Remaining health: " << health << endl;
        return;
    }

    // If the move is valid and not into a wall, update player position
    PlayerX = newX;
    playerY = newY;
    moveCount++;

    if (!(PlayerX == goalX && playerY == goalY))
    {
        cout << "You moved to (" << PlayerX << ", " << playerY << ")." << endl;
    }
} 