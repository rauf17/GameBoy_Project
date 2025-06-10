#include "GameBoy.h"
#include "Game.h"

GameBoy::GameBoy(const string& playerName) : window(VideoMode(1020, 800), "Game Menu"),
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
    {
        RenderWindow splashWindow(VideoMode(1024, 1200), "GameBoy", Style::Close);
        splashWindow.setFramerateLimit(60);

        Texture splashTexture;
        Sprite splashSprite;

        if (!splashTexture.loadFromFile("Textures/bg_mm.png")) // Your splash image
        {
            cout << "Failed to load splash image!" << endl;
            exit(-1);
        }

        splashSprite.setTexture(splashTexture);
        splashSprite.setScale(
            splashWindow.getSize().x / static_cast<float>(splashTexture.getSize().x),
            splashWindow.getSize().y / static_cast<float>(splashTexture.getSize().y)
        );

        Clock splashClock;
        const float fadeDuration = 3.f; // 3 seconds for each fade phase

        while (splashWindow.isOpen())
        {
            float elapsed = splashClock.getElapsedTime().asSeconds();
            float alpha = 255;

            if (elapsed < fadeDuration) // Fade In (0s - 3s)
            {
                alpha = 255 * (elapsed / fadeDuration);
            }
            else if (elapsed < 2 * fadeDuration) // Fade Out (3s - 6s)
            {
                alpha = 255 * (1 - ((elapsed - fadeDuration) / fadeDuration));
            }
            else // After 6s, close splash
            {
                splashWindow.close();
                break;
            }

            splashSprite.setColor(Color(255, 255, 255, static_cast<Uint8>(alpha)));

            splashWindow.clear();
            splashWindow.draw(splashSprite);
            splashWindow.display();
        }
    }


    string playerName;
    Player player1(playerName);
    player1.getName();
    GameBoy gameBoy(playerName);

    // Start the GameBoy
    gameBoy.run();

    return 0;
}