#include "GameBoy.h"
#include "Game.h"

GameBoy::GameBoy(const string& playerName)
    : window(VideoMode(1020, 800), "Game Menu"),
    menu(window, &leaderboard),
    player(playerName),
    leaderboard()
{
    leaderboard.loadFromFile("leaderboard.txt"); 
}

void GameBoy::run() 
{
    Game* games[3];
    

    while (true) 
    {

        if (!window.isOpen())
        {
            break; 
        }

        games[0] = new HangmanGame();
        games[1] = new WordleGame();
        games[2] = new SnakeGame();

        int choice = menu.displayMenu();


        if (choice >= 1 && choice <= 3)
        {
            cout << "Starting Game..." << endl;
            games[choice - 1]->Run(); // Run the selected game
            int gameScore = 0;

            // Update score based on the game
            switch (choice)
            {
            case 1: // Hangman
                gameScore = 190;
                player.updateScore(gameScore);
                leaderboard.addScore(0, player.getName(), gameScore);
                break;

            case 2: // Wordle
                gameScore = 110;
                player.updateScore(gameScore);
                leaderboard.addScore(1, player.getName(), gameScore);
                break;

            case 3: // Snake
                gameScore = 350;
                player.updateScore(gameScore);
                leaderboard.addScore(2, player.getName(), gameScore);
                break;
            }

            cout << "Your Score for this game: " << gameScore << endl;
            cout << "Total Score: " << player.getScore() << endl;

            // Save leaderboard data to file
            leaderboard.saveToFile("leaderboard.txt");

            cout << "Returning to Main Menu..." << endl;
            continue;

        }

        if (choice == 4) 
        {
            cout << "Exiting GameBoy. Goodbye!" << endl;
            sf::Clock clock;
            while (clock.getElapsedTime().asSeconds() < 3) {}
            window.close();
            break;
        }

        if (choice == 5) 
        {
            cout << "Opening Instructions!" << endl;
            int result = menu.displayInstructions();
            if (result == 6)
            {
                cout << "Returning to the main menu..." << endl;
            }
            continue;
        }

        

        if (choice == 7)
        {
            leaderboard.display(window);
            continue;
        }
        cout << "Invalid selection! Returning to the main menu..." << endl;


    }

    // Clean up allocated memory
    for (int i = 0; i < 3; i++)
    {
        delete games[i];
    }
}

int main() 
{
    string playerName;
    Player player1(playerName);
    player1.getName();
    GameBoy gameBoy(playerName);

    // Start the GameBoy
    gameBoy.run();

    return 0;
}