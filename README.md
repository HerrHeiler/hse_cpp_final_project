# hse_cpp_final_project
A repository for final project in the hse dsba c++ course

# Average HSE Student Routine Game

Small C++ game about an ordinary student doing daily routine: walking along a corridor with doors to lecture halls, library, home, etc.

## Project structure

- `src/` – implementation files.
- `include/` – headers.
- `assets/` – textures and fonts.
- `docs/` – design and architecture notes.

## Architecture (short)

- `Game` – owns the window and main loop, forwards events/update/render to `StateManager`.
- `StateManager` – stack of states (`MainMenuState`, `CorridorState`).
- `World` – game world for corridor + rooms, owns `Student` and `Door` objects.
- `Student` – player character, movement, sprite.
- `Door` – clickable/collidable areas leading to rooms.
- `ResourceManager` – loads and caches textures/fonts.

For detailed design see `docs/architecture.md`.
