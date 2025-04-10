
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "MENU-AR.h"
#include "Wordle.h"
#include "Hangman.h"
#include "SnakeGame.h" 
#include "Leaderboard.h"

using namespace std;
using namespace sf;


MainMenu::MainMenu(RenderWindow& win, Leaderboard* lb) : window(win), leaderboard(lb)
{
    if (!font.loadFromFile("BlazeCircuitRegular-xRvxj.ttf"))
    {
        cout << "Error loading font!" << endl;
        exit(-1);
    }

    // Initialize menu text
    GameBoyText.setFont(font);
    GameBoyText.setString("GameBoy");
    GameBoyText.setCharacterSize(80);
    GameBoyText.setFillColor(Color::Black);
    GameBoyText.setPosition(250, 80);
    GameBoyText.setOutlineColor(Color::Magenta);
    GameBoyText.setOutlineThickness(5);

    option1.setFont(font);
    option1.setString(" Hangman");
    option1.setCharacterSize(30);
    option1.setFillColor(Color::Black);
    option1.setPosition(405, 500);
    option1.setOutlineColor(Color::Magenta);
    option1.setOutlineThickness(5);

    option2.setFont(font);
    option2.setString(" Wordle");
    option2.setCharacterSize(30);
    option2.setFillColor(Color::Black);
    option2.setPosition(415, 550);
    option2.setOutlineColor(Color::Magenta);
    option2.setOutlineThickness(5);

    option3.setFont(font);
    option3.setString(" Snake");
    option3.setCharacterSize(30);
    option3.setFillColor(Color::Black);
    option3.setPosition(420, 600);
    option3.setOutlineColor(Color::Magenta);
    option3.setOutlineThickness(5);

    option4.setFont(font);
    option4.setString(" Exit");
    option4.setCharacterSize(30);
    option4.setFillColor(Color::Black);
    option4.setPosition(800, 700);
    option4.setOutlineColor(Color::Magenta);
    option4.setOutlineThickness(5);

    option5.setFont(font);
    option5.setString(" Instructions");
    option5.setCharacterSize(30);
    option5.setFillColor(Color::Black);
    option5.setPosition(60, 700);
    option5.setOutlineColor(Color::Magenta);
    option5.setOutlineThickness(5);

    option6.setFont(font);
    option6.setString(" Exit");
    option6.setCharacterSize(30);
    option6.setFillColor(Color::Black);
    option6.setPosition(800, 700);
    option6.setOutlineColor(Color::Magenta);
    option6.setOutlineThickness(5);

    option7.setFont(font);
    option7.setString(" Leaderboard");
    option7.setCharacterSize(30);
    option7.setFillColor(Color::Black);
    option7.setPosition(400, 700);
    option7.setOutlineColor(Color::Magenta);
    option7.setOutlineThickness(5);

    InstructionsHeading.setFont(font);
    InstructionsHeading.setString(" Instructions");
    InstructionsHeading.setCharacterSize(50);
    InstructionsHeading.setFillColor(Color::Black);
    InstructionsHeading.setPosition(10, 10);
    InstructionsHeading.setOutlineColor(Color::Magenta);
    InstructionsHeading.setOutlineThickness(5);

    GoodByeText.setFont(font);
    GoodByeText.setString(" Exiting GameBoy!\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\t\t\t Goodbye! ");
    GoodByeText.setCharacterSize(50);
    GoodByeText.setFillColor(Color::Black);
    GoodByeText.setPosition(10, 100);
    GoodByeText.setOutlineColor(Color::Magenta);
    GoodByeText.setOutlineThickness(5);


    InstructionsText.setFont(font);
    InstructionsText.setString( "Hangman:\n"
        "1. Player thinks of a word, and tries to guess it one letter at a time.\n"
        "2. For each incorrect guess, a part of a hangman is drawn.\n"
        "3. The game ends when Player 2 guesses the word or the hangman is \ncompletely drawn.\n"
        "4. Use logical guesses and avoid repeating incorrect letters.\n\n\n"
        "Wordle:\n"
        "1. Guess the 5-letter secret word in six tries.\n"
        "2. Each guess must be a valid word. Press Enter to submit.\n"
        "3. Feedback will be provided: \n"
        "   - Green: Correct letter in the correct spot.\n"
        "   - Yellow: Correct letter in the wrong spot.\n"
        "   - Gray: Letter not in the word.\n"
        "4. Use feedback to refine guesses and find the secret word.\n\n\n"
        "Snake:\n"
        "1. Control the snake to collect food and grow longer.\n"
        "2. Use arrow keys (or WASD) to navigate the snake.\n"
        "3. Avoid colliding with walls or the snake's own body.\n"
        "4. The game ends when the snake crashes or cannot move.\n"
        "5. Aim for the highest score by collecting as much food as possible.");
    InstructionsText.setCharacterSize(20);
    InstructionsText.setFillColor(Color::White);
    InstructionsText.setPosition(30, 100);
    InstructionsText.setOutlineColor(Color::Black);
    InstructionsText.setOutlineThickness(5);


    // Load and set background texture
    if (!backgroundTexture.loadFromFile("GameBoy-bg.jpg"))
    {
        cout << "Error loading background image!" << endl;
        exit(-1);
    }
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(window.getSize().x / static_cast<float>(backgroundTexture.getSize().x),
        window.getSize().y / static_cast<float>(backgroundTexture.getSize().y));
}

#include <SFML/Audio.hpp> // Include for sound functionality

int MainMenu::displayMenu() 
{
    // Load background music
    Music backgroundMusic;
    if (!backgroundMusic.openFromFile("Music/mainscreen.mp3"))
    {
        cout << "Failed to load main menu music" << endl;
        return -1;
    }
    backgroundMusic.setLoop(true); // Make the music loop
    backgroundMusic.setVolume(5); // Set background music volume to 30%
    backgroundMusic.play(); // Play the music when the menu is displayed
   

    // Load the hover sound
    SoundBuffer hoverSoundBuffer;
    if (!hoverSoundBuffer.loadFromFile("Music/key.wav")) 
    {
        cout << "Failed to load hover sound" << endl;
        return -1;
    }
    Sound hoverSound;
    hoverSound.setBuffer(hoverSoundBuffer);
    hoverSound.setVolume(80);

    // Variable to track the last hovered option
    int lastHoveredOption = -1;
    Clock hoverClock; // To track the time since the last sound play

    while (window.isOpen()) 
    {
        Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == Event::Closed)
            {
                window.close();
                return -1; // Exit if window is closed
            }

            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
            {
                Vector2i mousePos = Mouse::getPosition(window);
                if (option1.getGlobalBounds().contains(static_cast<Vector2f>(mousePos)))
                {
                    return 1; // Hangman selected
                }
                else if (option2.getGlobalBounds().contains(static_cast<Vector2f>(mousePos)))
                {
                    return 2; // Wordle selected
                }
                else if (option3.getGlobalBounds().contains(static_cast<Vector2f>(mousePos)))
                {
                    return 3; // Snake selected
                }
                else if (option4.getGlobalBounds().contains(static_cast<Vector2f>(mousePos))) 
                {
                    window.clear();
                    window.draw(backgroundSprite);
                    window.draw(GoodByeText);
                    window.display();
                    return 4; // Exit selected
                }
                else if (option5.getGlobalBounds().contains(static_cast<Vector2f>(mousePos)))
                {
                    return 5; // Exit selected
                }
				else if (option7.getGlobalBounds().contains(static_cast<Vector2f>(mousePos)))
				{
					leaderboard->display(window);
					return  7; // Exit selected
				}
            }

            // Check if the mouse is hovering over an option and play the sound if necessary
            Vector2i mousePos = Mouse::getPosition(window);
            if (option1.getGlobalBounds().contains(static_cast<Vector2f>(mousePos)))
            {
                if (lastHoveredOption != 1 && hoverClock.getElapsedTime().asMilliseconds() > 200) 
                {
                    hoverSound.play();
                    lastHoveredOption = 1;
                    hoverClock.restart();
                }
            }

            else if (option2.getGlobalBounds().contains(static_cast<Vector2f>(mousePos))) 
            {
                if (lastHoveredOption != 2 && hoverClock.getElapsedTime().asMilliseconds() > 200)
                {
                    hoverSound.play();
                    lastHoveredOption = 2;
                    hoverClock.restart();
                }
            }

            else if (option3.getGlobalBounds().contains(static_cast<Vector2f>(mousePos))) 
            {
                if (lastHoveredOption != 3 && hoverClock.getElapsedTime().asMilliseconds() > 200)
                {
                    hoverSound.play();
                    lastHoveredOption = 3;
                    hoverClock.restart();
                }
            }

            else if (option4.getGlobalBounds().contains(static_cast<Vector2f>(mousePos)))
            {
                if (lastHoveredOption != 4 && hoverClock.getElapsedTime().asMilliseconds() > 200)
                {
                    hoverSound.play();
                    lastHoveredOption = 4;
                    hoverClock.restart();
                }
            }

            else if (option5.getGlobalBounds().contains(static_cast<Vector2f>(mousePos))) 
            {
                if (lastHoveredOption != 5 && hoverClock.getElapsedTime().asMilliseconds() > 200)
                {
                    hoverSound.play();
                    lastHoveredOption = 5;
                    hoverClock.restart();
                }
            }

            else 
            {
                // Reset lastHoveredOption if the mouse is not over any option
                lastHoveredOption = -1;
            }
        }

        window.clear();
        window.draw(backgroundSprite);
        window.draw(GameBoyText);
        window.draw(option1);
        window.draw(option2);
        window.draw(option3);
        window.draw(option4);
        window.draw(option5);
		window.draw(option7);
        window.display();
    }
    return -1;
}


int MainMenu::displayInstructions()
{
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
                return -1; // Exit if window is closed
            }

            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
            {
                Vector2i mousePos = Mouse::getPosition(window);
                if (option6.getGlobalBounds().contains(static_cast<Vector2f>(mousePos)))
                {
                    return 6; // Signal to return to the menu
                }
            }
        }

        window.clear();
        window.draw(InstructionsHeading);
        window.draw(InstructionsText);
        window.draw(option6);
        window.display();
    }
    return -1; // Default return if window is closed
}

