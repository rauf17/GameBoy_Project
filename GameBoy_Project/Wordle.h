#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <SFML/Audio.hpp>
#include "Game.h"

using namespace std;
using namespace sf;

const int TILE_SIZE = 60;
const int NUM_ATTEMPTS = 6;
const int MAX_WORD_LENGTH = 5;
const int MAX_WORDS = 40;
const int MAX_KEYS = 26;


class WordManager {
private:
    string wordList[MAX_WORDS] = {
    "APPLE", "GRAPE", "PEACH", "MANGO", "FLAME", "PLANE", "ZEBRA", "LEMON", "TRAIN", "BERRY","CRANE",
    "WATER", "STORM", "SNOWY", "WINDY", "CLOUD", "STONE", "GLASS", "GRASS", "LEAFY",
    "BLOOM", "SHINE", "LIGHT", "SWEET", "FLOUR", "THORN", "SMILE", "ROSES", "OCEAN", "BLUSH","BASIC",
    "BRAIN", "SHARP", "COAST", "CLEAN", "BRAVE", "CRASH", "TIGHT", "GLOBE", "WITCH" };
    string currentWord;
public:
    WordManager();
    string getRandomWord();
    string getCurrentWord() const;
    // Check if a word is in the word list
    bool isValidWord(const string& word);
};

class Grid
{
private:
    char cells[NUM_ATTEMPTS][MAX_WORD_LENGTH];
public:
    Grid();
    void updateCell(int x, int y, char value);
    char getCell(int x, int y) const;
};

class keyboard
{
public:
    struct Key
    {
        char letter;
        RectangleShape shape;
        Color color_keys;
    };
private:
    Key keys[MAX_KEYS];
    const int KEY_WIDTH = 60;
    const int KEY_HEIGHT = 60;
    const int PADDING = 10;
    int keyCount = 0;
    RectangleShape enterButton;
    RectangleShape backspaceButton;
public:
    keyboard();
    void renderKeyboard(RenderWindow& window);
    char getClickedKey(Vector2i mousePos);
    void updateKeyboardKeyColor(char letter, Color color);
    static char sfKeyToChar(Keyboard::Key key);
};

class ScoreManager 
{
private:
    int currentScore;

public:
    ScoreManager();
    void updateScore(int points);
    int getScore() const;
};

class Menu
{
public:
    int displayMenu(RenderWindow& window, Font& font);
};

class HelpTutorial
{
public:
    void showHelp(RenderWindow& window, Font& font);
};


class WordleGame:public Game {
private:
    WordManager wordManager;
    keyboard keyboard;
    ScoreManager scoreManager;
    Grid grid;
    HelpTutorial help;

    Color attemptColors[NUM_ATTEMPTS][MAX_WORD_LENGTH];
    string currentGuess;
    int currentAttempt = 0;
    int attempttoprint = 6;
    bool gameOver = false;
    bool isGameWon = false;
    bool printing_invalidmsg = false;
    bool paused = false;

    Text instructionText;
    Text scoreText;
    Text attempts;

    void updateScoreText();
    void updateAttemptsText();
    void evaluateAttempt(int attemptIndex);
    void handleBackspaceKey();
public:
    WordleGame();
    void renderGame(RenderWindow& window);
    void togglePause(RenderWindow& window);
    void handleMouseClick(Vector2i mousePos, RenderWindow& window);
    bool handleEnterKey(RenderWindow& window);
    bool isGameOver();
    bool isGameWonStatus() const;
    const string& getCurrentGuess() const;
    void Run() override;

};

