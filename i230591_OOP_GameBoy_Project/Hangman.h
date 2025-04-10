#pragma once

#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <SFML/Audio.hpp>
#include "Game.h"

using namespace sf;
using namespace std;

class Wordmanager
{
private:
    char words[3][5][20];
    const char* categories[3] = { "Fruits", "Clothes", "Animals" };
    int categoryIndex;
public:
    Wordmanager();
    void loadWords();
    void setCategory(int index);
    const char* getCategoryHint() const;
    const char* getRandomWord() const;
};

class HangmanGame : public Game
{
private:
    int lives;
    char currentWord[20];
    char guessedWord[20];
    int currentWordLength;
    int guessedWordLength;
    Wordmanager Wordmanager;
    int alphabetStatus[26];
    int score;
    Texture hangmanTextures[7];
    Sprite hangmanSprite;
    void handleInput(char letter);
    bool isWordGuessed() const;
    void update(RenderWindow& window);
public:
    HangmanGame();
    void resetGame();
    void Run() override;
    void render(RenderWindow& window);
};