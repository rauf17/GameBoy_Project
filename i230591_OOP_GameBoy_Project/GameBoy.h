#pragma once

#include "MENU-AR.h"
#include "player.h"
#include "SnakeGame.h"
#include "Wordle.h"
#include "Hangman.h"
#include "Leaderboard.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

using namespace std;
using namespace sf;

class GameBoy
{
private:
    RenderWindow window;
    MainMenu menu;
    Player player;
    Game* game;
	Leaderboard leaderboard;
public:
    GameBoy(const string& playerName);
    void run();
};


