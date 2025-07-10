# No One Left - Combat Survival Game

No One Left is a top-down combat survival game where the player controls a soldier trying to eliminate all enemies in a hostile environment while avoiding enemy fire and using strategic positioning.
The game is implemented using C++ and SFML (Simple and Fast Multimedia Library) for graphics rendering and audio.

## Overview

In "No One Left", the player controls a soldier character navigating through combat zones filled with enemies, obstacles, and useful items.
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
- **Explosions**: Area damage effects from bombs rounds with animated sprite effects.
- **Obstacles**: Destructible environmental barriers that provide cover.
- **Walls**: Indestructible boundaries and structures.
- **Gifts**: Various power-ups including weapons, ammunition, health, and special items.

## Controls

- **Arrow Keys**: Move player character.
- **S Key**: Shoot current weapon.
- **B Key**: Place bomb.
- **M Key**: Mute/unmute music.
- **Escape Key**: Return to main menu.
- **Mouse**: Navigate menus and interact with buttons.

## Files

### Headers

- **Player.h**: Declares the `Player` class representing the player-controlled soldier character.
- **Enemy.h**: Contains the `Enemy` class declaration representing enemy characters with AI behavior.
- **GameObject.h**: Contains the `GameObject` class declaration, base class for all game objects.
- **UpdateableObject.h**: Base class for moving/animated game objects with sprite animation support.
- **StaticObject.h**: Base class for stationary game objects.
- **Projectile.h**: Declares the `Projectile` class for bullets and the bazooka missile.
- **Bomb.h**: Contains the `Bomb` class declaration for explosive devices with timed detonation.
- **Explosion.h**: Declares the `Explosion` class for area damage effects with animated sprite sequences.
- **Obstacles.h**: Contains obstacle class declarations for destructible barriers.
- **Wall.h**: Declares the `Wall` class for indestructible boundaries.
- **ItemsToCollect.h**: Base class for all collectible items in the game.
- **WeaponsGift.h**: Base class for weapon upgrade items, inherits from ItemsToCollect.
- **RifleGift.h**: Declares rifle weapon upgrade items, inherits from WeaponsGift.
- **MachineGunGift.h**: Declares machine gun weapon upgrade items, inherits from WeaponsGift.
- **BazookaGift.h**: Declares bazooka weapon upgrade items, inherits from WeaponsGift.
- **BulletsGift.h**: Declares ammunition pickup items, inherits from ItemsToCollect.
- **MedkitGift.h**: Declares health restoration items, inherits from ItemsToCollect.
- **IncreasingLife.h**: Alternative health item implementation, inherits from ItemsToCollect.
- **RemoveEnemy.h**: Declares special items that eliminate random enemies, inherits from ItemsToCollect.
- **RemoveTime.h**: Declares items that reduce mission timer, inherits from ItemsToCollect.
- **Map.h**: Contains the `Map` class for level loading and management.
- **Controller.h**: Contains the `Controller` class for game state management.
- **InfoBar.h**: Manages the game's user interface displaying health, ammunition, bombs, enemies, and timer.
- **ResourcesManager.h**: Manages loading and storage of game resources including textures, sounds, and fonts.
- **MusicManager.h**: Manages background music with fade transitions, different music types, and volume control.
- **Screen**: Directory containing all screen management classes.
- **AttackBehavior.h**: Base class for enemy attack patterns.
- **MoveBehavior.h**: Base class for enemy movement patterns.
- **CollisionFactory.h**: Handles collision detection between objects using type-index based lookup.
- **Factory.h**: Template-based object creation system for type-safe instantiation.
- **Const.h**: Contains game constants and configuration values.

### Source Files (CPP)

- **Player.cpp**: Implements player movement, shooting, collision handling, and interaction systems.
- **Enemy.cpp**: Implements enemy AI, movement, combat behaviors, and factory registration for three enemy types.
- **GameObject.cpp**: Base implementation for all game objects with sprite and position management.
- **UpdateableObject.cpp**: Base implementation for moving objects with animation and rotation systems.
- **StaticObject.cpp**: Base implementation for static objects.
- **Projectile.cpp**: Implements bullet\bazooka missile physics, collision detection, and automatic collision registration.
- **Bomb.cpp**: Implements bomb placement, timing, and explosion triggering logic.
- **Explosion.cpp**: Implements explosion effects, area damage, and comprehensive collision with all object types.
- **Map.cpp**: Implements hybrid level loading with CSV walls and random object placement algorithms.
- **Controller.cpp**: Main game loop and state management.
- **InfoBar.cpp**: Implements the UI information bar with real-time game statistics and icon display.
- **ResourcesManager.cpp**: Resource loading implementation with texture mapping and sound effect management.
- **MusicManager.cpp**: Complete audio system with fade transitions, menu/game/win/lose music types.
- **CollisionFactory.cpp**: Collision detection and response system using type-index based lookup tables.
- **Movement Behaviors**: RandomMoveBehavior.cpp (8-directional random movement), AxisMoveBehavior.cpp (intelligent pathfinding), BfsMoveBehavior.cpp (direct player tracking with collision avoidance).
- **Attack Behaviors**: OneDirectionAttackBehavior.cpp (single direction shooting), AllDirectionsAttackBehavior.cpp (multi-directional firing).
- **Gift Implementations**: Complete implementations for all collectible items with collision handling.
- **Screen implementations**: Handle different game states (menu, gameplay, win/lose) with button management.

### Algorithms

- **Enemy AI Movement**: Three different AI algorithms actively implemented:
  - Simple: Random 8-directional movement with 2-second interval changes and collision-based direction switching.
  - Smart: Intelligent axis-based pathfinding with collision avoidance and side-stepping behavior.
  - BFS: Direct movement toward player with collision-based obstacle avoidance (not actual BFS pathfinding).
- **Collision Detection**: Efficient collision detection system using SFML bounding rectangles with type-index lookup.
- **Projectile Physics**: Straight-line projectile movement with timed expiration and collision detection.
- **Random Placement**: Algorithms for randomly placing enemies, obstacles, and gifts while avoiding overlaps.
- **Factory Pattern Implementation**: Template-based object creation system with lambda-based registration.

### Design Patterns

- **Strategy Pattern**: Used for enemy movement and attack behaviors (MoveBehavior and AttackBehavior hierarchies)
- **Factory Pattern**: Template-based object creation system (Factory<UpdateableObject> and Factory<StaticObject>)
- **Singleton Pattern**: Used for ResourcesManager, MusicManager, and CollisionFactory
- **Command Pattern**: Used for collision handling between different object types
- **Template Pattern**: Used in the Factory implementation for type-safe object creation

### Class Hierarchy

- **GameObject**: Base class for all game entities.
  - **UpdateableObject**: Moving/animated objects (Player, Enemy, Projectile, Bomb, Explosion).
  - **StaticObject**: Stationary objects (Walls, Obstacles, ItemsToCollect).
    - **ItemsToCollect**: Base for all collectible items.
      - **WeaponsGift**: Base for weapon upgrades (RifleGift, MachineGunGift, BazookaGift).
      - **MedkitGift**: Health restoration items.
      - **IncreasingLife**: Alternative health items.
      - **RemoveEnemy**: Enemy elimination items.
      - **RemoveTime**: Timer reduction items.
      - **BulletsGift**: Ammunition refill items.
- **Screen**: Base class for all game screens.
  - **StartScreen**: Main menu interface.
  - **GamePlay**: Main game screen with combat.
  - **WinScreen**: Victory screen.
  - **LoseScreen**: Game over screen.
  - **HelpScreen**: Instructions and controls.
- **Behavior Classes**:
  - **MoveBehavior**: Base for enemy movement with three active implementations:
  - RandomMoveBehavior: Used by Simple enemies - 8-directional random movement.
  - AxisMoveBehavior: Used by Smart enemies - intelligent pathfinding with obstacle avoidance.
  - BfsMoveBehavior: Used by BFS enemies - direct movement toward player with collision avoidance.
  - **AttackBehavior**: Base for attack patterns (OneDirectionAttackBehavior, AllDirectionsAttackBehavior).
- **Factory<T>**: Template-based object creation system for UpdateableObject and StaticObject.
- **Singleton Classes**: ResourcesManager, MusicManager, CollisionFactory.

### Level System

The game uses a hybrid approach for level creation:
- **Walls**: Loaded from Level_Info.csv file with format: wall,wall,x_coordinate,y_coordinate.
- **Enemies**: Strategically distributed across three map sections:
  - First section: 5 Simple + 5 Smart enemies.
  - Second section: 1 Simple + 10 Smart enemies.
  - Third section: 1 Simple + 10 Smart + 1 BFS enemy.
- **Obstacles**: Randomly distributed across the map (60 total: 20 each of OBSTACLE1, OBSTACLE2, OBSTACLE3).
- **Gifts**: Randomly placed throughout the level including weapons, ammunition, and special items.

Currently implemented objects:
- **28 Total Enemies**: 7 Simple (random movement), 20 Smart (pathfinding), 1 BFS (direct tracking).
- **60 Destructible Obstacles**: Three types with 3 hit points each, provide cover and strategic destruction.
- **30 Weapon Gifts**: 10 each of Rifle, Machine Gun, and Bazooka upgrades.
- **80 Collectible Items**: 20 each of Bullets, Medkits, Enemy Removal, and Time Reduction items.
- **Player Statistics**: 100 health points, 29 bullets, 10 bombs initially.

### Technical Implementation Details

**Object Creation System:**
- **Template Factory**: `Factory<T>` template class for type-safe object creation.
- **Static Registration**: Objects register themselves with the factory using static variables and lambda functions.
- **Lambda Creation**: Factory uses lambda functions for object instantiation with proper behavior assignment.
- **Type Safety**: Separate factories for UpdateableObject and StaticObject hierarchies.

**Collision System:**
- **CollisionFactory**: Singleton managing all collision interactions using std::type_index.
- **Type-Index Based**: Uses `std::type_index` for efficient collision lookup with bidirectional registration.
- **Symmetric Registration**: Collision handlers work regardless of parameter order.
- **Automatic Registration**: Objects register their collision handlers automatically on first creation.

**Animation System:**
- **Sprite Animation**: Frame-based animation system with configurable frame timing.
- **Rotation System**: Smooth rotation interpolation for directional sprites.
- **Explosion Animation**: 257x250 pixel explosion sprites with 0.05s frame timing.

**Game Statistics:**
- **Map Size**: 5000x5000 pixel world with camera following player.
- **Frame Rates**: Player animation at 0.1s per frame, bomb animation at 0.7s per frame, explosion at 0.05s per frame.
- **Speeds**: Player moves at 250 units/second, enemies at 100 units/second, projectiles at 750 units/second.
- **Weapon Cooldowns**: Rifle (0.2s), Machine Gun (0.1s), Bazooka (0.5s).
- **Damage Values**: Projectiles (5 damage), Explosions (20 damage), Obstacles (3 hit points).
- **Explosion Properties**: 80-pixel radius, 2-second duration, 257x250 pixel sprites.


### Asset Management

**Texture Mappings (ResourcesManager.cpp):**
- **Player Sprites**: player_rifle.png, player_machine_gun.png, player_bazooka.png.
- **Enemy Sprites**: simple_enemy_rifle.png, smart_enemy_rifle.png, bfs_enemy_rifle.png.
- **Environment**: gameBackground.png, wall.png, Broken_tree1.png, Broken_tree2.png, Rock.png.
- **Effects**: Sprite_Effects_Exhaust.png (projectiles), Effect_Explosion.png (explosions).
- **UI Elements**: Various button and icon textures for interface.
- **Weapons/Items**: rifle.png, machine_gun.png, Bazooka_sized.png, medkit.png, Bullet.png, bazooka_missile.png.

**Sound Effects:**
- **Combat**: shoot.ogg, explosion.ogg, hit.ogg.
- **Interface**: present.ogg, addHealth.ogg, death.ogg.
- **Music**: menuMusic.ogg, gameMusic.ogg, winMusic.ogg, loseMusic.ogg.


### Music System

The game features a comprehensive music system with:
- **Menu Music**: Background music for menus and non-combat screens.
- **Game Music**: Intense combat music during gameplay.
- **Win Music**: Victory celebration music (60% volume).
- **Lose Music**: Somber defeat music (40% volume).
- **Smooth Transitions**: Fade-out transitions between music states.
- **Volume Control**: Adjustable master and per-track volume settings.
- **Mute/Unmute**: Toggle music on/off with M key.


### Credits

- Game developed by Noam Mazouz & Ofek Cohen & Orel Zabriko & Nadav Ben Melech.
- Sound effects and music obtained from Youtube, Pixabay.
- Special thanks to our lecturers Rachel Shepira & Yehezkel Bernat for their assistance and feedback.


### license

This project is licensed under the Jerusalem Multidisciplinary College students:
Noam Mazouz & Ofek Cohen & Orel Zabriko & Nadav Ben Melech.