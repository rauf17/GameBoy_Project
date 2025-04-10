#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <SFML/Audio.hpp>
#include "Game.h"
using namespace std;
using namespace sf;


const int resolutionX = 1000;
const int resolutionY = 800;
const int boxSize = 32; // Size of each grid square
const int gameRows = resolutionY / boxSize;
const int gameColumns = resolutionX / boxSize;
const int maxSnakeLength = 1000;

class grid 
{
private:
    int rows, columns, cellSize;
    RectangleShape gridCell;

public:
    grid(int rows, int columns, int cellSize);
    void draw(RenderWindow& window);
    Vector2f toPixelCoords(int gridX, int gridY) const;
    Vector2i toGridCoords(int pixelX, int pixelY) const;
};

class Scoremanager 
{
private:
    int score;
    Font font2;
    Text scoreText;

public:
    Scoremanager();
    const Font& getFont() const;
    void increaseScore(int amount);
    int getScore() const;
    void draw(RenderWindow& window);
};

class Snake 
{
private:
    int body[1000][2];  // Snake body as an array of [x, y] positions
    int length;
    int directionX, directionY;

public:
    Snake(int initialLength = 5);
    void move();
    void grow();
    bool checkCollision() const;
    void setDirection(int dx, int dy);
    int(*getBody())[2];
    int getLength() const;
};

class Food 
{
private:
    int foodX, foodY;

public:
    Food();
    void spawnFood();
    int getFoodX() const;
    int getFoodY() const;
};


class SnakeGame : public Game
{
private:
    RenderWindow window;
    Texture headTexture, bodyTexture, foodTexture, bonusFoodTexture, backgroundTexture, startScreenTexture, gameOverTexture;
    Sprite headSprite, bodySprite, foodSprite, bonusFoodSprite, backgroundSprite, startScreenSprite, gameOverSprite;
    Text gameOverScoreText, StartScreenText;
    Font font2;
    bool isPaused;
    bool bonusFoodActive;
    Text pauseText;
    grid grid;
    Snake snake;
    Food food;
    Scoremanager scoreManager;
    int bonusFoodX, bonusFoodY;
    Clock bonusFoodClock;
    Clock gameClock;

public:
    SnakeGame();
    void Run() override;
    void processEvents();
    void update();
    void render();
    void showStartScreen();
    void spawnBonusFood();
    void showGameOverScreen();
};


