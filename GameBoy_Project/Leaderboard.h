#pragma once

#include <SFML/Graphics.hpp>
#include <string>

using namespace std;
using namespace sf;

class Leaderboard {
private:
    static const int MAX_GAMES = 3;
    static const int MAX_ENTRIES = 2;

    // Leaderboard data
    string gameNames[MAX_GAMES];
    string playerNames[MAX_GAMES][MAX_ENTRIES];
    int scores[MAX_GAMES][MAX_ENTRIES];
    Font font;
    Text titleText, exitOption;
    RectangleShape background;
    Texture bgtexture;      
    Sprite bgsprite;

public:
    Leaderboard();
    // Methods to load and save leaderboard data
    void loadFromFile(const string& filename);
    void saveToFile(const string& filename);

    // Add a new score
    void addScore(int gameIndex, const string& playerName, int score);
    void display(RenderWindow& window);
    void render(RenderWindow& window);
};
