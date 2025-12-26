# Dokumentace - Maze Game (Hra Bludiště)

**Autor:** Anton Sokolov  
**Předmět:** B6B36PCC -- Programování v C/C++  
**Akademický rok:** 2025/2026  

---

## 1. Úvod

Tento projekt implementuje konzolovou hru Bludiště (Maze Game) v jazyce C++. Hráč se pohybuje po procedurálně generovaném bludišti s cílem najít východ. Bludiště je generováno pomocí algoritmu rekurzivního backtrackingu.

### 1.1 Cíl hry

Hráč ovládá postavu (`@`) umístěnou na startovní pozici (levý horní roh) a snaží se navigovat bludiště, aby dosáhl východu označeného symbolem `E`. Hra končí po dosažení východu.

### 1.2 Použité technologie

- **Jazyk:** C++20
- **Knihovny:**
  - `<iostream>` - pro vstup a výstup
  - `<vector>` - pro správu 2D herní pole
  - `<utility>` - pro práci s páry (souřadnice)
  - `<random>`, `<algorithm>` - pro generování náhodných bludišť
  - `<string>` - pro práci s textovými řetězci
- **Build systém:** CMake 3.10+
- **Kompilátor:** g++ s podporou C++20

---

## 2. Struktura projektu

```
project/
├── game.hpp                  # Hlavičkový soubor třídy Game
├── game.cpp                  # Implementace herní logiky a game loopu
├── maze.hpp                  # Hlavičkový soubor třídy Maze
├── maze.cpp                  # Implementace bludiště
├── generator.hpp             # Hlavičkový soubor generátoru bludiště
├── generator.cpp             # Implementace rekurzivního backtracking algoritmu
├── player.hpp                # Hlavičkový soubor třídy Player
├── player.cpp                # Implementace pohybu hráče
├── renderer.hpp              # Hlavičkový soubor třídy Renderer
├── renderer.cpp              # Implementace vykreslování
├── helper.hpp                # Pomocné funkce
├── helper.cpp                # Implementace nápovědy
├── main.cpp                  # Vstupní bod programu
├── CMakeLists.txt            # Konfigurační soubor pro CMake
└── maze_documentation.md     # Dokumentace
```

### 2.1 Popis souborů

**game.hpp / game.cpp**
- Třída `Game` - hlavní kontrolér hry
- Správa herní smyčky (render → input → update)
- Inicializace všech komponent (Maze, Generator, Player, Renderer)
- Menu pro výběr velikosti bludiště

**maze.hpp / maze.cpp**
- Třída `Maze` - reprezentace bludiště
- 2D grid s buňkami (zdi `#`, chodby `.`, východ `E`)
- Gettery a settery pro přístup k buňkám
- Kontrola hranic a zdí

**generator.hpp / generator.cpp**
- Třída `Generator` - generátor bludiště
- Implementace rekurzivního backtracking algoritmu
- Vytváří perfektní bludiště (právě jedna cesta mezi každými dvěma body)

**player.hpp / player.cpp**
- Třída `Player` - reprezentace hráče
- Uchovává pozici hráče
- Metoda `go()` pro pohyb se kontrolou kolizí se zdmi

**renderer.hpp / renderer.cpp**
- Třída `Renderer` - vykreslování hry
- Čistí obrazovku pomocí ANSI sekvencí
- Vykresluje bludiště s hráčem

**helper.hpp / helper.cpp**
- Funkce `printHelp()` - zobrazí nápovědu s ovládáním

**main.cpp**
- Zpracování argumentů příkazové řádky (`--help`)
- Vytvoření a spuštění instance třídy Game

---

## 3. Architektura řešení

### 3.1 Objektově orientovaný model

Program využívá **objektově orientovaný design** s pěti hlavními třídami:

```
        Game (hlavní kontrolér)
          |
    +-----+-----+-----+-----+
    |     |     |     |     |
  Maze  Gen.  Play. Rend. Helper
```

#### 3.1.1 Třída Game

**Odpovědnost:** Vysokoúrovňový kontrolér hry

**Hlavní komponenty:**
```cpp
class Game {
private:
    Maze maze;           // Instance bludiště
    Generator generator; // Generátor bludiště
    Player player;       // Hráč
    Renderer renderer;   // Vykreslování
    bool isRunning;      // Stav hry
```

**Hlavní metody:**
- `initialize()` - inicializuje hru:
  - Zobrazí menu pro výběr velikosti
  - Vytvoří bludiště zvolené velikosti
  - Vygeneruje bludiště pomocí `Generator`
  - Umístí východ a hráče
- `run()` - hlavní herní smyčka:
  ```
  while (isRunning) {
      render();      // Vykresli aktuální stav
      handleInput(); // Načti a zpracuj vstup
      update();      // Aktualizuj stav hry
  }
  ```
- `handleInput()` - zpracovává vstup uživatele (W/A/S/D/Q/H)
- `update()` - kontroluje výherní podmínku
- `render()` - deleguje vykreslení na Renderer

#### 3.1.2 Třída Maze

**Odpovědnost:** Reprezentace struktury bludiště

**Datové struktury:**
```cpp
class Maze {
private:
    std::pair<int, int> size;              // Šířka a výška
    std::vector<std::vector<char>> maze;   // 2D grid
    std::pair<int, int> exitCoordinates;   // Pozice východu
```

**Hlavní metody:**
- `getCell(x, y)` - vrací znak na pozici [x, y]
- `setCell(x, y, value)` - nastaví znak na pozici
- `isInMazeBounds(x, y)` - kontrola, zda je pozice v hranicích
- `isWall(x, y)` - kontrola, zda je na pozici zeď
- `getSize()` - vrací rozměry bludiště
- `getExitCoordinates()` / `setExitCoordinates()` - práce s východem

**Symboly v bludišti:**
- `#` - zeď
- `.` - chodba (průchozí buňka)
- `E` - východ
- `@` - hráč (vykreslován přes mapu)

#### 3.1.3 Třída Generator

**Odpovědnost:** Generování náhodných bludišť

**Algoritmus:** Rekurzivní backtracking (DFS-based)

**Hlavní metody:**
- `generate(maze, startX, startY)` - spustí generování
- `carvePassages(maze, x, y)` - rekurzivní metoda:

**Princip algoritmu:**
```
1. Označ aktuální buňku jako chodbu ('.')
2. Vytvoř seznam 4 směrů (nahoru, dolů, vlevo, vpravo)
3. Zamíchej směry náhodně
4. Pro každý směr:
   a) Vypočti sousední buňku (2 buňky daleko)
   b) Pokud je soused v bludišti a je to zeď:
      - Odstraň zeď mezi aktuální buňkou a sousedem
      - Rekurzivně pokračuj ze souseda
```

**Vlastnosti generovaného bludiště:**
- Perfektní bludiště (žádné cykly)
- Právě jedna cesta mezi každými dvěma body
- Plně souvislé (všechny buňky jsou dostupné)

#### 3.1.4 Třída Player

**Odpovědnost:** Reprezentace a pohyb hráče

**Datové struktury:**
```cpp
class Player {
private:
    std::pair<int, int> currentPosition; // Aktuální pozice
```

**Hlavní metody:**
- `go(direction, maze)` - pohyb hráče:
  ```cpp
  W/w → nahoru    (y - 1)
  S/s → dolů      (y + 1)
  A/a → vlevo     (x - 1)
  D/d → vpravo    (x + 1)
  ```
  - Kontroluje validitu pohybu (hranice a zdi)
  - Pohyb se provede pouze pokud cílová buňka není zeď

- `getX()`, `getY()` - gettery pozice
- `setCurrentPosition(x, y)` - nastaví pozici

#### 3.1.5 Třída Renderer

**Odpovědnost:** Vykreslování hry do konzole

**Hlavní metody:**
- `draw(maze, player)`:
  - Vyčistí obrazovku pomocí `clearScreen()`
  - Projde celé bludiště
  - Na pozici hráče zobrazí `@`, jinak znak z bludiště
  - Vytiskne výsledek do konzole

- `showTutorial()`:
  - Vyčistí obrazovku
  - Zobrazí nápovědu
  - Čeká na Enter

- `clearScreen()` (inline v hlavičce):
  ```cpp
  // ANSI escape sekvence pro čištění obrazovky
  std::cout << "[2J[H";
  ```

### 3.2 Tok dat a řízení

#### 3.2.1 Inicializace hry

```
1. main() → vytvoří instanci Game
2. Game::initialize():
   ├─→ helloFunction() - zobrazí menu
   │   ├─→ [1] SMALL:  31x15
   │   ├─→ [2] MEDIUM: 51x21
   │   ├─→ [3] LARGE:  101x21
   │   └─→ [4] CUSTOM: uživatelská velikost
   │
   ├─→ customChoice() (pokud [4])
   │   └─→ validace rozměrů (11-99, lichá čísla)
   │
   ├─→ Maze(width, height) - vytvoř bludiště
   ├─→ generator.generate(maze, 1, 1) - vygeneruj
   ├─→ maze.setExitCoordinates() - umísti východ
   └─→ player = Player(1, 1) - vytvoř hráče na startu
```

#### 3.2.2 Herní smyčka

```
Game::run() {
    while (isRunning) {
        │
        ├─→ render()
        │   └─→ renderer.draw(maze, player)
        │       └─→ Zobrazí bludiště s hráčem
        │
        ├─→ handleInput()
        │   ├─→ Načti znak ze vstupu
        │   ├─→ [Q] → isRunning = false (ukončení)
        │   ├─→ [H] → renderer.showTutorial()
        │   └─→ [W/A/S/D] → player.go(direction, maze)
        │
        └─→ update()
            └─→ Pokud hráč == exit:
                ├─→ Zobraz "Congratulations!"
                └─→ isRunning = false
    }
}
```

### 3.3 Validace vstupu

#### 3.3.1 Validace velikosti bludiště (customChoice)

**Kontroly:**
- Šířka a výška musí být čísla
- Minimální rozměr: 11x11
- Maximální rozměr: 99x99
- Zamezení příliš velkých čtverců (≥ 60x60)
- Automatická konverze na lichá čísla (kvůli algoritmu generování)

**Příklad:**
```
Vstup: 20x20
Výstup: 21x21 (zaokrouhleno nahoru na liché)
```

#### 3.3.2 Validace pohybu hráče

**Kontroly v Player::go():**
```cpp
1. Spočti novou pozici podle směru
2. Pokud nová pozice:
   - JE v hranicích bludiště
   - NENÍ zeď
   → Proved pohyb
   Jinak → Ignoruj vstup
```

---

## 4. Kompilace a spuštění

### 4.1 Požadavky

- C++ kompilátor s podporou C++20 (g++, clang++)
- CMake verze 3.10 nebo vyšší
- Terminál s podporou ANSI escape sekvencí (Unix, Linux, macOS, Windows 10+)

### 4.2 Ruční kompilace

```bash
g++ -std=c++11 main.cpp game.cpp maze.cpp generator.cpp \
    player.cpp renderer.cpp helper.cpp -o cppsemestralprjct
```

### 4.3 Kompilace pomocí CMake

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

### 4.4 Spuštění

```bash
# Základní spuštění
./cppsemestralprjct

# Zobrazení nápovědy
./cppsemestralprjct --help
```

### 4.5 Argumenty příkazové řádky

| Argument | Popis | Výstup |
|----------|-------|--------|
| `--help` | Zobrazí nápovědu s ovládáním | Vypíše ovládání a ukončí program |

---

## 5. Herní mechaniky

### 5.1 Ovládání

| Klávesa | Akce |
|---------|------|
| `W` nebo `w` | Pohyb nahoru |
| `S` nebo `s` | Pohyb dolů |
| `A` nebo `a` | Pohyb vlevo |
| `D` nebo `d` | Pohyb vpravo |
| `H` nebo `h` | Zobrazit nápovědu |
| `Q` nebo `q` | Ukončit hru |

### 5.2 Velikosti bludišť

#### Přednastavené velikosti:

- **SMALL (31x15):** Vhodné pro rychlou hru
- **MEDIUM (51x21):** Střední obtížnost
- **LARGE (101x21):** Dlouhé bludiště s větší výzvou

#### Vlastní velikost:

- Minimální rozměr: 11x11
- Maximální rozměr: 99x99
- Rozměry jsou automaticky upraveny na lichá čísla
- Velké čtvercové bludiště (≥ 60x60) nejsou povoleny kvůli hratelnosti

### 5.3 Výherní podmínka

Hráč vyhraje, když jeho pozice odpovídá pozici východu:
```cpp
if (player.getX() == exitX && player.getY() == exitY) {
    std::cout << "Congratulations! You won\n";
    // Ukončení hry
}
```

---

## 6. Algoritmy a datové struktury

### 6.1 Rekurzivní backtracking pro generování bludiště

**Časová složitost:** O(w × h), kde w je šířka a h výška bludiště

**Prostorová složitost:** O(w × h) pro uložení bludiště + O(w × h) pro zásobník rekurze (worst case)

**Pseudokód:**
```
function carvePassages(maze, x, y):
    maze[x][y] = '.'  // Označ jako chodbu

    directions = [(0,-2), (0,2), (-2,0), (2,0)]
    shuffle(directions)  // Náhodné pořadí

    for each (dx, dy) in directions:
        nx = x + dx
        ny = y + dy

        if isInBounds(nx, ny) and maze[nx][ny] == '#':
            wallX = (x + nx) / 2
            wallY = (y + ny) / 2
            maze[wallX][wallY] = '.'  // Odstraň zeď
            carvePassages(maze, nx, ny)  // Rekurze
```

**Proč funguje:**
- Začíná z jednoho bodu a postupně "vysekává" chodby
- Návštěva sousedů v náhodném pořadí zajišťuje náhodnost
- Kontrola "už navštíveno" (`maze[nx][ny] == '#'`) zabraňuje cyklům
- Výsledek: souvislé bludiště bez cyklů

### 6.2 Uložení bludiště

**2D vector:**
```cpp
std::vector<std::vector<char>> maze;
```

**Přístup k buňce:**
```cpp
char cell = maze[y][x];  // Pozor: [řádek][sloupec]
```

**Výhody:**
- Dynamická velikost
- Snadný přístup O(1)
- Intuitivní indexování

---

## 7. Funkce a jejich popis

### 7.1 Globální pomocné funkce

#### helloFunction()
```cpp
char helloFunction()
```
**Účel:** Zobrazí úvodní menu a přečte volbu velikosti bludiště  
**Návratová hodnota:** Znak '1'-'4' podle volby uživatele  
**Validace:** Opakuje dotaz, dokud není zadána platná volba

#### customChoice()
```cpp
std::pair<int, int> customChoice()
```
**Účel:** Načte vlastní rozměry bludiště od uživatele  
**Návratová hodnota:** Pár (šířka, výška) validovaných rozměrů  
**Validace:**
- Kontrola číselného vstupu
- Rozsah 11-99
- Zamezení příliš velkých čtverců
- Konverze na lichá čísla

### 7.2 Třída Game

#### Game::initialize()
```cpp
void initialize()
```
**Účel:** Inicializuje všechny komponenty hry před startem  
**Kroky:**
1. Zobrazí menu a načte velikost
2. Vytvoří instanci Maze
3. Vygeneruje bludiště pomocí Generator
4. Umístí východ
5. Vytvoří hráče na startu
6. Nastaví `isRunning = true`

#### Game::run()
```cpp
void run()
```
**Účel:** Spustí hlavní herní smyčku  
**Průběh:** Opakuje render → handleInput → update, dokud je `isRunning == true`

#### Game::handleInput()
```cpp
void handleInput()
```
**Účel:** Načte a zpracuje jeden vstup od uživatele  
**Zpracovává:**
- Q/q: ukončení
- H/h: nápověda
- W/A/S/D: pohyb hráče

#### Game::update()
```cpp
void update()
```
**Účel:** Aktualizuje stav hry po každé akci  
**Kontroluje:** Zda hráč dosáhl východu

#### Game::render()
```cpp
void render() const
```
**Účel:** Vykreslí aktuální stav hry  
**Deleguje:** Renderer::draw()

### 7.3 Třída Maze

#### Maze::Maze(int width, int height)
```cpp
Maze(int width, int height)
```
**Účel:** Konstruktor vytvoří bludiště dané velikosti  
**Inicializace:** Všechny buňky nastaví na '#' (zeď)

#### Maze::isInMazeBounds(int x, int y)
```cpp
bool isInMazeBounds(int x, int y) const
```
**Účel:** Kontrola, zda je pozice uvnitř bludiště  
**Návratová hodnota:** `true` pokud 0 ≤ x < width a 0 ≤ y < height

#### Maze::isWall(int x, int y)
```cpp
bool isWall(int x, int y) const
```
**Účel:** Kontrola, zda je na pozici zeď  
**Návratová hodnota:** `true` pokud `maze[y][x] == '#'`

### 7.4 Třída Generator

#### Generator::generate(Maze& maze, int startX, int startY)
```cpp
void generate(Maze& maze, int startX, int startY)
```
**Účel:** Veřejné rozhraní pro generování bludiště  
**Parametry:**
- `maze`: Reference na bludiště k vyplnění
- `startX`, `startY`: Startovní pozice (měly by být liché)

#### Generator::carvePassages(Maze& maze, int x, int y)
```cpp
void carvePassages(Maze& maze, int x, int y)
```
**Účel:** Rekurzivní metoda pro vysekávání chodeb  
**Algoritmus:** Viz sekce 6.1

### 7.5 Třída Player

#### Player::go(char direction, const Maze& maze)
```cpp
void go(char direction, const Maze& maze)
```
**Účel:** Pokus o pohyb hráče v daném směru  
**Parametry:**
- `direction`: W/A/S/D pro směr
- `maze`: Reference na bludiště (pro kontrolu zdí)  
**Chování:** Pohyb se provede pouze pokud cíl není zeď

### 7.6 Třída Renderer

#### Renderer::draw(const Maze& maze, const Player& player)
```cpp
void draw(const Maze& maze, const Player& player) const
```
**Účel:** Vykreslí bludiště s hráčem do konzole  
**Kroky:**
1. Vyčistí obrazovku
2. Pro každou buňku:
   - Pokud je na pozici hráč → vypíše '@'
   - Jinak → vypíše znak z bludiště
3. Vypíše nový řádek po každém řádku bludiště

#### Renderer::showTutorial()
```cpp
void showTutorial() const
```
**Účel:** Zobrazí nápovědu s ovládáním  
**Kroky:**
1. Vyčistí obrazovku
2. Zavolá `printHelp()`
3. Čeká na Enter

---

## 8. Testování

### 8.1 Funkční testování

#### Test 1: Generování bludiště
**Vstup:** Spuštění programu s volbou velikosti  
**Očekávaný výsledek:**
- Bludiště je vygenerováno
- Všechny rozměry odpovídají zvolené velikosti
- Bludiště je souvislé (existuje cesta k východu)

#### Test 2: Pohyb hráče
**Vstup:** Stisknutí W/A/S/D  
**Očekávaný výsledek:**
- Hráč se pohybuje odpovídajícím směrem
- Hráč nemůže projít zdí
- Hráč nemůže opustit bludiště

#### Test 3: Výherní podmínka
**Vstup:** Dosažení východu  
**Očekávaný výsledek:**
- Zobrazí se zpráva "Congratulations! You won"
- Hra se ukončí

#### Test 4: Ukončení hry
**Vstup:** Stisknutí Q  
**Očekávaný výsledek:**
- Zobrazí se zpráva "Quitting! Bye!"
- Program se korektně ukončí

#### Test 5: Nápověda
**Vstup:** Stisknutí H  
**Očekávaný výsledek:**
- Zobrazí se nápověda
- Po stisku Enter pokračuje hra

### 8.2 Hraniční podmínky

#### Test validace velikosti
```
Vstup: width = 5, height = 5
Očekáváno: Zamítnuto (< 11)

Vstup: width = 100, height = 100
Očekáváno: Zamítnuto (≥ 100)

Vstup: width = 20, height = 20
Očekáváno: Přijato jako 21x21 (zaokrouhleno na liché)

Vstup: width = 65, height = 65
Očekáváno: Zamítnuto (velký čtverec)
```

#### Test pohybu na okraji
```
Pozice: (0, 0) - levý horní roh
Akce: Stisknutí W nebo A
Očekáváno: Žádný pohyb (mimo hranice)
```

### 8.3 Testovací scénář

**Komplexní test průchodu hrou:**
```
1. Spusť program
2. Zvol velikost [1] SMALL
3. Ověř, že bludiště je 31x15
4. Ověř, že hráč je na pozici (1,1)
5. Stiskni H - zkontroluj nápovědu
6. Stiskni Enter - pokračuj
7. Pohybuj se pomocí W/A/S/D
8. Ověř, že pohyb funguje správně
9. Najdi a dosáhni východu
10. Ověř výherní zprávu
```

---

## 9. Možná rozšíření

### 9.1 Herní mechaniky
- **Časomíra:** Měření času dokončení
- **Počítadlo kroků:** Sledování efektivity řešení
- **Mini-mapa:** Zobrazení navštívených oblastí
- **Mlha války:** Zobrazovat pouze okolí hráče

### 9.2 Grafika
- **Barevné znaky:** Použití ANSI barev pro lepší vizualizaci
- **Různé textury:** Různé symboly pro různé typy zdí
- **Animace:** Plynulý pohyb hráče

### 9.3 Algoritmy
- **Další generátory:** Prim's algorithm, Kruskal's algorithm
- **Nastavitelná obtížnost:** Více/méně zatáček
- **Tematické bludiště:** Místnosti, chodby různých šířek

### 9.4 Multiplayer
- **Závod:** Dva hráči hledají východ
- **Kooperace:** Společné řešení složitějšího bludiště

---

## 10. Známé problémy a omezení

### 10.1 Platforma
- **Windows terminál:** Starší verze Windows (< 10) nemusí podporovat ANSI escape sekvence
- **Řešení:** Použít Windows 10+ nebo knihovnu pro kompatibilitu

### 10.2 Výkon
- **Velká bludiště:** Generování velmi velkých bludišť (např. 99x99) může trvat déle
- **Rekurze:** Hluboká rekurze může způsobit stack overflow u extrémně velkých rozměrů
- **Řešení:** Omezení maximální velikosti na 99x99

### 10.3 Použitelnost
- **Vstup:** Program vyžaduje Enter po každém vstupu
- **Budoucí zlepšení:** Implementace raw mode pro okamžitou reakci na klávesy

---

## 11. Závěr

Tento projekt demonstruje implementaci klasické bludiště hry v C++ s důrazem na:
- **Čistý objektově orientovaný design** s oddělenými odpovědnostmi
- **Efektivní algoritmus** pro generování náhodných bludišť
- **Validaci vstupů** a robustní zpracování chyb
- **Modularitu** umožňující snadná budoucí rozšíření

Program splňuje základní požadavky pro konzolovou hru a poskytuje solidní základ pro případná vylepšení.

---

## 12. Reference a použité zdroje

### 12.1 Algoritmy
- **Recursive Backtracking Maze Generation:**  
  Jamis Buck, "Mazes for Programmers", The Pragmatic Bookshelf, 2015

### 12.2 C++ Reference
- **std::vector dokumentace:** https://en.cppreference.com/w/cpp/container/vector
- **std::random dokumentace:** https://en.cppreference.com/w/cpp/numeric/random
- **ANSI Escape Sequences:** https://en.wikipedia.org/wiki/ANSI_escape_code

---

**Konec dokumentace**
