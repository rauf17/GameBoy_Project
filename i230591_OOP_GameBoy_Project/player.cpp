#include "Player.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
using namespace std;
using namespace sf;


Player::Player(const string& playerName) : name(playerName), score(0) {}

#include <SFML/Audio.hpp> 

string Player::getName() 
{
    RenderWindow window(VideoMode(1020, 800), "Enter Your Name", Style::Close);
    window.setFramerateLimit(30);

    string playerName;
    Font font;
    Font font2;
    Text inputText;
    Text promptText;
    Text DevelopersText;

    if (!font.loadFromFile("BlazeCircuitRegular-xRvxj.ttf")) 
    {
        cout << "Failed to load font";
    }

    if (!font2.loadFromFile("Fonts/main.ttf")) 
    {
        cout << "Failed to load font";
    }

    // Load and set up sound
    SoundBuffer keySoundBuffer;
    if (!keySoundBuffer.loadFromFile("Music/key.wav"))
    {
        cout << "Failed to load sound file" << endl;
        exit(-1);
    }
    Sound keySound;
    keySound.setBuffer(keySoundBuffer);

    // Set up prompt text
    promptText.setFont(font);
    promptText.setString("Welcome to GameBoy! \n\t\tEnter your name: ");
    promptText.setCharacterSize(40);
    promptText.setFillColor(Color::Black);
    promptText.setOutlineColor(Color::Magenta);
    promptText.setOutlineThickness(5);
    promptText.setPosition(50, 70);

    // Set up input text for displaying the name with an underscore
    inputText.setFont(font);
    inputText.setCharacterSize(30);
    inputText.setFillColor(Color::Black);
    inputText.setOutlineColor(Color::Magenta);
    inputText.setOutlineThickness(5);
    inputText.setPosition(650, 650);

    // Set up Developers text
    DevelopersText.setFont(font);
    DevelopersText.setString("Developers :\n\nAbdul Rauf (23I-0591)\tAbdul Ghufran (23I-0576)\tShayan Asad  (23I-0518)");
    DevelopersText.setCharacterSize(20);
    DevelopersText.setFillColor(Color::Black);
    DevelopersText.setOutlineColor(Color::Magenta);
    DevelopersText.setOutlineThickness(5);
    DevelopersText.setPosition(10, 700);

    // Load and set background texture
    if (!backgroundTexture.loadFromFile("GameBoy-bg.jpg")) 
    {
        cout << "Error loading background image!" << endl;
        exit(-1);
    }
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(window.getSize().x / static_cast<float>(backgroundTexture.getSize().x),
        window.getSize().y / static_cast<float>(backgroundTexture.getSize().y));

    while (window.isOpen()) 
    {
        window.draw(backgroundSprite);
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed) 
            {
                window.close();
            }
            else if (event.type == Event::TextEntered) 
            {
                if (event.text.unicode == '\b')
                { // Handle backspace
                    if (!playerName.empty())
                    {
                        playerName.pop_back();
                    }
                }
                else if (event.text.unicode == '\r' || event.text.unicode == '\n')
                { // Handle Enter key
                    if (!playerName.empty()) 
                    {
                        name = playerName; // Save the name
                        window.close();
                    }
                }
                else if (event.text.unicode < 128)
                { 
                    playerName += static_cast<char>(event.text.unicode);
                    keySound.play(); // Play sound when a key is pressed
                }
            }
        }

        // Update input text to show the current input with an underscore at the end
        inputText.setString(playerName + "-");

        window.draw(promptText);
        window.draw(inputText);
        window.draw(DevelopersText);
        window.display();
    }

    return name;
}


void Player::updateScore(int points) 
{
    score += points;
}

int Player::getScore() const 
{
    return score;
}



