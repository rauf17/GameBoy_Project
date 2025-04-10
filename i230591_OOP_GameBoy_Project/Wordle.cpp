//#include <SFML/Graphics.hpp>
//#include <iostream>
//#include <cstdlib>
//#include <ctime>
#include "Wordle.h"
Font font;
//#include <string>
using namespace std;
using namespace sf;

WordManager::WordManager()
{
    currentWord = "";
}
string WordManager::getRandomWord()
{
    srand(time(0));  
    int randomIndex = rand() % MAX_WORDS;
    currentWord = wordList[randomIndex];
    return currentWord;
}
string WordManager::getCurrentWord() const 
{
    return currentWord;
}
// Check if a word is in the word list
bool WordManager::isValidWord(const string& word)
{
    for (int i = 0; i < MAX_WORDS; i++) 
    {
        if (wordList[i] == word) 
        {
            return true;
        }
    }
    return false;
}

Grid::Grid()
{
    for (int i = 0; i < NUM_ATTEMPTS; i++)
    {
        for (int j = 0; j < MAX_WORD_LENGTH; j++) 
        {
            cells[i][j] = ' '; // Initialize cells as empty
        }
    }
}
void Grid::updateCell(int x, int y, char value)
{
    if (x >= 0 && x < NUM_ATTEMPTS && y >= 0 && y < MAX_WORD_LENGTH)
    {
        cells[x][y] = value;
    }
}
char Grid::getCell(int x, int y) const 
{
    if (x >= 0 && x < NUM_ATTEMPTS && y >= 0 && y < MAX_WORD_LENGTH)
    {
        return cells[x][y];
    }
    return '\0'; // Return null char if out of bounds
}

keyboard::keyboard()
{
    const string rows[] = { "QWERTYUIOP", "ASDFGHJKL", "ZXCVBNM" };
    const int rowCount = 3;
    int startY = 525;

    // Setup Enter and Backspace buttons
    enterButton.setSize(Vector2f(KEY_WIDTH * 2 + PADDING, KEY_HEIGHT));  // Wider than normal keys
    enterButton.setPosition(15, startY - KEY_HEIGHT + 6 * PADDING);
    enterButton.setFillColor(Color::Yellow);
    enterButton.setOutlineColor(Color::White);
    enterButton.setOutlineThickness(2);

    backspaceButton.setSize(Vector2f(KEY_WIDTH * 2 + PADDING, KEY_HEIGHT));  // Wider than normal keys
    backspaceButton.setPosition(855, startY - KEY_HEIGHT + 6 * PADDING);
    backspaceButton.setFillColor(Color::Yellow);
    backspaceButton.setOutlineColor(Color::White);
    backspaceButton.setOutlineThickness(2);

    for (int r = 0; r < rowCount; r++) 
    {
        int startX = (1000 - ((KEY_WIDTH + PADDING) * rows[r].size() - PADDING)) / 2;

        for (int i = 0; i < rows[r].size(); i++)
        {
            RectangleShape keyShape(Vector2f(KEY_WIDTH, KEY_HEIGHT));
            keyShape.setPosition(startX + i * (KEY_WIDTH + PADDING), startY + r * (KEY_HEIGHT + PADDING));
            keyShape.setFillColor(Color::Black);
            keyShape.setOutlineColor(Color::White);
            keyShape.setOutlineThickness(2);
            keys[keyCount++] = { rows[r][i], keyShape };
        }
    }
}
void keyboard::renderKeyboard(RenderWindow& window)
{
    window.draw(enterButton);
    window.draw(backspaceButton);
    // Add text to these buttons
    Text enterText;
    enterText.setFont(font);
    enterText.setString("ENTER");
    enterText.setCharacterSize(30);
    enterText.setFillColor(Color::Red);
    enterText.setOutlineColor(Color::Black);
    enterText.setOutlineThickness(3);
    enterText.setPosition(enterButton.getPosition().x, enterButton.getPosition().y + 10);
    window.draw(enterText);

    Text backspaceText;
    backspaceText.setFont(font);
    backspaceText.setString("BACK");
    backspaceText.setCharacterSize(30);
    backspaceText.setFillColor(Color::Red);
    backspaceText.setOutlineColor(Color::Black);
    backspaceText.setOutlineThickness(3);
    backspaceText.setPosition(backspaceButton.getPosition().x + 15, backspaceButton.getPosition().y + 10);
    window.draw(backspaceText);
    // Render regular keys
    for (int i = 0; i < keyCount; i++) 
    {
        window.draw(keys[i].shape);
        Text label;
        label.setFont(font);
        label.setString(keys[i].letter);
        label.setCharacterSize(30);
        label.setFillColor(Color::Blue);
        label.setOutlineColor(Color::White);
        label.setOutlineThickness(3);
        label.setPosition(keys[i].shape.getPosition().x + 15 , keys[i].shape.getPosition().y + 10 );
        window.draw(label);
    }
}

char keyboard::getClickedKey(Vector2i mousePos)
{  
    // Check if Enter or Backspace was clicked
    if (enterButton.getGlobalBounds().contains(static_cast<Vector2f>(mousePos)))
    {
        return '\n';  // Return newline for Enter
    }

    if (backspaceButton.getGlobalBounds().contains(static_cast<Vector2f>(mousePos)))
    {
        return '\b';  // Return backspace symbol
    }

    // Check if a letter key was clicked
    for (int i = 0; i < keyCount; i++) 
    {
        if (keys[i].shape.getGlobalBounds().contains(static_cast<Vector2f>(mousePos)))
        {
            return keys[i].letter;
        }
    }
    return '\0';
}

void keyboard::updateKeyboardKeyColor(char letter, Color color)
{
    for (int i = 0; i < keyCount; i++) 
    {
        if (keys[i].letter == letter) 
        {
            keys[i].color_keys = color;  // Update the color of the key
            keys[i].shape.setFillColor(color);  // Set the new color for the key
            break;
        }
    }
}

char keyboard::sfKeyToChar(Keyboard::Key key)
{
    if (key >= Keyboard::A && key <= Keyboard::Z)
    {
        return 'A' + (key - Keyboard::A);
    }
    return '\0';
}

ScoreManager::ScoreManager() : currentScore(0) {}

void ScoreManager::updateScore(int points) 
{
    currentScore += points;

}

int ScoreManager::getScore() const 
{
    return currentScore;
}

int Menu::displayMenu(RenderWindow& window, Font& font)
{
    Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("Textures/wordle-bg-2.jpeg")) 
    {
        cout << "Error loading background image!" << endl;
        return -1;
    }

    Sprite backgroundSprite;
    backgroundSprite.setTexture(backgroundTexture);

    // Optionally, scale the background to fit the window size
    Vector2u textureSize = backgroundTexture.getSize();
    Vector2u windowSize = window.getSize();

    float scaleX = windowSize.x / float(textureSize.x);  // Use float literals for division
    float scaleY = windowSize.y / float(textureSize.y);
    backgroundSprite.setScale(scaleX, scaleY);

    Text menuTitle("Wordle Game", font, 80);
    menuTitle.setFillColor(Color::Red);
    menuTitle.setPosition(80, 100);
    menuTitle.setOutlineColor(Color::Black);
    menuTitle.setOutlineThickness(10);

    Text menuNameText("The Battle of Words", font, 50);
    menuNameText.setFillColor(Color::Black);
    menuNameText.setPosition(200, 200);
    menuNameText.setOutlineColor(Color::Red);
    menuNameText.setOutlineThickness(5);

    Text menuStartText("Start Game", font, 40);
    menuStartText.setFillColor(Color::White);
    menuStartText.setOutlineColor(Color::Black);
    menuStartText.setOutlineThickness(5);
    menuStartText.setPosition(400, 350);

    Text menuQuitText("Quit", font, 40);
    menuQuitText.setFillColor(Color::White);
    menuQuitText.setOutlineColor(Color::Black);
    menuQuitText.setOutlineThickness(5);
    menuQuitText.setPosition(400, 400);

    int selectedOption = 0; // 0 = Start Game, 1 = Quit

    while (window.isOpen()) 
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
                return -1; // Exit game
            }

            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
            {
                Vector2i mousePos = Mouse::getPosition(window);
                if (menuStartText.getGlobalBounds().contains(static_cast<Vector2f>(mousePos)))
                {
                    return 0; // Start Game
                }

                else if (menuQuitText.getGlobalBounds().contains(static_cast<Vector2f>(mousePos))) 
                {
                    return 1; // Quit
                }
            }
        }

        window.clear(Color::Black);
        window.draw(backgroundSprite);
        window.draw(menuTitle);
        window.draw(menuStartText);
        window.draw(menuQuitText);
        window.draw(menuNameText);
        window.display();
    }
    return -1; // Exit if window is closed
}

void HelpTutorial::showHelp(RenderWindow& window, Font& font) 
{
    // Create the help text
    Text helpText(" Tutorial : Welcome to Wordle!\n\n-  Guess the 5-letter word.\n-  You have 6 attempts.\n-  Green means correct, Yellow means exists, Red means wrong.", font, 20);
    Text helpText2("------- Note : Click to Continue ------- \n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n------------------------------------------------------ Enjoy The Game!", font, 20);

    // Set text properties
    helpText.setFillColor(Color::White);
    helpText.setOutlineColor(Color::Black);
    helpText.setOutlineThickness(5);
    helpText.setPosition(50, 250);

    helpText2.setFillColor(Color::Red);
    helpText2.setOutlineColor(Color::Black);
    helpText2.setOutlineThickness(5);
    helpText2.setPosition(50, 50);

    // Draw the help screen
    window.clear();
    window.draw(helpText);
    window.draw(helpText2);
    window.display();

    // Listen for a mouse click to start the game
    bool clicked = false;
    while (!clicked)
    {
        Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == Event::Closed) 
            {
                window.close();  // Close the window if the user clicks the close button
            }
            if (event.type == Event::MouseButtonPressed)
            {
                // If mouse button is pressed, proceed to start the game
                clicked = true;
            }
        }
    }
}

WordleGame::WordleGame()
{
    wordManager.getRandomWord();
    instructionText.setFont(font);
    instructionText.setString("Enter a 5-letter word");
    instructionText.setOutlineColor(Color::Yellow);
    instructionText.setOutlineThickness(3);
    instructionText.setCharacterSize(40);
    instructionText.setFillColor(Color::Red);
    instructionText.setStyle(Text::Bold);
    FloatRect textBounds = instructionText.getLocalBounds();
    instructionText.setPosition(500 - textBounds.width / 2, 40);

    attempts.setFont(font);
    attempts.setCharacterSize(30);
    attempts.setFillColor(Color::White);
    attempts.setOutlineColor(Color::Red);
    attempts.setOutlineThickness(5);
    attempts.setStyle(Text::Bold);
    attempts.setPosition(30, 5);
    updateAttemptsText();

    scoreText.setFont(font);
    scoreText.setCharacterSize(30);
    scoreText.setFillColor(Color::White);
    scoreText.setOutlineColor(Color::Red);
    scoreText.setOutlineThickness(5);
    scoreText.setStyle(Text::Bold);
    scoreText.setPosition(800, 5);
    updateScoreText();

    Color customColor(20, 49, 66);
    for (int i = 0; i < NUM_ATTEMPTS; i++) 
    {
        for (int j = 0; j < MAX_WORD_LENGTH; j++) 
        {
            attemptColors[i][j] = customColor;
        }
    }
}

void WordleGame::renderGame(RenderWindow& window)
{
    if (paused) 
    {

        Texture pauseBackgroundTexture;
        Sprite pauseBackgroundSprite;
        pauseBackgroundTexture.loadFromFile("Textures/wordle-bg-4.jpg");
        pauseBackgroundSprite.setTexture(pauseBackgroundTexture);
        Vector2u textureSize = pauseBackgroundTexture.getSize();
        Vector2u windowSize = window.getSize();
        float scaleX = windowSize.x / float(textureSize.x);
        float scaleY = windowSize.y / float(textureSize.y);
        pauseBackgroundSprite.setScale(scaleX, scaleY);
        window.draw(pauseBackgroundSprite); // Draw the pause screen background

        Text pauseText("Game Paused\nPress Escape to Resume", font, 50);
        pauseText.setFillColor(Color::Yellow);
        pauseText.setOutlineColor(Color::Black);
        pauseText.setOutlineThickness(5);
        pauseText.setPosition(window.getSize().x / 2 - pauseText.getLocalBounds().width / 2,
        window.getSize().y / 2 - pauseText.getLocalBounds().height / 2);
        window.draw(pauseText); // Draw pause message
    }
    else
    {
        // If not paused, continue rendering the normal game
        window.draw(instructionText);
        window.draw(scoreText);
        window.draw(attempts);

        int gridWidth = MAX_WORD_LENGTH * TILE_SIZE + (MAX_WORD_LENGTH - 1) * 10;
        int startX = (window.getSize().x - gridWidth) / 2;

        for (int row = 0; row <= currentAttempt; row++)
        {
            if (gameOver && row > currentAttempt - 1) 
            {
                break;
            }
            for (int col = 0; col < MAX_WORD_LENGTH; col++)
            {
                RectangleShape tile(Vector2f(TILE_SIZE, TILE_SIZE));
                tile.setPosition(startX + col * (TILE_SIZE + 10), 100 + row * (TILE_SIZE + 10));
                tile.setFillColor(attemptColors[row][col]);
                tile.setOutlineColor(Color::Black);
                tile.setOutlineThickness(2);
                window.draw(tile);

                char letter = grid.getCell(row, col);
                if (letter != ' ')
                {
                    Text letterText;
                    letterText.setFont(font);
                    letterText.setString(string(1, letter));
                    letterText.setCharacterSize(30);
                    letterText.setFillColor(Color::White);
                    letterText.setOutlineColor(Color::Black);
                    letterText.setOutlineThickness(3);
                    letterText.setPosition(tile.getPosition().x + 20, tile.getPosition().y + 10);
                    window.draw(letterText);
                }
            }
        }

        // Check if the invalid message needs to be displayed
        if (printing_invalidmsg) 
        {
            Text printinvalidmsg;
            printinvalidmsg.setFont(font);
            printinvalidmsg.setString("Word not in the list!\nEnter Again!");
            printinvalidmsg.setOutlineColor(Color::Black);
            printinvalidmsg.setOutlineThickness(10);
            printinvalidmsg.setCharacterSize(20);
            printinvalidmsg.setFillColor(Color::Yellow);
            printinvalidmsg.setStyle(Text::Bold);
            printinvalidmsg.setPosition(20, 300);
            window.draw(printinvalidmsg);
        }

        if (!gameOver)
        {
            keyboard.renderKeyboard(window);
        }

        Text gameOverText;
        Text gameWonText;
        if (isGameWon)
        {
            gameWonText.setFont(font);
            gameWonText.setString("Congratulations!!\n-> You guessed the word correctly!: " + wordManager.getCurrentWord());
            gameWonText.setOutlineColor(Color::Black);
            gameWonText.setOutlineThickness(5);
            gameWonText.setCharacterSize(30);
            gameWonText.setFillColor(Color::Green);
            gameWonText.setStyle(Text::Bold);
            FloatRect textBounds = gameWonText.getLocalBounds();
            gameWonText.setPosition(500 - textBounds.width / 2, 600);
            window.draw(gameWonText);
            window.display();

            Clock clock;
            while (clock.getElapsedTime().asSeconds() < 3) {}
            window.close();
        }
        else if (gameOver)
        {
            // Load and play game over music
            Music gameOverMusic;
            if (!gameOverMusic.openFromFile("Music/gameovervoice.mp3")) 
            {
                cout << "Error loading game over music!" << endl;
            }
            gameOverMusic.setVolume(10); 
            gameOverMusic.setVolume(100);
            gameOverMusic.play();

            // Set up and display the game over text
            gameOverText.setFont(font);
            gameOverText.setString("Game Over! The word was: " + wordManager.getCurrentWord());
            gameOverText.setOutlineColor(Color::Yellow);
            gameOverText.setOutlineThickness(3);
            gameOverText.setCharacterSize(40);
            gameOverText.setFillColor(Color::Red);
            gameOverText.setStyle(Text::Bold);
            FloatRect textBounds = gameOverText.getLocalBounds();
            gameOverText.setPosition(500 - textBounds.width / 2, 600);
            window.draw(gameOverText);
            window.display();

            Clock clock;
            while (clock.getElapsedTime().asSeconds() < 3) {}

            // Stop the game over music and close the window
            gameOverMusic.stop();
            window.close();
        }



    }
}

void WordleGame::togglePause(RenderWindow& window)
{
    paused = !paused; // Toggle pause state
}


void WordleGame::handleMouseClick(Vector2i mousePos, RenderWindow& window)
{
    if (!gameOver) 
    {
        char clickedKey = keyboard.getClickedKey(mousePos);

        if (clickedKey == '\n') 
        {
            handleEnterKey(window);
        }
        else if (clickedKey == '\b') 
        {
            handleBackspaceKey();
        }
        else if (clickedKey != '\0' && currentGuess.size() < MAX_WORD_LENGTH)
        {
            currentGuess += clickedKey;
            grid.updateCell(currentAttempt, currentGuess.size() - 1, clickedKey);
        }
    }
}
bool WordleGame::handleEnterKey(RenderWindow& window)
{
    if (currentGuess.size() == MAX_WORD_LENGTH)
    {
        // Check if the word is valid
        if (!wordManager.isValidWord(currentGuess)) 
        {
            cout << "Word not in the list!\nEnter Again!" << endl;
            // Clear the grid cells for the current guess (do not increment attempts)
            for (int i = 0; i < MAX_WORD_LENGTH; i++) 
            {
                grid.updateCell(currentAttempt, i, ' ');
            }
            currentGuess.clear();  // Clear the current guess
            printing_invalidmsg = true;
            return false;  // Invalid word, do not proceed
        }
        else
        {
            printing_invalidmsg = false;
            // Proceed with the normal flow if the word is valid
            for (int i = 0; i < MAX_WORD_LENGTH; i++) 
            {
                grid.updateCell(currentAttempt, i, currentGuess[i]);
            }
            evaluateAttempt(currentAttempt);
            bool correct = (currentGuess == wordManager.getCurrentWord());
            currentGuess.clear();
            currentAttempt++;  // Increment attempts
            attempttoprint--;
            updateAttemptsText();

            if (correct) 
            {
                scoreManager.updateScore(10);
                updateScoreText();
                gameOver = true;
                isGameWon = true;
            }
            else if (currentAttempt == NUM_ATTEMPTS)
            {
                gameOver = true;
            }

            return correct;
        }
        return false;
    }
}

bool WordleGame::isGameOver()
{
    return gameOver; 
}

bool WordleGame::isGameWonStatus() const 
{
    return isGameWon;
}

const string& WordleGame::getCurrentGuess() const 
{
    return currentGuess; 
}

//PRIVATE WORDLEGAME FUNCTIONS:

void WordleGame::updateScoreText()
{
    scoreText.setString("Score: " + to_string(scoreManager.getScore()));
}
void WordleGame::updateAttemptsText()
{
    attempts.setString("Attempts: " + to_string(attempttoprint));
}
void WordleGame::evaluateAttempt(int attemptIndex) 
{
    string targetWord = wordManager.getCurrentWord();
    bool usedInTarget[MAX_WORD_LENGTH] = { false };

    for (int i = 0; i < MAX_WORD_LENGTH; i++) 
    {
        if (grid.getCell(attemptIndex, i) == targetWord[i])
        {
            attemptColors[attemptIndex][i] = Color::Green;
            usedInTarget[i] = true;
            keyboard.updateKeyboardKeyColor(grid.getCell(attemptIndex, i), Color::Green);
            cout << "You have guessed the alphabet correctly! : " << grid.getCell(attemptIndex, i) << endl;
        }
    }
    for (int i = 0; i < MAX_WORD_LENGTH; i++) 
    {
        if (attemptColors[attemptIndex][i] == Color::Green) continue;

        char guessLetter = grid.getCell(attemptIndex, i);
        bool foundInWord = false;
        for (int j = 0; j < MAX_WORD_LENGTH; j++) 
        {
            if (!usedInTarget[j] && guessLetter == targetWord[j])
            {
                foundInWord = true;
                usedInTarget[j] = true;
                break;
            }
        }
        Color customGray(128, 128, 128); // RGB values for a medium gray
        cout << "You didn't guess the alphabet correctly,Try again : " << guessLetter << endl;
        attemptColors[attemptIndex][i] = foundInWord ? Color::Yellow : customGray;
        keyboard.updateKeyboardKeyColor(guessLetter, attemptColors[attemptIndex][i]);
    }
    cout << endl;
}

void WordleGame::handleBackspaceKey() 
{
    if (!currentGuess.empty()) 
    {
        grid.updateCell(currentAttempt, currentGuess.size() - 1, ' ');
        currentGuess.pop_back();
    }
}

void WordleGame::Run()
{
    if (!font.loadFromFile("BlazeCircuitRegular-xRvxj.ttf")) 
    {
        cout << "Error loading font!" << endl;
    }

    RenderWindow window(VideoMode(1020, 800), "Wordle Game");
    WordleGame game;
    Menu menu;
    bool inMenu = true;
    bool inGame = false;

    // Load background music
    Music backgroundMusic;
    if (!backgroundMusic.openFromFile("Music/wordlemusic.mp3")) 
    {
        cout << "Error loading background music!" << endl;
    }
    backgroundMusic.setLoop(true); // Ensure the music loops until the game is over or the window closes
    backgroundMusic.setVolume(10);
    backgroundMusic.play(); 

    // Load key press sound
    SoundBuffer keySoundBuffer;
    if (!keySoundBuffer.loadFromFile("Music/key.wav"))
    {
        cout << "Error loading key sound!" << endl;
    }

    Sound keySound;
    keySound.setBuffer(keySoundBuffer);
    keySound.setVolume(80);

    Texture backgroundTexture2;
    if (!backgroundTexture2.loadFromFile("Textures/wordle-bg-3.jpg")) 
    { 
        cout << "Error loading background image!" << endl;
    }

    Sprite backgroundSprite2;
    backgroundSprite2.setTexture(backgroundTexture2);
    Vector2u textureSize2 = backgroundTexture2.getSize();
    Vector2u windowSize2 = window.getSize();
    float scaleX2 = windowSize2.x / float(textureSize2.x);  // Use float literals for division
    float scaleY2 = windowSize2.y / float(textureSize2.y);
    backgroundSprite2.setScale(scaleX2, scaleY2);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == Event::Closed) 
            {
                window.close();
            }

            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) 
            {
                game.togglePause(window); // Toggle pause on Escape key press
            }

            if (!game.paused) 
            {
                if (inMenu)
                {
                    // Menu interaction handling
                    int menuResult = menu.displayMenu(window, font);
                    if (menuResult == 0) 
                    { // Start Game
                        inMenu = false;
                        inGame = true;
                        help.showHelp(window, font);
                    }

                    else if (menuResult == 1)
                    { // Quit Game
                        window.close();
                    }
                }
                else if (inGame)
                {
                    if (!game.gameOver) 
                    { 
                        if (event.type == Event::MouseButtonPressed) 
                        {
                            if (event.mouseButton.button == Mouse::Left) 
                            {
                                Vector2i mousePos = Mouse::getPosition(window);
                                game.handleMouseClick(mousePos, window);
                            }
                        }
                        else if (event.type == Event::KeyPressed)
                        {
                            // Play key sound on key press
                            keySound.play();

                            if (event.key.code == Keyboard::Enter) 
                            {
                                game.handleEnterKey(window);
                            }
                            else if (event.key.code == Keyboard::Backspace)
                            {
                                game.handleBackspaceKey();
                            }
                            else
                            {
                                char letter = keyboard::sfKeyToChar(event.key.code);
                                if (letter != '\0' && game.currentGuess.size() < MAX_WORD_LENGTH) 
                                {
                                    game.currentGuess += letter;
                                    game.grid.updateCell(game.currentAttempt, game.currentGuess.size() - 1, letter);
                                }
                            }
                        }
                    }
                }
            }
        }
        window.clear();
        if (inMenu) 
        {
            menu.displayMenu(window, font);
        }

        else if (inGame)
        {
            window.draw(backgroundSprite2);
            game.renderGame(window);
        }

        // Display pause screen if the game is paused
        if (game.paused)
        {
            Text pauseText("Game Paused\nPress Escape to Resume", font, 50);
            pauseText.setFillColor(Color::Yellow);
            pauseText.setOutlineColor(Color::Black);
            pauseText.setOutlineThickness(5);
            pauseText.setPosition(window.getSize().x / 2 - pauseText.getLocalBounds().width / 2,
            window.getSize().y / 2 - pauseText.getLocalBounds().height / 2);
            window.draw(pauseText);
        }
        window.display();
    }

    backgroundMusic.stop();
}



//int main()
//{
//    if (!font.loadFromFile("BlazeCircuitRegular-xRvxj.ttf")) {
//        cout << "Error loading font!" << endl;
//        return -1;
//    }
//    WordleGame game;
//    game.Run();
//    return 0;
//}
