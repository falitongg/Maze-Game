# Documentation - Maze Game

**Author:** Anton Sokolov
**Subject:** B6B36PCC -- Programming in C/C++
**Academic Year:** 2025/2026

---

## 1. Introduction

This project implements a console-based Maze Game in C++. The player moves through a procedurally generated maze with the goal of finding the exit. The maze is generated using a recursive backtracking algorithm.
[![Watch the video](https://img.youtube.com/vi/lKvjPtktGcE/hqdefault.jpg)](https://www.youtube.com/watch?v=lKvjPtktGcE)

### 1.1 Goal of the Game

The player controls a character (`@`) placed at the starting position (top-left corner) and attempts to navigate the maze to reach the exit marked by the symbol `E`. The game ends upon reaching the exit.

### 1.2 Technologies Used

* **Language:** C++20
* **Libraries:**
* `<iostream>` - for input and output
* `<vector>` - for managing the 2D game grid
* `<utility>` - for working with pairs (coordinates)
* `<random>`, `<algorithm>` - for generating random mazes
* `<string>` - for working with text strings


* **Build System:** CMake 3.10+
* **Compiler:** g++ with C++20 support

---

## 2. Project Structure

```
project/
├── game.hpp                  # Header file for the Game class
├── game.cpp                  # Implementation of game logic and game loop
├── maze.hpp                  # Header file for the Maze class
├── maze.cpp                  # Implementation of the maze
├── generator.hpp             # Header file for the maze generator
├── generator.cpp             # Implementation of the recursive backtracking algorithm
├── player.hpp                # Header file for the Player class
├── player.cpp                # Implementation of player movement
├── renderer.hpp              # Header file for the Renderer class
├── renderer.cpp              # Implementation of rendering
├── helper.hpp                # Helper functions
├── helper.cpp                # Implementation of help/tutorial
├── main.cpp                  # Entry point of the program
├── CMakeLists.txt            # CMake configuration file
└── maze_documentation.md     # Documentation

```

### 2.1 File Descriptions

**game.hpp / game.cpp**

* Class `Game` - main game controller
* Management of the game loop (render → input → update)
* Initialization of all components (Maze, Generator, Player, Renderer)
* Menu for selecting maze size

**maze.hpp / maze.cpp**

* Class `Maze` - representation of the maze
* 2D grid with cells (walls `#`, passages `.`, exit `E`)
* Getters and setters for accessing cells
* Boundary and wall checks

**generator.hpp / generator.cpp**

* Class `Generator` - maze generator
* Implementation of the recursive backtracking algorithm
* Creates a perfect maze (exactly one path between any two points)

**player.hpp / player.cpp**

* Class `Player` - representation of the player
* Stores the player's position
* Method `go()` for movement with wall collision checking

**renderer.hpp / renderer.cpp**

* Class `Renderer` - game rendering
* Clears the screen using ANSI sequences
* Draws the maze with the player

**helper.hpp / helper.cpp**

* Function `printHelp()` - displays help with controls

**main.cpp**

* Command line argument processing (`--help`)
* Creation and execution of the Game class instance

---

## 3. Solution Architecture

### 3.1 Object-Oriented Model

The program uses an **object-oriented design** with five main classes:

```
        Game (main controller)
          |
    +-----+-----+-----+-----+
    |     |     |     |     |
  Maze  Gen.  Play. Rend. Helper

```

#### 3.1.1 Game Class

**Responsibility:** High-level game controller

**Main Components:**

```cpp
class Game {
private:
    Maze maze;           // Maze instance
    Generator generator; // Maze generator
    Player player;       // Player
    Renderer renderer;   // Rendering
    bool isRunning;      // Game state

```

**Main Methods:**

* `initialize()` - initializes the game:
* Displays the size selection menu
* Creates a maze of the chosen size
* Generates the maze using `Generator`
* Places the exit and the player


* `run()` - main game loop:
```
while (isRunning) {
    render();      // Draw current state
    handleInput(); // Read and process input
    update();      // Update game state
}

```


* `handleInput()` - processes user input (W/A/S/D/Q/H)
* `update()` - checks the win condition
* `render()` - delegates drawing to Renderer

#### 3.1.2 Maze Class

**Responsibility:** Representation of the maze structure

**Data Structures:**

```cpp
class Maze {
private:
    std::pair<int, int> size;              // Width and height
    std::vector<std::vector<char>> maze;   // 2D grid
    std::pair<int, int> exitCoordinates;   // Exit position

```

**Main Methods:**

* `getCell(x, y)` - returns the character at position [x, y]
* `setCell(x, y, value)` - sets the character at position
* `isInMazeBounds(x, y)` - checks if the position is within bounds
* `isWall(x, y)` - checks if there is a wall at the position
* `getSize()` - returns maze dimensions
* `getExitCoordinates()` / `setExitCoordinates()` - exit management

**Symbols in the Maze:**

* `#` - wall
* `.` - passage (walkable cell)
* `E` - exit
* `@` - player (drawn over the map)

#### 3.1.3 Generator Class

**Responsibility:** Generation of random mazes

**Algorithm:** Recursive backtracking (DFS-based)

**Main Methods:**

* `generate(maze, startX, startY)` - starts generation
* `carvePassages(maze, x, y)` - recursive method:

**Algorithm Principle:**

```
1. Mark current cell as passage ('.')
2. Create a list of 4 directions (up, down, left, right)
3. Shuffle directions randomly
4. For each direction:
   a) Calculate neighbor cell (2 cells away)
   b) If neighbor is in maze and is a wall:
      - Remove wall between current cell and neighbor
      - Recursively continue from neighbor

```

**Properties of Generated Maze:**

* Perfect maze (no loops)
* Exactly one path between any two points
* Fully connected (all cells are accessible)

#### 3.1.4 Player Class

**Responsibility:** Representation and movement of the player

**Data Structures:**

```cpp
class Player {
private:
    std::pair<int, int> currentPosition; // Current position

```

**Main Methods:**

* `go(direction, maze)` - player movement:
```cpp
W/w → up      (y - 1)
S/s → down    (y + 1)
A/a → left    (x - 1)
D/d → right   (x + 1)

```


* Checks movement validity (bounds and walls)
* Movement is executed only if the target cell is not a wall


* `getX()`, `getY()` - position getters
* `setCurrentPosition(x, y)` - sets position

#### 3.1.5 Renderer Class

**Responsibility:** Rendering the game to the console

**Main Methods:**

* `draw(maze, player)`:
* Clears the screen using `clearScreen()`
* Iterates through the entire maze
* Displays `@` at the player's position, otherwise the character from the maze
* Prints the result to the console


* `showTutorial()`:
* Clears the screen
* Displays help
* Waits for Enter


* `clearScreen()` (inline in header):
```cpp
// ANSI escape sequence for clearing the screen
std::cout << " [2J [H";

```



### 3.2 Data Flow and Control

#### 3.2.1 Game Initialization

```
1. main() → creates Game instance
2. Game::initialize():
   ├─→ helloFunction() - displays menu
   │   ├─→ [1] SMALL:  31x15
   │   ├─→ [2] MEDIUM: 51x21
   │   ├─→ [3] LARGE:  101x21
   │   └─→ [4] CUSTOM: user size
   │
   ├─→ customChoice() (if [4])
   │   └─→ dimension validation (11-99, odd numbers)
   │
   ├─→ Maze(width, height) - create maze
   ├─→ generator.generate(maze, 1, 1) - generate
   ├─→ maze.setExitCoordinates() - place exit
   └─→ player = Player(1, 1) - create player at start

```

#### 3.2.2 Game Loop

```
Game::run() {
    while (isRunning) {
        │
        ├─→ render()
        │   └─→ renderer.draw(maze, player)
        │       └─→ Display maze with player
        │
        ├─→ handleInput()
        │   ├─→ Read character from input
        │   ├─→ [Q] → isRunning = false (quit)
        │   ├─→ [H] → renderer.showTutorial()
        │   └─→ [W/A/S/D] → player.go(direction, maze)
        │
        └─→ update()
            └─→ If player == exit:
                ├─→ Display "Congratulations!"
                └─→ isRunning = false
    }
}

```

### 3.3 Input Validation

#### 3.3.1 Maze Size Validation (customChoice)

**Checks:**

* Width and height must be numbers
* Minimum dimension: 11x11
* Maximum dimension: 99x99
* Prevention of excessively large squares (≥ 60x60)
* Automatic conversion to odd numbers (due to generation algorithm)

**Example:**

```
Input: 20x20
Output: 21x21 (rounded up to odd)

```

#### 3.3.2 Player Movement Validation

**Checks in Player::go():**

```cpp
1. Calculate new position based on direction
2. If new position:
   - IS within maze bounds
   - IS NOT a wall
   → Execute movement
   Else → Ignore input

```

---

## 4. Compilation and Execution

### 4.1 Requirements

* C++ compiler with C++20 support (g++, clang++)
* CMake version 3.10 or higher
* Terminal with ANSI escape sequence support (Unix, Linux, macOS, Windows 10+)

### 4.2 Manual Compilation

```bash
g++ -std=c++11 main.cpp game.cpp maze.cpp generator.cpp \
    player.cpp renderer.cpp helper.cpp -o cppsemestralprjct

```

### 4.3 Compilation using CMake

```cmake
# CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(cppsemestralprjct)

set(CMAKE_CXX_STANDARD 20)

add_executable(cppsemestralprjct main.cpp
        maze.hpp
        maze.cpp
        player.hpp
        player.cpp
        renderer.hpp
        renderer.cpp
        game.hpp
        game.cpp
        generator.hpp
        helper.cpp
        helper.hpp
        generator.cpp
)

```

```bash
mkdir build
cd build
cmake ..
cmake --build .

```

### 4.4 Execution

```bash
# Basic execution
./cppsemestralprjct

# Display help
./cppsemestralprjct --help

```

### 4.5 Command Line Arguments

| Argument | Description | Output |
| --- | --- | --- |
| `--help` | Displays help with controls | Prints controls and exits program |

---

## 5. Game Mechanics

### 5.1 Controls

| Key | Action |
| --- | --- |
| `W` or `w` | Move up |
| `S` or `s` | Move down |
| `A` or `a` | Move left |
| `D` or `d` | Move right |
| `H` or `h` | Show help |
| `Q` or `q` | Quit game |

### 5.2 Maze Sizes

#### Preset Sizes:

* **SMALL (31x15):** Suitable for a quick game
* **MEDIUM (51x21):** Medium difficulty
* **LARGE (101x21):** Long maze with a greater challenge

#### Custom Size:

* Minimum dimension: 11x11
* Maximum dimension: 99x99
* Dimensions are automatically adjusted to odd numbers
* Large square mazes (≥ 60x60) are not allowed due to playability

### 5.3 Win Condition

The player wins when their position matches the exit position:

```cpp
if (player.getX() == exitX && player.getY() == exitY) {
    std::cout << "Congratulations! You won\n";
    // End game
}

```

---

## 6. Algorithms and Data Structures

### 6.1 Recursive Backtracking for Maze Generation

**Time Complexity:** O(w × h), where w is width and h is height of the maze

**Space Complexity:** O(w × h) for storing the maze + O(w × h) for the recursion stack (worst case)

**Pseudocode:**

```
function carvePassages(maze, x, y):
    maze[x][y] = '.'  // Mark as passage

    directions = [(0,-2), (0,2), (-2,0), (2,0)]
    shuffle(directions)  // Random order

    for each (dx, dy) in directions:
        nx = x + dx
        ny = y + dy

        if isInBounds(nx, ny) and maze[nx][ny] == '#':
            wallX = (x + nx) / 2
            wallY = (y + ny) / 2
            maze[wallX][wallY] = '.'  // Remove wall
            carvePassages(maze, nx, ny)  // Recursion

```

**Why it works:**

* Starts from one point and gradually "carves" passages
* Visiting neighbors in random order ensures randomness
* Checking "already visited" (`maze[nx][ny] == '#'`) prevents cycles
* Result: connected maze without cycles

### 6.2 Maze Storage

**2D vector:**

```cpp
std::vector<std::vector<char>> maze;

```

**Cell Access:**

```cpp
char cell = maze[y][x];  // Note: [row][column]

```

**Advantages:**

* Dynamic size
* Easy O(1) access
* Intuitive indexing

---

## 7. Functions and Their Descriptions

### 7.1 Global Helper Functions

#### helloFunction()

```cpp
char helloFunction()

```

**Purpose:** Displays the introductory menu and reads the maze size choice
**Return Value:** Character '1'-'4' depending on user choice
**Validation:** Repeats the prompt until a valid choice is entered

#### customChoice()

```cpp
std::pair<int, int> customChoice()

```

**Purpose:** Reads custom maze dimensions from the user
**Return Value:** Pair (width, height) of validated dimensions
**Validation:**

* Check for numeric input
* Range 11-99
* Prevention of excessively large squares
* Conversion to odd numbers

### 7.2 Game Class

#### Game::initialize()

```cpp
void initialize()

```

**Purpose:** Initializes all game components before start
**Steps:**

1. Displays menu and reads size
2. Creates Maze instance
3. Generates maze using Generator
4. Places exit
5. Creates player at start
6. Sets `isRunning = true`

#### Game::run()

```cpp
void run()

```

**Purpose:** Runs the main game loop
**Flow:** Repeats render → handleInput → update, as long as `isRunning == true`

#### Game::handleInput()

```cpp
void handleInput()

```

**Purpose:** Reads and processes one input from the user
**Processes:**

* Q/q: quit
* H/h: help
* W/A/S/D: player movement

#### Game::update()

```cpp
void update()

```

**Purpose:** Updates game state after every action
**Checks:** Whether the player reached the exit

#### Game::render()

```cpp
void render() const

```

**Purpose:** Renders current game state
**Delegates:** Renderer::draw()

### 7.3 Maze Class

#### Maze::Maze(int width, int height)

```cpp
Maze(int width, int height)

```

**Purpose:** Constructor creates a maze of given size
**Initialization:** Sets all cells to '#' (wall)

#### Maze::isInMazeBounds(int x, int y)

```cpp
bool isInMazeBounds(int x, int y) const

```

**Purpose:** Checks if position is inside the maze
**Return Value:** `true` if 0 ≤ x < width and 0 ≤ y < height

#### Maze::isWall(int x, int y)

```cpp
bool isWall(int x, int y) const

```

**Purpose:** Checks if there is a wall at the position
**Return Value:** `true` if `maze[y][x] == '#'`

### 7.4 Generator Class

#### Generator::generate(Maze& maze, int startX, int startY)

```cpp
void generate(Maze& maze, int startX, int startY)

```

**Purpose:** Public interface for maze generation
**Parameters:**

* `maze`: Reference to the maze to fill
* `startX`, `startY`: Starting position (should be odd)

#### Generator::carvePassages(Maze& maze, int x, int y)

```cpp
void carvePassages(Maze& maze, int x, int y)

```

**Purpose:** Recursive method for carving passages
**Algorithm:** See section 6.1

### 7.5 Player Class

#### Player::go(char direction, const Maze& maze)

```cpp
void go(char direction, const Maze& maze)

```

**Purpose:** Attempt to move player in given direction
**Parameters:**

* `direction`: W/A/S/D for direction
* `maze`: Reference to maze (for wall checking)
**Behavior:** Movement is executed only if target is not a wall

### 7.6 Renderer Class

#### Renderer::draw(const Maze& maze, const Player& player)

```cpp
void draw(const Maze& maze, const Player& player) const

```

**Purpose:** Renders the maze with the player to the console
**Steps:**

1. Clears the screen
2. For each cell:
* If player is at position → print '@'
* Else → print character from maze


3. Prints a new line after each maze row

#### Renderer::showTutorial()

```cpp
void showTutorial() const

```

**Purpose:** Displays help with controls
**Steps:**

1. Clears the screen
2. Calls `printHelp()`
3. Waits for Enter

---

## 8. Testing

### 8.1 Functional Testing

#### Test 1: Maze Generation

**Input:** Starting program with size selection
**Expected Result:**

* Maze is generated
* All dimensions match selected size
* Maze is connected (path to exit exists)

#### Test 2: Player Movement

**Input:** Pressing W/A/S/D
**Expected Result:**

* Player moves in corresponding direction
* Player cannot pass through a wall
* Player cannot leave the maze

#### Test 3: Win Condition

**Input:** Reaching the exit
**Expected Result:**

* Message "Congratulations! You won" is displayed
* Game ends

#### Test 4: Quitting Game

**Input:** Pressing Q
**Expected Result:**

* Message "Quitting! Bye!" is displayed
* Program terminates correctly

#### Test 5: Help

**Input:** Pressing H
**Expected Result:**

* Help is displayed
* Game continues after pressing Enter

### 8.2 Boundary Conditions

#### Test Size Validation

```
Input: width = 5, height = 5
Expected: Rejected (< 11)

Input: width = 100, height = 100
Expected: Rejected (≥ 100)

Input: width = 20, height = 20
Expected: Accepted as 21x21 (rounded to odd)

Input: width = 65, height = 65
Expected: Rejected (large square)

```

#### Test Edge Movement

```
Position: (0, 0) - top left corner
Action: Press W or A
Expected: No movement (out of bounds)

```

### 8.3 Test Scenario

**Complex Game Walkthrough:**

```
1. Run program
2. Select size [1] SMALL
3. Verify maze is 31x15
4. Verify player is at position (1,1)
5. Press H - check help
6. Press Enter - continue
7. Move using W/A/S/D
8. Verify movement works correctly
9. Find and reach exit
10. Verify win message

```

---

## 9. Possible Extensions

### 9.1 Game Mechanics

* **Timer:** Measuring completion time
* **Step Counter:** Tracking solution efficiency
* **Mini-map:** Displaying visited areas
* **Fog of War:** Displaying only the player's surroundings

### 9.2 Graphics

* **Colored Characters:** Using ANSI colors for better visualization
* **Different Textures:** Different symbols for different wall types
* **Animations:** Smooth player movement

### 9.3 Algorithms

* **Other Generators:** Prim's algorithm, Kruskal's algorithm
* **Adjustable Difficulty:** More/fewer turns
* **Themed Maze:** Rooms, corridors of varying widths

### 9.4 Multiplayer

* **Race:** Two players look for the exit
* **Co-op:** Collaborative solution of a more complex maze

---

## 10. Known Issues and Limitations

### 10.1 Platform

* **Windows Terminal:** Older Windows versions (< 10) may not support ANSI escape sequences
* **Solution:** Use Windows 10+ or a compatibility library

### 10.2 Performance

* **Large Mazes:** Generating very large mazes (e.g., 99x99) may take longer
* **Recursion:** Deep recursion may cause stack overflow with extremely large dimensions
* **Solution:** Limiting maximum size to 99x99

### 10.3 Usability

* **Input:** Program requires Enter after each input
* **Future Improvement:** Implementation of raw mode for immediate key reaction

---

## 11. Conclusion

This project demonstrates the implementation of a classic maze game in C++ with an emphasis on:

* **Clean object-oriented design** with separated responsibilities
* **Efficient algorithm** for generating random mazes
* **Input validation** and robust error handling
* **Modularity** allowing for easy future extensions

The program meets the basic requirements for a console game and provides a solid foundation for potential improvements.

---

## 12. References and Sources
### 12.1 C++ References

* **std::vector documentation:** [https://en.cppreference.com/w/cpp/container/vector](https://en.cppreference.com/w/cpp/container/vector)
* **std::random documentation:** [https://en.cppreference.com/w/cpp/numeric/random](https://en.cppreference.com/w/cpp/numeric/random)
* **ANSI Escape Sequences:** [https://en.wikipedia.org/wiki/ANSI_escape_code](https://en.wikipedia.org/wiki/ANSI_escape_code)
