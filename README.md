# Memorama Game in C++

This project is a simple simulation of the classic "Memorama" game, implemented in C++.

## Features

- Allows users to choose the size of the game board (from 2x2 to 10x10).
- Includes a variety of emojis as cards.
- Supports UTF-8 encoding for emoji display.
- Provides feedback to users during gameplay (e.g., invalid inputs, matched pairs).
- Clears the screen to simulate a "memory test" between turns.

## Requirements

- **Operating System**: The code was tested on **Windows**, but it may also work on other platforms with minor adjustments.
- **Compiler**: Any modern C++ compiler with support for C++11 or later.

> [!IMPORTANT] 
> Proper visualization of emojis depends on the console or terminal's support for UTF-8 encoding. On Windows, the code includes a function to set the code page to UTF-8.

## Game Instructions

1. At the start of the game, you have to enter the size of the board (n x n).
   - The size must be an even number between 2 and 10 (including both numbers).
2. The game will display the emojis for a period of time to help you memorize their positions.
3. Enter the coordinates of two cards you want to flip.
4. If the cards match, they will remain visible; otherwise, they will be hidden again.
5. The game ends when you match all pairs or exceed the allowed number of turns.

### System-Specific Behavior

- **Emoji Support**: The `allowEmojis()` function ensures UTF-8 encoding for emoji display on Windows.
- **Screen Clearing**: Functions like `clearScreen()` and `clearScreenAfterTime()` abstract platform-specific behaviors for clearing the console.

### Game Logic

- The board is represented using a `std::vector<std::string>` for emojis and a `std::vector<bool>` for card visibility.
- A shuffle mechanism ensures random card placement.
- 
### Example Gameplay

```
Introduce the size for the board game (n x n): 4
Time to memorize!

   🐸   🐸   ⚽   ⚽
   🏀   🏀   😎   😎
   😀   😀   😁   😁
   😂   😂   😍   😍

The cards will hide after 8 seconds...
This is your turn #1 of 9 in total.
      ❓      ❓      ❓      ❓
      ❓      ❓      ❓      ❓
      ❓      ❓      ❓      ❓
      ❓      ❓      ❓      ❓

Enter the coordinates for the first card (x y): 1 1
Enter the coordinates for the second card (x y): 1 2
Congratulations! You found the same emoji.
```

## Known Limitations

- The game only supports board sizes up to 10x10.
- Emojis may not render correctly on some older terminals.
- Input validation assumes proper integer inputs (no handling for invalid data types).

## License

This project is open-source and available under the MIT License. Feel free to use, modify, and distribute.

## Acknowledgements
README Structure and Initial Draft: Generated with the assistance of ChatGPT, an AI language model by OpenAI.

## Author

- **Christopher Espinosa**
- **Date**: January 12, 2024
