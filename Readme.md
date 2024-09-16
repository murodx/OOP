# Creature Battle Game

## Overview

This is a simple text-based game demonstrating Object-Oriented Programming (OOP) concepts using C++. The game allows the player to battle against random monsters and level up. The game incorporates basic OOP principles such as classes, inheritance, and encapsulation.

## Features

- **Player Character**: Can level up and gain gold.
- **Monsters**: Have different types, health, damage, and gold values.
- **Combat System**: Player can choose to fight or flee from monsters.
- **Game Progression**: The game continues until the player either wins or dies.

## Classes

### `Creature`

The base class for both `Player` and `Monster`.

**Member Variables:**
- `m_name`: The name of the creature.
- `m_symbol`: The symbol representing the creature.
- `m_health`: The health points of the creature.
- `m_damage`: The damage the creature can inflict.
- `m_gold`: The gold the creature carries.

**Methods:**
- Getters and setters for the above attributes.
- `isDead()`: Checks if the creature's health is zero or less.

### `Player`

Inherits from `Creature`.

**Additional Member Variables:**
- `m_level`: The player's current level.

**Additional Methods:**
- `levelUp()`: Increases the player's level and damage.
- `hasWon()`: Checks if the player has reached level 3.

### `Monster`

Inherits from `Creature`.

**Additional Member Variables:**
- `m_type`: The type of the monster.

**Additional Methods:**
- `getRandomMonster()`: Generates a random monster from predefined types.

## Functions

- `getRandomNumber(int min, int max)`: Generates a random number between `min` and `max`.
- `attackMonster(Player& p, Monster& m)`: Handles the player's attack on the monster.
- `attackPlayer(Monster& m, Player& p)`: Handles the monster's attack on the player.
- `fightMonster(Player& p)`: Manages the fight between the player and a random monster.

## Compilation and Execution

To compile the game, use the following command:

```bash
g++ -o Source.cpp && ./a.out
or
make ./game
