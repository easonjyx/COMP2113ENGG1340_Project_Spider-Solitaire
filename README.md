# COMP2113ENGG1340_Project_Spider-Solitaire

# Spider Solitaire

A terminal-based **Spider Solitaire** game written in **C++**, suitable for course projects (e.g. COMP2113 / ENGG1340) and local play.

## Features

- **Three difficulties**: 1 suit (easy), 2 suits (medium), 4 suits (hard)
- **Classic spider rules**: build descending sequences in the same suit, full K–A runs are removed automatically, empty columns accept any card or legal stack
- **Deal row**: when stock remains, deal one new face-up card to each of the ten columns
- **Undo**: step back one move
- **Save / load**: persist and restore games from the main menu or during play
- **Move mode toggle**: press `m` to switch between “same-suit stacks only” and “any-suit stacks” (handy for practice or different house rules)

## Requirements

- A **C++11** compiler (e.g. **g++**)
- **GNU Make** to use the provided Makefile (common on Linux and macOS; on Windows, use [MSYS2](https://www.msys2.org/), MinGW, or similar)

## Build and run

### Using the Makefile (recommended)

```bash
make
```

This produces the **`spider`** binary (`spider.exe` on Windows).

Clean build artifacts:

```bash
make clean
```

### Manual build (without Make)

From the project root:

```bash
g++ -pedantic-errors -std=c++11 -o spider \
  main.cpp GameController.cpp DeckManager.cpp eliminate_card.cpp \
  Movecard.cpp MoveRule.cpp GameHistory.cpp SaveLoad.cpp Print_introduction.cpp
```

Run:

```bash
./spider
```

On Windows, if suit symbols render incorrectly, run `chcp 65001` in the console before starting the game.

## Game flow

1. After launch, read the intro and type **`yes`** to open the main menu.
2. Main menu:
   - **1** — New game (then pick difficulty **1**, **2**, or **3**)
   - **2** — View rules
   - **3** — Load a save (enter the filename)
   - **4** — Exit

## In-game commands

Columns are numbered **1–10** (left to right). At the `>` prompt, enter:

| Input | Action |
|--------|--------|
| `h` | Show help |
| `q` | Quit to main menu (confirms with `y` / `n`) |
| `u` | Undo last move |
| `r` | Restart at the same difficulty |
| `m` | Toggle same-suit-only vs any-suit move mode |
| `d` | Deal the next row from stock (needs at least 10 cards in stock) |
| `s <file>` | Save (e.g. `s mysave.bin`) |
| `l <file>` | Load (e.g. `l mysave.bin`) |
| `<n> <src> <dst>` | Move the top **n** cards as one stack from column **src** to **dst** (e.g. `3 5 2` moves 3 cards from column 5 to column 2) |

**Win condition:** remove all **8** same-suit King-through-Ace sequences.

## Project layout (main sources)

| File | Role |
|------|------|
| `main.cpp` | Entry point, main menu, difficulty selection |
| `GameController.cpp` | Game loop, board rendering, command parsing |
| `DeckManager.cpp` | Shuffle, deal, stock, completed-set count |
| `Movecard.cpp` / `MoveRule.cpp` | Move logic and rule checks |
| `eliminate_card.cpp` | Detect and remove completed sequences |
| `GameHistory.cpp` | Undo stack |
| `SaveLoad.cpp` | Save/load on disk |
| `Print_introduction.cpp` | Opening screen |
| `cards.h` | Card data structures |

The repository also contains **`uig.cpp`**, **`gicards.cpp`**, and **`suittest.cpp`**, which are **not linked by the default Makefile**. For submissions or releases, treat the Makefile object list as the canonical build.
