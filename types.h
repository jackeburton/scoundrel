#ifndef TYPES_H
#define TYPES_H

#define NUMBER_OF_CARDS 60
#define ROOM_SIZE 4
#define STARTING_HEALTH 20

struct Weapon
{
    int damage;
};

struct Player
{
    struct Weapon weapon;
    int health;
    int last_defeated;
};

struct Enemy
{
    int damage;
};

struct Potion {
    int healing;
};

enum EntityType
{
    ENTITY_WEAPON,
    ENTITY_ENEMY,
    ENTITY_POTION,
    ENTITY_NONE
};

struct Entity
{
    enum EntityType type;
    union 
    {
        struct Weapon weapon;
        struct Enemy enemy;
        struct Potion potion;
    };
    
};

struct Dungeon {
    struct Entity entities[NUMBER_OF_CARDS];
    int head;
    int tail;
};

struct Room {
    struct Entity entities[ROOM_SIZE];
};

struct GameState {
    struct Dungeon dungeon;
    struct Room room;
    struct Player player;
};

#endif