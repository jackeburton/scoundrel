#ifndef TYPES_H
#define TYPES_H

#define NUMBER_OF_CARDS 30 
#define ROOM_SIZE 4
#define STARTING_HEALTH 20

typedef struct Weapon
{
    int damage;
} Weapon;

typedef struct {
    struct Weapon weapon;
    int health;
    int last_defeated;
} Player;

typedef struct {
    int damage;
} Enemy;

typedef struct {
    int healing;
} Potion;

enum EntityType{
    ENTITY_WEAPON,
    ENTITY_ENEMY,
    ENTITY_POTION,
    ENTITY_NONE
};

typedef struct {
    enum EntityType type;
    union {
        Weapon weapon;
        Enemy enemy;
        Potion potion;
    };
    bool discarded;
} Entity;

typedef struct {
    Entity entities[NUMBER_OF_CARDS];
    int head;
    int tail;
} Dungeon;

// TODO make this a Pointer to the entities in the Dungeon!
typedef struct {
    Entity entities[ROOM_SIZE];
} Room;

typedef struct {
    Dungeon dungeon;
    Room room;
    Player player;
} GameState;

#endif
