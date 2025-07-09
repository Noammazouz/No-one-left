# No One Left - Combat Survival Game

No One Left is a top-down combat survival game where the player controls a soldier trying to eliminate all enemies in a hostile environment while avoiding enemy fire and using strategic positioning.
The game is implemented using C++ and SFML (Simple and Fast Multimedia Library) for graphics rendering and audio.

## Overview

In No One Left, the player controls a soldier character navigating through combat zones filled with enemies, obstacles, and useful items.
The objective is to eliminate all enemies while managing health, ammunition, and strategic positioning.
The game features intense combat scenarios with different enemy types, multiple weapon systems, and destructible environments.
Players must use strategy, quick reflexes, and resource management to survive and complete their mission.

## Features

- **Player Control**: Navigate the soldier character using arrow keys, shoot with 'S', and place bombs with 'B'.
- **Weapon Systems**: Multiple weapons including rifles, machine guns, and bazookas with different firing rates and damage.
- **Enemy AI**: Multiple AI types - Simple (random movement), Smart (advanced pathfinding), and BFS (direct player tracking).
- **Collision Detection**: Handle interactions between player, enemies, projectiles, and environmental objects.
- **Destructible Environment**: Use weapons and bombs to destroy obstacles and create strategic paths.
- **Resource Management**: Manage health, ammunition, and bombs throughout combat.
- **Gift System**: Collect weapon upgrades, ammunition, health packs, and special items.
- **Sound Effects and Music**: Immersive combat audio with background music and sound effects.
- **User Interface**: Comprehensive UI showing health, ammunition, bombs, enemies remaining, and game controls.

## Game Objects

- **Player**: Soldier controlled by the player with health, weapons, and movement abilities.
- **Enemies**: Multiple enemy types with different AI behaviors - Simple (random), Smart (pathfinding), and BFS (direct tracking).
- **Weapons**: Rifle, Machine Gun, and Bazooka with different characteristics.
- **Projectiles**: Bullets fired by player and enemies with collision detection.
- **Bombs**: Explosive devices that can destroy obstacles and enemies.
- **Explosions**: Area damage effects from bombs and bazooka rounds.
- **Obstacles**: Destructible environmental barriers that provide cover.
- **Walls**: Indestructible boundaries and structures.
- **Gifts**: Various power-ups including weapons, ammunition, health, and special items.

## Controls

- **Arrow Keys**: Move player character
- **S Key**: Shoot current weapon
- **B Key**: Place bomb
- **M Key**: Mute/unmute music
- **Escape Key**: Return to main menu
- **Mouse**: Navigate menus and interact with buttons

## Files

### Headers

- **Player.h**: Declares the `Player` class representing the player-controlled soldier character.
- **Enemy.h**: Contains the `Enemy` class declaration representing enemy characters with AI behavior.
- **GameObject.h**: Contains the `GameObject` class declaration, base class for all game objects.
- **UpdateableObject.h**: Base class for moving/animated game objects.
- **StaticObject.h**: Base class for stationary game objects.
- **Projectile.h**: Declares the `Projectile` class for bullets and projectiles.
- **Bomb.h**: Contains the `Bomb` class declaration for explosive devices with timed detonation.
- **Explosion.h**: Declares the `Explosion` class for area damage effects from bomb detonations.
- **Obstacles.h**: Contains obstacle class declarations for destructible barriers.
- **Wall.h**: Declares the `Wall` class for indestructible boundaries.
- **ItemsToCollect.h**: Base class for all collectible items in the game.
- **WeaponsGift.h**: Base class for weapon upgrade items, inherits from ItemsToCollect.
- **RifleGift.h**: Declares rifle weapon upgrade items.
- **MachineGunGift.h**: Declares machine gun weapon upgrade items.
- **BazookaGift.h**: Declares bazooka weapon upgrade items.
- **BulletsGift.h**: Declares ammunition pickup items.
- **MedkitGift.h**: Declares health restoration items (inherits from ItemsToCollect).
- **IncreasingLife.h**: Alternative health item implementation.
- **RemoveEnemy.h**: Declares special items that eliminate random enemies.
- **RemoveTime.h**: Declares items that reduce mission timer.
- **Map.h**: Contains the `Map` class for level loading and management.
- **Controller.h**: Contains the `Controller` class for game state management.
- **Infobar.h**: Manages the game's user interface displaying health, ammunition, bombs, enemies, and timer.
- **ResourcesManager.h**: Manages loading and storage of game resources.
- **MusicManager.h**: Manages background music with fade transitions, different music types, and volume control.
- **Screen/**: Directory containing all screen management classes.
- **AttackBehavior.h**: Base class for enemy attack patterns.
- **MoveBehavior.h**: Base class for enemy movement patterns.
- **CollisionFactory.h**: Handles collision detection between objects.
- **Const.h**: Contains game constants and configuration values.

### Source Files (CPP)

- **Player.cpp**: Implements player movement, shooting, and interaction systems.
- **Enemy.cpp**: Implements enemy AI, movement, and combat behaviors.
- **GameObject.cpp**: Base implementation for all game objects.
- **UpdateableObject.cpp**: Base implementation for moving objects.
- **StaticObject.cpp**: Base implementation for static objects.
- **Projectile.cpp**: Implements bullet physics and collision.
- **Bomb.cpp**: Implements bomb placement, timing, and explosion logic.
- **Explosion.cpp**: Implements explosion effects and area damage.
- **Map.cpp**: Implements hybrid level loading with CSV files and random object placement.
- **Controller.cpp**: Main game loop and state management.
- **Infobar.cpp**: Implements the UI information bar with real-time game statistics.
- **ResourcesManager.cpp**: Resource loading and management implementation.
- **MusicManager.cpp**: Complete audio system with fade transitions, menu/game/win/lose music types.
- **CollisionFactory.cpp**: Collision detection and response system.
- **Movement Behaviors**: RandomMoveBehavior.cpp, AxisMoveBehavior.cpp, BfsMoveBehavior.cpp - different enemy AI patterns.
- **Attack Behaviors**: OneDirectionAttackBehavior.cpp, AllDirectionsAttackBehavior.cpp - different shooting patterns.
- **Gift Implementations**: RifleGift.cpp, MachineGunGift.cpp, BazookaGift.cpp, BulletsGift.cpp, MedkitGift.cpp.
- **Collectible Items**: RemoveEnemy.cpp, RemoveTime.cpp, IncreasingLife.cpp - special game items.
- **Screen implementations**: Handle different game states (menu, gameplay, win/lose).

### Algorithms

- **Enemy AI Movement**: Three different AI algorithms actively implemented:
  - Simple: Random movement patterns with periodic direction changes
  - Smart: Advanced pathfinding with obstacle avoidance
  - BFS: Direct movement toward player position
- **Collision Detection**: Efficient collision detection system using SFML bounding rectangles
- **Projectile Physics**: Straight-line projectile movement with collision detection
- **Random Placement**: Algorithms for randomly placing enemies, obstacles, and gifts while avoiding overlaps
- **Factory Pattern Implementation**: Template-based object creation system

### Design Patterns

- **Strategy Pattern**: Used for enemy movement and attack behaviors (MoveBehavior and AttackBehavior hierarchies)
- **Factory Pattern**: Template-based object creation system (Factory<UpdateableObject> and Factory<StaticObject>)
- **Singleton Pattern**: Used for ResourcesManager, MusicManager, and CollisionFactory
- **Command Pattern**: Used for collision handling between different object types
- **Template Pattern**: Used in the Factory implementation for type-safe object creation

### Class Hierarchy

- **GameObject**: Base class for all game entities
  - **UpdateableObject**: Moving/animated objects (Player, Enemy, Projectile, Bomb, Explosion)
  - **StaticObject**: Stationary objects (Walls, Obstacles, ItemsToCollect)
    - **ItemsToCollect**: Base for all collectible items
      - **WeaponsGift**: Base for weapon upgrades (RifleGift, MachineGunGift, BazookaGift)
      - **MedkitGift**: Health restoration items
      - **IncreasingLife**: Alternative health items
      - **RemoveEnemy**: Enemy elimination items
      - **RemoveTime**: Timer reduction items
      - **BulletsGift**: Ammunition refill items
- **Screen**: Base class for all game screens
  - **StartScreen**: Main menu interface
  - **GamePlay**: Main game screen with combat
  - **WinScreen**: Victory screen
  - **LoseScreen**: Game over screen
  - **HelpScreen**: Instructions and controls
- **Behavior Classes**:
  - **MoveBehavior**: Base for enemy movement with three active implementations:
  - RandomMoveBehavior: Used by Simple enemies - random directional movement
  - AxisMoveBehavior: Used by Smart enemies - advanced pathfinding with obstacle avoidance
  - BfsMoveBehavior: Used by BFS enemies - direct movement toward player
  - **AttackBehavior**: Base for attack patterns (OneDirectionAttackBehavior, AllDirectionsAttackBehavior)
- **Factory<T>**: Template-based object creation system for UpdateableObject and StaticObject
- **Singleton Classes**: ResourcesManager, MusicManager, CollisionFactory

### Level System

The game uses a hybrid approach for level creation:
- **Walls**: Loaded from Level1.csv file with format: wall,wall,x_coordinate,y_coordinate
- **Enemies**: Strategically distributed across three map sections:
  - First section: 5 Simple enemies
  - Second section: 1 Simple + 10 Smart enemies  
  - Third section: 1 Simple + 10 Smart + 1 BFS enemy
- **Obstacles**: Randomly distributed across the map (3 types: OBSTACLE1, OBSTACLE2, OBSTACLE3)
- **Gifts**: Randomly placed throughout the level including weapons, ammunition, and special items

Currently implemented objects:
- **28 Total Enemies**: 7 Simple (random movement), 20 Smart (pathfinding), 1 BFS (direct tracking)
- **60 Destructible Obstacles**: Three types with 3 hit points each, provide cover and strategic destruction
- **30 Weapon Gifts**: 10 each of Rifle, Machine Gun, and Bazooka upgrades
- **80 Collectible Items**: 20 each of Bullets, Medkits, Enemy Removal, and Time Reduction items
- **Player Statistics**: 100 health points, 29 bullets, 10 bombs initially

### Technical Implementation Details

**Object Creation System:**
- **Template Factory**: `Factory<T>` template class for type-safe object creation
- **Static Registration**: Objects register themselves with the factory using static variables
- **Lambda Creation**: Factory uses lambda functions for object instantiation
- **Type Safety**: Separate factories for UpdateableObject and StaticObject hierarchies

**Collision System:**
- **CollisionFactory**: Singleton managing all collision interactions
- **Type-Index Based**: Uses `std::type_index` for efficient collision lookup
- **Symmetric Registration**: Collision handlers work regardless of parameter order
- **Extensible**: Easy to add new collision types without modifying existing code

**Game Statistics:**
- **Map Size**: 5000x5000 pixel world with camera following player
- **Frame Rates**: Player animation at 0.1s per frame, bomb animation at 0.7s per frame
- **Speeds**: Player moves at 250 units/second, enemies at 100 units/second, projectiles at 750 units/second
- **Weapon Cooldowns**: Rifle (0.2s), Machine Gun (0.1s), Bazooka (0.5s)
- **Damage Values**: Projectiles (5 damage), Explosions (20 damage), Obstacles (3 hit points)

### Music System

The game features a comprehensive music system with:
- **Menu Music**: Background music for menus and non-combat screens
- **Game Music**: Intense combat music during gameplay
- **Win Music**: Victory celebration music
- **Smooth Transitions**: Seamless audio transitions between game states
- **Volume Control**: Adjustable master and per-track volume settings
- **Mute/Unmute**: Toggle music on/off with M key

## Credits

- Game developed by Noam Mazouz & Ofek Cohen & Orel Zabriko & Nadav Ben Melech.
- Sound effects and music obtained from Youtube, Pixabay.
- Special thanks to our lecturers Rachel Shepira & Yehezkel Bernat for their assistance and feedback.

## License

This project is licensed under the Hadassah Academic College students:
Noam Mazouz & Ofek Cohen & Orel Zabriko & Nadav Ben Melech.
