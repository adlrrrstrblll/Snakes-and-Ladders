# Snakes and Ladders in C

## Overview
This is a simple command-line implementation of the classic **Snakes and Ladders** game written in **C**. The game allows players to roll a die, move their pieces across a numbered board, and interact with snakes and ladders along the way.

## Features
- Supports **2 or more players**.
- Simulated **dice rolls**.
- Players encounter **snakes** (which move them down) and **ladders** (which move them up).
- The first player to reach **100** wins.

## How to Play
1. Players take turns rolling the dice.
2. If a player lands at the base of a ladder, they climb up.
3. If a player lands on the head of a snake, they slide down.
4. The first player to reach exactly **100** wins.

## Installation & Compilation
### Prerequisites
Ensure you have a **C compiler** installed. If you're using macOS or Linux, you can use `gcc`. On Windows, you may need **MinGW**.

### Compilation
```sh
gcc snakes_ladders.c -o snakes_ladders
```

### Running the Game
```sh
./snakes_ladders
```

## Code Structure
- `snakes_ladders.c` - Contains the game logic and main loop.
- `snakes_ladders.h` - Header file with function definitions.

## Future Enhancements
- Add a **graphical interface**.
- Implement **networked multiplayer** mode.
- Save and load game progress.

## License
This project is open-source and available under the **MIT License**.

---

Feel free to contribute or suggest improvements! 🚀
