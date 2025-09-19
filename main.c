#include "raylib.h"

#include "types.h"

// actions
Entity spawnEntity(Dungeon *dungeon){
    // TODO IF HEAD MEETS TAIL
    Entity entity = dungeon->entities[dungeon->head];
    while (entity.type == ENTITY_NONE)
    {
        dungeon->head++;
        entity = dungeon->entities[dungeon->head];
    }
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

int getCurrentRoomPop(Room *room){
    int i;
    // TODO add this as a macro????
    int popCount = 0;
    for (i = 0; i < sizeof(room->entities) / sizeof(room->entities[i]); i++){
        if (room->entities[i].type == ENTITY_NONE){
            continue;
        }
        popCount++;
    }
    return popCount;
}

//init
Dungeon initDungeon(int num_of_entities){
    // populate dungeon
    int i;
    Dungeon dungeon;
    for (i = 0; i < num_of_entities; i++) {
        Entity newEntity;
        newEntity.type = ENTITY_WEAPON;
        newEntity.weapon.damage = i;
        dungeon.entities[i] =  newEntity;
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
    Room room;
    int i;
    for (i = 0; i < roomSize; i++){
        room.entities[i] = spawnEntity(dungeon);
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

//draw

void drawRoom(GameState *gameState, int x, int y){
    int i;
    for (i = 0; i < getCurrentRoomPop(&gameState->room); i++){
        Entity entity = gameState->room.entities[i];
        if (entity.type == ENTITY_ENEMY){
            DrawText(
                TextFormat("ENEMY : %d", entity.enemy.damage),
                x + i * 100,
                y,
                14,
                RED
            );
        } else if (entity.type == ENTITY_WEAPON){
            DrawText(
                TextFormat("WEAPON : %d", entity.weapon.damage),
                x + i * 100,
                x,
                14,
                BLACK
            );
        } else if (entity.type == ENTITY_POTION){
            DrawText(
                TextFormat("POTION : %d", entity.potion.healing),
                x + i * 100,
                x,
                14,
                GREEN
            );
        }
    }
}

int main(void) {
    InitWindow(800, 400, "raylib window");
    SetTargetFPS(60);

    GameState gameState = initGame(NUMBER_OF_CARDS, STARTING_HEALTH, ROOM_SIZE);

    while (!WindowShouldClose()){
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawText("hello raylib", 100, 50, 14, BLACK);

            // room
            drawRoom(&gameState, 100, 50);

            //player

        EndDrawing();
    }

    CloseWindow();
}
