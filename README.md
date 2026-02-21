# hse_cpp_final_project
A repository for final project in the HSE DSBA C++ course

# Average HSE Student Routine Game

Small C++ game about an ordinary student doing daily routine: walking along a corridor with doors to lecture halls, library, home, etc.

## Project structure

- `src/` – implementation files
- `include/` – headers
- `assets/` – textures and fonts
- `docs/` – design and architecture notes

## Architecture (short)

- `Game` – owns the window and main loop, forwards events/update/render to `StateManager`
- `StateManager` – stack of states (`MainMenuState`, `CorridorState`)
- `World` – game world for corridor + rooms, owns `Student` and `Door` objects
- `Student` – player character, movement, sprite
- `Door` – clickable/collidable areas leading to rooms
- `ResourceManager` – loads and caches textures/fonts

For detailed design see `docs/architecture.md`.

---

## For programmers

### Dependencies

- CMake ≥ 3.10  
- C++17 compiler  
- **SFML 3.0+**

#### macOS (Homebrew)

Install:

```bash
brew install cmake sfml
```

By default SFML CMake config will be at:

```bash
/opt/homebrew/opt/sfml/lib/cmake/SFML
```
If it differs, pass your path explicitly when configuring:

```bash
cmake .. -DSFML_DIR=/path/to/sfml/lib/cmake/SFML
```
Build
```bash
git clone https://github.com/.../hse_cpp_final_project.git
cd hse_cpp_final_project

mkdir build
cd build

cmake .. -DSFML_DIR=/opt/homebrew/opt/sfml/lib/cmake/SFML
cmake --build .
```
Run
From the project root (so relative assets/ paths work):

```bash
cd hse_cpp_final_project
./build/student-game
```