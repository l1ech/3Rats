# TODO List

## 1. Alpha Version Update

### 1.1 Refactoring

#### Clock
- Structure
  - Add `Time` class in `/core` (functionality taken from `Clock`). [CHECKED]
  - Add `Time` to `Clock`.

- Add `Clock_Manager`.

#### Acteur
- Structure
  - Move `Body` to `/core`. [CHECKED]
  - Move `update` function to `Body` from `Acteur`.

- Add `Acteur_Manager`. [CHECKED]

#### Map
- Generation
  - Overlay a couple of paths to improve map type `Maze`.
  - Add `Gave_yard`.

- Structure
  - make `topology` the new `map_manager`

### 1.2 Bugfix
- Fix issue with textures not drawing correctly.

### 1.3 
- add optional debug for every file

---

## 2. Feature

### 2.1 Teleport Feature
- Implement teleportation if the player clips out of a room.

### 2.2 Stun Class
- Add `Stun` class that can be executed from anywhere in the game.
- Make it halt the player's movement (effectively making them "sleep").
