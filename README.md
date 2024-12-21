# TODO List

## 1. Alpha Version Update

### 1.1 Refactoring

#### Clock
- Add `Time` class in `/core` (functionality taken from `Clock`).
- Add `Time` to `Clock`.
- Add `Clock_Manager`.

#### Acteur
- Add `Acteur_Manager`.
- ~~Move `Body` to `/core`. ~~
- Move `update` function to `Body` from `Acteur`.

#### Map
- Overlay a couple of paths to create `maze::type`.
- Add map grave-yard.
- make topology new map_manager

### 1.2 Bugfix
- Fix issue with textures not drawing correctly.

---

## 2. Feature

### 2.1 Teleport Feature
- Implement teleportation if the player clips out of a room.

### 2.2 Stun Class
- Add `Stun` class that can be executed from anywhere in the game.
- Make it halt the player's movement (effectively making them "sleep").
