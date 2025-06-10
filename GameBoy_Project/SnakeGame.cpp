#include "SnakeGame.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>

using namespace std;
using namespace sf;

// Grid Class Definitions
grid::grid(int rows, int columns, int cellSize) : rows(rows), columns(columns), cellSize(cellSize) 
{
    gridCell.setSize(Vector2f(cellSize, cellSize));
    gridCell.setFillColor(Color(0, 0, 0, 0));
}

void grid::draw(RenderWindow& window) 
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++) 
        {
            gridCell.setPosition(j * cellSize, i * cellSize);
            window.draw(gridCell);
        }
    }
}

Vector2f grid::toPixelCoords(int gridX, int gridY) const
{
    return Vector2f(gridX * cellSize, gridY * cellSize);
}

Vector2i grid::toGridCoords(int pixelX, int pixelY) const 
{
    return Vector2i(pixelX / cellSize, pixelY / cellSize);
}



// ScoreManager Class Definitions
Scoremanager::Scoremanager() : score(0) 
{
    if (!font2.loadFromFile("Textures/font2.ttf"))
    {
        cout << "Error loading font!" << endl;
        exit(-1);
    }
    scoreText.setFont(font2);
    scoreText.setCharacterSize(35);
    scoreText.setFillColor(Color::White);
    scoreText.setPosition(resolutionX / 2.0f - 100, 15);
}

const Font& Scoremanager::getFont() const 
{
    return font2;
}

void Scoremanager::increaseScore(int amount) 
{
    score += amount;
}

int Scoremanager::getScore() const 
{
    return score;
}

void Scoremanager::draw(RenderWindow& window)
{
    scoreText.setString("Score: " + to_string(score));
    window.draw(scoreText);
}





// Snake Class Definitions
Snake::Snake(int initialLength) : length(initialLength), directionX(1), directionY(0) 
{
    for (int i = 0; i < length; i++)
    {
        body[i][0] = gameColumns / 2 - i;
        body[i][1] = gameRows / 2;
    }
}

void Snake::move() 
{
    int newHeadX = body[0][0] + directionX;
    int newHeadY = body[0][1] + directionY;

    for (int i = length; i > 0; i--) 
    {
        body[i][0] = body[i - 1][0];
        body[i][1] = body[i - 1][1];
    }

    body[0][0] = newHeadX;
    body[0][1] = newHeadY;
}

void Snake::grow() 
{
    length++;
    body[length - 1][0] = body[length - 2][0];
    body[length - 1][1] = body[length - 2][1];
}

bool Snake::checkCollision() const
{
    if (body[0][0] < 0 || body[0][1] < 0 || body[0][0] >= gameColumns || body[0][1] >= gameRows) 
    {
        return true;
    }

    for (int i = 1; i < length; i++) 
    {
        if (body[i][0] == body[0][0] && body[i][1] == body[0][1]) 
        {
            return true;
        }
    }
    return false;
}

void Snake::setDirection(int dx, int dy)
{
    if ((dx == 0 && dy == 0) || (dx == -directionX && dy == -directionY))
    {
        return;
    }
    directionX = dx;
    directionY = dy;
}

int(*Snake::getBody())[2]
{
    return body;
}

int Snake::getLength() const
{
    return length;
}





// Food Class Definitions
Food::Food()
{
    spawnFood();
}

void Food::spawnFood()
{
    srand(time(0));
    foodX = rand() % (gameColumns - 2) + 1;
    foodY = rand() % (gameRows - 2) + 1;
}

int Food::getFoodX() const 
{
    return foodX;
}

int Food::getFoodY() const
{
    return foodY;
}

// SnakeGame Class Definitions
SnakeGame::SnakeGame() : grid(gameRows, gameColumns, boxSize), snake(5), food(), scoreManager(), bonusFoodActive(false), isPaused(false)
{
    if (!headTexture.loadFromFile("Textures/snake_head.png") ||
        !bodyTexture.loadFromFile("Textures/snake_body.png") ||
        !foodTexture.loadFromFile("Textures/mushroom.png") ||
        !backgroundTexture.loadFromFile("Textures/background1.jpg") ||
        !gameOverTexture.loadFromFile("Textures/gameover.jpg") ||
        !startScreenTexture.loadFromFile("Textures/start.png") ||
        !bonusFoodTexture.loadFromFile("Textures/bonus_food.png")) {
        cout << "Error loading textures!" << endl;
        exit(-1);
    }

    headSprite.setTexture(headTexture);
    bodySprite.setTexture(bodyTexture);
    foodSprite.setTexture(foodTexture);
    bonusFoodSprite.setTexture(bonusFoodTexture);
    backgroundSprite.setTexture(backgroundTexture);
    startScreenSprite.setTexture(startScreenTexture);
    gameOverSprite.setTexture(gameOverTexture);

    Vector2f scaleFactor(3.0 * (boxSize) / headTexture.getSize().x, 3.0 * (boxSize) / headTexture.getSize().y);
    headSprite.setScale(scaleFactor);
    bodySprite.setScale(scaleFactor);
    foodSprite.setScale(3.0 * (boxSize) / foodTexture.getSize().x, 3.0 * (boxSize) / foodTexture.getSize().y);
    bonusFoodSprite.setScale(1.7 * (boxSize) / bonusFoodTexture.getSize().x, 1.7 * (boxSize) / bonusFoodTexture.getSize().y);

    Vector2f backgroundScaleFactor(float(resolutionX) / backgroundTexture.getSize().x, float(resolutionY) / backgroundTexture.getSize().y);
    backgroundSprite.setScale(backgroundScaleFactor);

    Vector2f startScreenScaleFactor(float(resolutionX) / startScreenTexture.getSize().x, float(resolutionY) / startScreenTexture.getSize().y);
    startScreenSprite.setScale(startScreenScaleFactor);

    Vector2f gameOverScaleFactor(float(resolutionX) / gameOverTexture.getSize().x, float(resolutionY) / gameOverTexture.getSize().y);
    gameOverSprite.setScale(gameOverScaleFactor);

    gameOverScoreText.setFont(scoreManager.getFont());
    gameOverScoreText.setCharacterSize(36);
    gameOverScoreText.setFillColor(Color::White);
    gameOverScoreText.setPosition(resolutionX / 2.0f - 100, resolutionY / 2.0f + 50);

    StartScreenText.setFont(scoreManager.getFont());
    StartScreenText.setCharacterSize(50);
    StartScreenText.setFillColor(Color::Green);
    StartScreenText.setOutlineColor(Color::Black);
    StartScreenText.setOutlineThickness(5);
    StartScreenText.setPosition(resolutionX / 2.0f-500, 50);

    pauseText.setFont(scoreManager.getFont());
    pauseText.setCharacterSize(48);
    pauseText.setFillColor(Color::White);
    pauseText.setString("PAUSED");
    pauseText.setPosition(resolutionX / 2.0f - 100, resolutionY / 2.0f);
}

void SnakeGame::Run()
{
    // Load and play background music
    Music backgroundMusic;
    if (!backgroundMusic.openFromFile("Music/mainmusic.mp3"))
    {
        cout << "Error loading background music!" << endl;
    }
    backgroundMusic.setLoop(true); // Ensure the music loops until the game is over or the window closes
    backgroundMusic.setVolume(30); 
    backgroundMusic.play(); 

    showStartScreen();
    while (window.isOpen())
    {
        processEvents();
        update();
        render();
    }

    // Stop the music when the game ends or the window closes
    backgroundMusic.stop();
}

void SnakeGame::processEvents() 
{
    Event e;
    while (window.pollEvent(e))
    {
        if (e.type == Event::Closed) 
        {
            window.close();
        }

        if (e.type == Event::KeyPressed) 
        {
            if (e.key.code == Keyboard::Up) {
                snake.setDirection(0, -1);
            }
            if (e.key.code == Keyboard::Down) {
                snake.setDirection(0, 1);
            }
            if (e.key.code == Keyboard::Left) {
                snake.setDirection(-1, 0);
            }
            if (e.key.code == Keyboard::Right) {
                snake.setDirection(1, 0);
            }
            if (e.key.code == Keyboard::Space) {
                isPaused = !isPaused;
            }
        }
    }
}

void SnakeGame::update() 
{
    if (isPaused) 
    {
        return;
    }

    if (!bonusFoodActive && gameClock.getElapsedTime().asSeconds() >= 10)
    {
        spawnBonusFood();
        gameClock.restart();
    }

    if (bonusFoodActive && bonusFoodClock.getElapsedTime().asSeconds() >= 5)
    {
        bonusFoodActive = false;
    }

    snake.move();

    if (snake.checkCollision())
    {
        showGameOverScreen();
        window.close();
        return;
    }

    if (snake.getBody()[0][0] == food.getFoodX() && snake.getBody()[0][1] == food.getFoodY()) 
    {
        food.spawnFood();
        snake.grow();
        scoreManager.increaseScore(10);
    }

    if (bonusFoodActive && snake.getBody()[0][0] == bonusFoodX && snake.getBody()[0][1] == bonusFoodY) 
    {
        bonusFoodActive = false;
        snake.grow();
        snake.grow();
        snake.grow();
        scoreManager.increaseScore(30);
    }
}

void SnakeGame::render()
{
    window.clear();
    window.draw(backgroundSprite);

    if (isPaused) 
    {
        window.draw(pauseText);
    }
    else 
    {
        grid.draw(window);

        for (int i = 0; i < snake.getLength(); i++) 
        {
            int(*body)[2] = snake.getBody();
            Vector2f pixelPos = grid.toPixelCoords(body[i][0], body[i][1]);

            if (i == 0) 
            {
                headSprite.setPosition(pixelPos);
                window.draw(headSprite);
            }
            else {
                bodySprite.setPosition(pixelPos);
                window.draw(bodySprite);
            }
        }

        Vector2f foodPos = grid.toPixelCoords(food.getFoodX(), food.getFoodY());
        foodSprite.setPosition(foodPos);
        window.draw(foodSprite);

        if (bonusFoodActive) 
        {
            Vector2f bonusFoodPos = grid.toPixelCoords(bonusFoodX, bonusFoodY);
            bonusFoodSprite.setPosition(bonusFoodPos);
            window.draw(bonusFoodSprite);
        }

        scoreManager.draw(window);
    }

    window.display();
}

void SnakeGame::showStartScreen() 
{
    window.create(VideoMode(resolutionX, resolutionY), "Snake Game");
    window.setFramerateLimit(10);

    Clock clock;
    StartScreenText.setString("Snake Game \n\t\t\t  The Dangerous Zone");
    
    while (clock.getElapsedTime().asSeconds() < 3) 
    {
        window.clear();
        window.draw(startScreenSprite);
        window.draw(StartScreenText);
        window.display();
    }
}

void SnakeGame::spawnBonusFood()
{
    srand(time(0));
    bonusFoodX = rand() % (gameColumns - 2) + 1;
    bonusFoodY = rand() % (gameRows - 2) + 1;
    bonusFoodActive = true;
    bonusFoodClock.restart();
}

void SnakeGame::showGameOverScreen()
{
    // Load and play game over music
    Music gameOverMusic;
    if (!gameOverMusic.openFromFile("Music/gameovervoice.mp3"))
    {
        cout << "Error loading game over music!" << endl;
    }
    gameOverMusic.setVolume(10); // Adjust the volume as needed (0-100)
    gameOverMusic.play(); // Play the game over music

    Clock clock;
    gameOverScoreText.setString("Final Score: " + to_string(scoreManager.getScore()));
    while (clock.getElapsedTime().asSeconds() < 3)
    {
        window.clear();
        window.draw(gameOverSprite);
        window.draw(gameOverScoreText);
        window.display();
    }

    // Stop the game over music after the screen has been shown
    gameOverMusic.stop();
}

