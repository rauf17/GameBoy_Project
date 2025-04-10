#pragma once

class Game {
public:
    virtual void Run() = 0; // Pure virtual function to be overridden
    virtual ~Game() {}     // Virtual destructor
};

