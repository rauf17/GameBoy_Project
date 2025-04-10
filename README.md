# 🎮 Classic GameBoy Project

Welcome to the **Classic GameBoy Project** – a retro-inspired gaming platform crafted in modern **C++** using **SFML** and powered by solid **Object-Oriented Programming** principles. Featuring **three classic games** – **Snake Xenia**, **Wordle**, and **Hangman** – this is not just a coding project, it's your own nostalgic gaming universe.

---

## 🎯 Features

- 🕹️ **Multiple Games**: Choose between Snake, Wordle, and Hangman.
- 👤 **Player Profiles**: Player accounts, track scores.
- 📱 **In-Game Console System**: A GameBoy-like menu system with input control and game navigation.
- 🎨 **SFML Graphics**: 2D rendering and animation using SFML.
- 🎼 **Audio Integration**: Retro sound effects for extra immersion.
- 🎵 **Game Over Screen**: Includes a dramatic game-over music effect.
- 🧠 **Modular Code Design**: Easily extensible due to strong OOP architecture.

---

## 🛠️ Installation

1. 📥 Clone the repository:
   ```bash
   git clone https://github.com/rauf17/i230591_OOP_GameBoy_Project.git
   ```

2. 📂 Navigate to the executable directory:
   - Navigate to x64 and run i230591_OOP_GameBoy_Project.exe to play the game!
   

3. ▶️ Run the game:
   - Click on i230591_OOP_GameBoy_Project.exe.


> ⚠️ Make sure all SFML `.dll` files and assets (like music and textures) are in the same directory as the `.exe`.

---

## 🧰 Games Included

- ### 🐍 Snake Xenia

- ### 🧩 Wordle Clone

- ###  💀 Hangman 
---

## 🧱 Object-Oriented Concepts Used

This project was built from the ground up to demonstrate mastery of OOP concepts:

### 🔁 Inheritance
- All games (`SnakeGame`, `WordleGame`, `HangmanGame`) inherit from the abstract base class `Game`.
- This provides a unified `Run()` interface for all games.

### 🔄 Polymorphism
- `GameBoy` uses a `Game*` pointer to run any game type without needing to know its concrete class.
- Enables flexible runtime behavior and uniform function calls across different games.

### 🔗 Composition
- `GameBoy` is composed of core components: `MainMenu`, `Player`, `Leaderboard`, and the current `Game`.
- Each part handles its own logic and responsibilities, making the system modular and extendable.

### 🧺 Aggregation
- `GameBoy` aggregates multiple games and shares access to the `Leaderboard` and `Player` without owning them.
- Promotes reuse and loose coupling between system components.

### 🧊 Abstraction
- The abstract `Game` class defines a clear interface (`Run()`) that all games must implement.
- Details like game logic, rendering, and input handling are hidden behind each game's implementation.

---


## 🕹️ How to Play

- ### 🐍 Snake Xenia
  - Control a snake that grows after eating each mushroom.
  - Avoid colliding with the walls or yourself.
  - Use arrow keys or WASD to move.
  - Increasing speed with growth.
  - Eat coins to get bonus.
  - Tracks high scores per session.

---

- ### 🧩 Wordle Clone
  - Guess the 5-letter word within a limited number of tries.
  - Feedback via colored tiles.
  - Uses a virtual keyboard for input.
  - Input via Keyboard and Mouse both.
  - Tracks performance per session.

---

- ###  💀 Hangman
  - Guess the word letter by letter.
  - Each wrong guess draws part of the hanging man.
  - A limited number of lives.
  - Hints available for tougher words.

---

## ⚙️ Development

This project is built using:

- 💬 **Language**: C++
- 🧰 **Library**: SFML (Simple and Fast Multimedia Library)
  - 🎨 Graphics
  - 🔊 Audio
  - 🪟 Window
  - ⚙️ System
  - 🎮 Events
- 🧱 **Programming Paradigm**: Purely **Object-Oriented Programming (OOP)** concepts
- 💻 **Tools**: Visual Studio, Git, SFML

---

## 👥 Credits

- 🎮 **Game Concept**: Inspired by the original *GameBoy* and its retro charm — reimagined with modern C++ and OOP principles.
- 👨‍💻 **Developer**: Abdul Rauf  
- 🎼 **Music & Art**: Custom or royalty-free resources.

---

## 📬 Contact

For feedback, bugs, or questions, feel free to reach out:

- 📧 **Email**: connect2rauf17@gmail.com  
- 🐙 **GitHub**: [rauf17](https://github.com/rauf17)

---

## 📸 Gameplay

![image](https://github.com/user-attachments/assets/48925ad1-44fb-4832-9d74-d97064cffccd)

![image](https://github.com/user-attachments/assets/d01c3932-de0a-4c9b-a8f0-2b563713e83d)

![image](https://github.com/user-attachments/assets/b68dd625-0f55-4078-89d7-ae7185d0add4)

![image](https://github.com/user-attachments/assets/32035750-f340-466f-8b2f-3de2ac62a3e9)

![image](https://github.com/user-attachments/assets/88ce87be-2904-4385-a1df-3bb4da2c21e9)

![image](https://github.com/user-attachments/assets/859d1d2a-9906-4e79-8301-fab230896684)

![image](https://github.com/user-attachments/assets/813495ac-bffe-4108-acf6-110b75eff189)

![image](https://github.com/user-attachments/assets/dd366008-b08e-47d3-86e5-40a630dbdfaf)

![image](https://github.com/user-attachments/assets/95430ab7-614a-49c7-b3b1-43216b7279ff)

![image](https://github.com/user-attachments/assets/3e1eafaa-19f9-4963-9594-bc187f4b31a8)

![image](https://github.com/user-attachments/assets/903fe5bc-9675-46aa-bd04-56e0445ed876)

![image](https://github.com/user-attachments/assets/aedcc3a5-c6c2-42e9-a1e4-986e4f870650)






