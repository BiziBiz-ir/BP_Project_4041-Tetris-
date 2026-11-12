```
████████╗ ███████╗ ████████╗ ██████╗ ██╗ ███████╗
   ██╔══╝ ██╔════╝ ╚══██╔══╝ ██╔══██╗██║ ██╔════╝
   ██║    █████╗      ██║    ██████╔╝██║ ███████╗
   ██║    ██╔══╝      ██║    ██╔══██╗██║ ╚════██║
   ██║    ███████╗    ██║    ██║  ██║██║ ███████║
   ╚═╝    ╚══════╝    ╚═╝    ╚═╝  ╚═╝╚═╝ ╚══════╝
```

A Tetris game written in C++ for the **BP_4041** course project.

## Features

- Classic Tetris board, 7 block shapes, rotation and collision detection
- Hard drop
- Save / load game, plus an all-time best score
- Colourful UI and ASCII art
- Next-piece preview
- Level system — the game speeds up as you clear lines
- Pause

## Requirements

- A C++17 compiler (`g++` or `clang++`)
- CMake ≥ 3.10
- ncurses development files

Debian / Ubuntu:

```bash
sudo apt install build-essential cmake libncurses-dev
```

## Build

```bash
cmake -S . -B build
cmake --build build -j
```

## Run

The game writes its save files (`best.txt`, `saved_game.txt`, `saved_data.txt`)
to the current directory, so run it from `build/`:

```bash
cd build
./tetris
```

## Controls

| Menu      | Action            |
| --------- | ----------------- |
| `1`       | New game          |
| `2`       | Load saved game   |
| `3`       | Help              |
| `4`       | Exit              |

| In game        | Action            |
| -------------- | ----------------- |
| `A` / `D`, ← → | Move left / right |
| `W`            | Rotate            |
| `Space`        | Hard drop         |
| `P`            | Pause / resume    |
| `S`            | Save and quit     |
| `Q`            | Quit              |

## Project layout

```
.
├── CMakeLists.txt
├── include/        # headers: block.h, game.h, tools.h
├── src/            # sources: main.cpp, block.cpp, game.cpp, tools.cpp
└── README.md
```

## Notes

Save files and build output are not tracked — `build/` and the runtime `.txt`
files are listed in `.gitignore`.
