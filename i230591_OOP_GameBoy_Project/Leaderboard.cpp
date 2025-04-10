#include "Leaderboard.h"
#include <fstream>
#include <iostream>

Leaderboard::Leaderboard()
{
    // Initialize game names
    gameNames[0] = "Hangman";
    gameNames[1] = "Wordle";
    gameNames[2] = "Snake";

    // Initialize scores and player names
    for (int i = 0; i < MAX_GAMES; i++)
    {
        for (int j = 0; j < MAX_ENTRIES; j++)
        {
            playerNames[i][j] = "---"; // Placeholder
            scores[i][j] = 0;
        }
    }

    // Load font
    if (!font.loadFromFile("BlazeCircuitRegular-xRvxj.ttf"))
    {
        cout << "Error loading font!" << endl;
        exit(-1);
    }

    // Title text
    titleText.setFont(font);
    titleText.setString("Leaderboard");
    titleText.setCharacterSize(60);
    titleText.setFillColor(Color::White);
    titleText.setOutlineColor(Color::Black);
    titleText.setOutlineThickness(5);
    titleText.setPosition(250, 50);

    // Exit option text
    exitOption.setFont(font);
    exitOption.setString("Press ESC to return to Main Menu");
    exitOption.setCharacterSize(30);
    exitOption.setFillColor(Color::Green);
    exitOption.setOutlineColor(Color::Black);
    exitOption.setOutlineThickness(2);
    exitOption.setPosition(250, 700);

    if (!bgtexture.loadFromFile("Textures/background.jpg")) 
    {
        cout << "Error loading background image!" << endl;
        exit(-1);
    }
    bgsprite.setTexture(bgtexture);
    bgsprite.setScale(1020.0f / bgtexture.getSize().x, 800.0f / bgtexture.getSize().y);
    

}

void Leaderboard::loadFromFile(const string& filename) 
{
    ifstream file(filename);
    if (!file.is_open()) 
    {
        cout << "Error: Unable to open leaderboard file!" << endl;
        return;
    }

    for (int i = 0; i < MAX_GAMES; i++) 
    {
        for (int j = 0; j < MAX_ENTRIES; j++) 
        {
            file >> playerNames[i][j] >> scores[i][j];
        }
    }

    file.close();
}

void Leaderboard::saveToFile(const string& filename)
{
    ofstream file(filename);
    if (!file.is_open()) 
    {
        cout << "Error: Unable to open leaderboard file!" << endl;
        return;
    }

    for (int i = 0; i < MAX_GAMES; i++)
    {
        for (int j = 0; j < MAX_ENTRIES; j++) 
        {
            file << playerNames[i][j] << " " << scores[i][j] << endl;
        }
    }

    file.close();
}

void Leaderboard::addScore(int gameIndex, const string& playerName, int score) 
{
    if (gameIndex < 0 || gameIndex >= MAX_GAMES)
        return;

    // Find the position for the new score
    for (int i = 0; i < MAX_ENTRIES; i++)
    {
        if (score > scores[gameIndex][i])
        {
            // Shift lower scores down
            for (int j = MAX_ENTRIES - 1; j > i; j--)
            {
                playerNames[gameIndex][j] = playerNames[gameIndex][j - 1];
                scores[gameIndex][j] = scores[gameIndex][j - 1];
            }

            // Insert the new score
            playerNames[gameIndex][i] = playerName;
            scores[gameIndex][i] = score;
            break;
        }
    }
}

void Leaderboard::display(RenderWindow& window)
{
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == Event::Closed || (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)) {
                return;  // Return to the main menu
            }
        }

        render(window);
    }
}

void Leaderboard::render(RenderWindow& window)
{
    window.clear();
    window.draw(bgsprite);
    window.draw(titleText);

    float yOffset = 150;
    for (int i = 0; i < MAX_GAMES; i++)
    {
        // Display game title
        Text gameTitle(gameNames[i] + " Highscores", font, 40);
        gameTitle.setFillColor(Color::White);
        gameTitle.setOutlineColor(Color::Black);
        gameTitle.setOutlineThickness(2);
        gameTitle.setPosition(100, yOffset);
        window.draw(gameTitle);

        yOffset += 50;

        // Display player names and scores
        for (int j = 0; j < MAX_ENTRIES; j++) 
        {
            Text entryText(playerNames[i][j] + ": " + to_string(scores[i][j]), font, 30);
            entryText.setFillColor(Color::White);
            entryText.setPosition(150, yOffset);
            window.draw(entryText);
            yOffset += 40;
        }

        yOffset += 20;  // Add spacing between games
    }

    window.draw(exitOption);    
    window.display();
}