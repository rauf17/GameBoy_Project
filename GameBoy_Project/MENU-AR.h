#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "Leaderboard.h"

using namespace std;
using namespace sf;

class MainMenu 
{
private:
    RenderWindow& window;
    Font font;
    Text GameBoyText, option1, option2, option3, option4, option5, option6 , option7 , InstructionsText, InstructionsHeading, GoodByeText;
    Texture backgroundTexture;
    Sprite backgroundSprite;
	Leaderboard* leaderboard;
public:
    MainMenu(RenderWindow& win, Leaderboard* lb);
    int displayMenu();
    int displayInstructions();
};



