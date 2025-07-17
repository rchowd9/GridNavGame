#include "textgames.hpp"
#include <iostream>
#include <cctype>
#include <cstdlib>
#include <ctime>
#include <limits> // For std::numeric_limits

int main()
{
    srand(static_cast<unsigned int>(time(0)));

    int sizeX = 10, sizeY = 10;
    GameObject game(sizeX, sizeY);

    int numObstacles = 15; // Number of walls to attempt to place
    int numCollectibles = 5; // Number of collectibles to place
    game.placeObstacles(numObstacles, numCollectibles); // --- MODIFIED: Added numCollectibles ---

    bool gameOver = false;

    while (!gameOver)
    {
        game.display();

        char move;
        std::cout << "Enter move (W/A/S/D): ";
        std::cin >> move;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear buffer

        game.movePlayer(tolower(move));

        // Check for winning condition
        if (game.getPlayerX() == game.getGoalX() && game.getPlayerY() == game.getGoalY()) {
            gameOver = true;
            game.display();
            std::cout << "\n********************************************\n";
            std::cout << " CONGRATULATIONS! You've reached the target!\n";
            std::cout << " Total Moves: " << game.getMoveCount() << "\n";
            std::cout << " Your Score: " << game.getScore() << "\n"; // --- NEW: Display score on win ---
            std::cout << "********************************************\n";
        }
        // Check for losing condition
        else if (game.getHealth() <= 0) {
            gameOver = true;
            game.display();
            std::cout << "\n********************************************\n";
            std::cout << " GAME OVER! You ran out of health.\n";
            std::cout << " You made " << game.getMoveCount() << " moves.\n";
            std::cout << " Your Score: " << game.getScore() << "\n"; // --- NEW: Display score on lose ---
            std::cout << " Better luck next time!\n";
            std::cout << "********************************************\n";
        }
    }

    std::cout << "\nThanks for playing!\n";
    return 0;
} 