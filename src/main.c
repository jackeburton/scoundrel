#include <stdio.h>
#include "raylib.h"


#include "../include/types.h"

#include "render.c"

// spawning from dungeon actions
Entity spawnEntity(Dungeon *dungeon){
    // TODO IF HEAD MEETS TAIL
    Entity entity = dungeon->entities[dungeon->head];
    while (entity.type == ENTITY_NONE)
    {
        dungeon->head++;
        entity = dungeon->entities[dungeon->head];
    }
    printf("getting entity from dungeon at %d \n", dungeon->head);
    dungeon->head++;
    return entity;
}

Entity returnEntity(Dungeon *dungeon){
    // TODO IF HEAD MEETS TAIL
    Entity entity = dungeon->entities[dungeon->tail];
    while (entity.type == ENTITY_NONE)
    {
        dungeon->tail--;
        entity = dungeon->entities[dungeon->tail];
    } 
    dungeon->tail--;
    return entity;
}

// game interraction actions
// TODO make this modular, so when we call a parent function ie interractWithEntity it will decide
// which to interract with based on what type it is
void takeWeapon(Player *player, Weapon *weapon){
    player->weapon = *weapon;
    player->last_defeated = 0;
} 

bool fightEnemy(Player *player, Enemy *enemy) {
    if (enemy->damage < player->last_defeated){
        return false;
    }
    if (enemy->damage >= player->health){
        player->health = 0;
        return false;
    } else {
        if (player->weapon.damage < enemy->damage){
            player->health = player->health - (enemy->damage - player->weapon.damage);
        }
    }
    player->last_defeated = enemy->damage;
    return true;
}

void usePotion(Player *player, Potion *potion) {
    player->health = player->health + potion->healing;
    if (player->health > 20){
        player->health = 20;
    }
}

void nextRoom() {}

void interractWithEntity(Room *room, Player *player, int index) {
    Entity *room_entity = &room->entities[index-1];
    if (room_entity->discarded){
        return;
    }
    if (room_entity->type == ENTITY_ENEMY) {
        if (fightEnemy(player, &room_entity->enemy)){
            room_entity->discarded = true;
        }
    }
    else if (room_entity->type == ENTITY_WEAPON) {
        takeWeapon(player, &room_entity->weapon); room_entity->discarded = true;
    }
    else if (room_entity->type == ENTITY_POTION) {
        usePotion(player, &room_entity->potion); room_entity->discarded = true;
    }
}



//init
Dungeon initDungeon(int num_of_entities){
    // populate dungeon
    int i;
    Dungeon dungeon;
    for (i = 0; i < num_of_entities; i++) {
        if (i == 0){
            Entity newEntity;
            newEntity.type = ENTITY_ENEMY;
            newEntity.enemy.damage = 5;
            newEntity.discarded = false;
            dungeon.entities[i] =  newEntity;
            printf("adding enemy to dungeon at %d\n", i);
        } else if (i == 1){
            Entity newEntity;
            newEntity.type = ENTITY_POTION;
            newEntity.potion.healing = 5;
            newEntity.discarded = false;
            dungeon.entities[i] =  newEntity;
            printf("adding potion to dungeon at %d\n", i);
        } else {
            Entity newEntity;
            newEntity.type = ENTITY_WEAPON;
            newEntity.weapon.damage = i;
            newEntity.discarded = false;
            dungeon.entities[i] =  newEntity;
            printf("adding weapon to dungeon at %d\n", i);
        }
    }
    dungeon.head = 0;
    dungeon.tail = num_of_entities - 1;

    return dungeon;
}

Player initPlayer(int starting_health){
    Player player;
    player.health = starting_health;
    player.last_defeated = 0;
    Weapon startingWeapon;
    startingWeapon.damage = 0;
    player.weapon = startingWeapon;
    return player;
};

Room initRoom(Dungeon *dungeon, int roomSize){
    printf("INITIALISING ROOM\n");
    Room room;
    int i;
    for (i = 0; i < roomSize; i++){
        room.entities[i] = spawnEntity(dungeon);
        switch (room.entities[i].type){
            case ENTITY_ENEMY: printf("GOT ENEMY FROM DUNEGON\n"); break;
            case ENTITY_WEAPON: printf("GOT WEAPON FROM DUNEGON\n"); break;
            case ENTITY_POTION: printf("GOT POTION FROM DUNEGON\n"); break;
            case ENTITY_NONE: printf("GOT NONE FROM DUNEGON\n"); break;
        }
    }
    return room;
}

GameState initGame(int numberOfCards, int startingHealth, int roomSize){
    Dungeon dungeon = initDungeon(NUMBER_OF_CARDS);
    Player player = initPlayer(STARTING_HEALTH);
    Room room = initRoom(&dungeon, ROOM_SIZE); 
    GameState gameState;
    gameState.dungeon = dungeon;
    gameState.player = player;
    gameState.room = room;
    return gameState;
}

int main(void) {
    InitWindow(800, 400, "raylib window");
    SetTargetFPS(60);

    GameState gameState = initGame(NUMBER_OF_CARDS, STARTING_HEALTH, ROOM_SIZE);

    while (!WindowShouldClose()){
        
        if(IsKeyDown(KEY_ONE)) interractWithEntity(&gameState.room, &gameState.player, 1);
        if(IsKeyDown(KEY_TWO)) interractWithEntity(&gameState.room, &gameState.player, 2);
        if(IsKeyDown(KEY_THREE)) interractWithEntity(&gameState.room, &gameState.player, 3);
        if(IsKeyDown(KEY_FOUR)) interractWithEntity(&gameState.room, &gameState.player, 4);

        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawText("scoundrel", 100, 50, 14, BLACK);

            // room
            draw(&gameState, 150, 100);

            //player

        EndDrawing();
    }

    CloseWindow();
}
