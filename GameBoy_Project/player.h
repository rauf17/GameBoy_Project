#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
using namespace std;
using namespace sf;

class Player 
{
private:
    string name;
    int score;

    Texture backgroundTexture;
    Sprite backgroundSprite;

public:
    Player(const string& playerName);
    string getName();
    void updateScore(int points);
    int getScore() const;
};

