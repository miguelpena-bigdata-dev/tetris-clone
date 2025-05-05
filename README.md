# Tetris Clone

A classic **Tetris clone** built in **C++** using **SFML 3.0.0** for graphics and input handling. 
This project was created to explore game architecture, object-oriented design, and real-time rendering using a modern multimedia library.

## Features

- Traditional Tetris gameplay with basic scoring
- Grid-based block placement and collision detection
- Next-piece preview
- Rotations with wall kick behavior
- Static linking with SFML 3.0.0
- Modular class-based structure (`Tetranimo`, `Map`, `UserInterface`, etc.)

## Screenshots

*(Add screenshots here if available)*

## Requirements

- [SFML 3.0.0](https://www.sfml-dev.org/download.php)
- GCC / G++ via MSYS2 with UCRT64
- C++17 or newer
- Windows (tested under MSYS2)

## Building

### 1. Install SFML

Download and extract SFML 3.0.0, then copy the `include` and `lib` directories somewhere accessible.

### 2. Compile

You can build the game manually using:

```bash
g++ -fdiagnostics-color=always -g main.cpp map.cpp tetranimo.cpp user_interface.cpp \
    -I"C:/SFML-3.0.0/include" -DSFML_STATIC \
    -o main.exe -L"C:/SFML-3.0.0/lib" \
    -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 -mwindows
```

Or use the provided tasks.json in VS Code to build with a task runner.

3. Run
Make sure the required SFML static libraries are linked correctly, and run:

bash
./main.exe

Project Structure

TetrisClone/
├── main.cpp              # Entry point
├── map.cpp / map.h       # Manages the Tetris grid
├── tetranimo.cpp / .h    # Handles Tetris pieces
├── user_interface.cpp / .h # UI drawing functions
├── randomer.hpp          # Random utility header
├── assets/               # Fonts or other media (if applicable)

Notes
This project uses SFML in static mode. Make sure all required dependencies (like freetype, winmm, etc.) are linked.

Font loading now checks the return value due to [[nodiscard]] in SFML 3.0.0.

License
This project is released under the MIT License.

Built with love for classic games and C++ practice.
