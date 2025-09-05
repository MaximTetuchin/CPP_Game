# 🕹️ Simple Platformer Game

A 2D platformer built with SFML, featuring smooth controls, obstacles, and enemies. Jump, run, and explore different levels!

## 🎮 Features
- Classic platformer movement (jumping, running)
- Animated character
- Simple enemy AI
- Collectibles and obstacles
- Colorful pixel-art style
## Controls

### Basic Controls
- **← / → Arrow Keys** - Move left/right
- **↑ Arrow Key** - Jump (works only when grounded)
- **Spacebar** - Fire current weapon
- **1-4 Keys** - Quick weapon switch:
  - 1 - Pistol
  - 2 - Minigun
  - 3 - Shotgun
  - 4 - Rifle

### Object Interactions
- **Coins (C)** - Auto-collect on contact (+10 coins)
- **Medkits (H)** - Auto-heal on contact (+25 HP)
- **Invincibility Sphere (I)** - Grants temporary invulnerability
- **Speed Berry (S)** - Temporary movement speed boost

### Key Features
- On death (HP = 0) player automatically respawns:
  - Full health restoration
  - Return to starting position
  - Reset all temporary effects
- **Moving Platforms (L/U)** - Automatically traverse levels - just

- ## Requirements

### Development Dependencies
- **C++ Compiler** with C++11 support (g++/clang)
- **SFML 2.5.x** or newer (Graphics and Window modules)
- **CMake** (optional, for build automation)

### Library Includes
```cpp
#include <SFML/Graphics.hpp>  // Main graphics functionality
#include <SFML/Window.hpp>    // Window management
#include <SFML/System.hpp>    // Core system functionality
```
```
sudo apt-get update && sudo apt-get install -y xvfb libsfml-dev libgtest-dev
```
