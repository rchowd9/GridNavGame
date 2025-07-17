#ifndef TEXTGAMES_HPP
#define TEXTGAMES_HPP

#include <vector>    // For std::vector
#include <iostream>  // For std::cout, std::endl
#include <cstdlib>   // For rand, srand
#include <ctime>     // For time (used with srand)
#include <cctype>    // For tolower
#include <queue>     // For std::queue in BFS

// Constants for grid elements
const int EMPTY_SPACE =0;
const int WALL =2;
const int PLAYER = 3; // (Not directly used in grid cell values, but conceptually for display)
const int TARGET = 4;
const int COLLECTIBLE = 5; // --- NEW: Constant for collectibles ---

class GameObject
{
private:
    std::vector<std::vector<int>> grid;
    int sizeGridX, sizeGridY;
    int PlayerX, playerY;
    int goalX, goalY;

    int moveCount;
    int health;
    int score; // --- NEW: Score for collectibles ---

    // --- NEW: Helper for BFS pathfinding ---
    bool isPathExist(int startX, int startY, int endX, int endY);

public:
    GameObject(int sizeX, int sizeY);
    void display();
    void placeObstacles(int numObstacles, int numCollectibles); // --- MODIFIED: Added numCollectibles parameter ---
    void movePlayer(char direction);

    // Getters
    int getPlayerX() const { return PlayerX; }
    int getPlayerY() const { return playerY; }
    int getGoalX() const { return goalX; }
    int getGoalY() const { return goalY; }
    int getMoveCount() const { return moveCount; }
    int getHealth() const { return health; }
    int getScore() const { return score; } // --- NEW: Getter for score ---
};

#endif // TEXTGAMES_HPP 