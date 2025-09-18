#include "raylib.h"

#include "types.h"

// actions
struct Entity spawnEntity(struct Dungeon *dungeon){
    // TODO IF HEAD MEETS TAIL
    struct Entity entity = dungeon->entities[dungeon->head];
    while (entity.type == ENTITY_NONE)
    {
        dungeon->head++;
        entity = dungeon->entities[dungeon->head];
    }
    dungeon->head++;
    return entity;
}

struct Entity returnEntity(struct Dungeon *dungeon){
    // TODO IF HEAD MEETS TAIL
    struct Entity entity = dungeon->entities[dungeon->tail];
    while (entity.type == ENTITY_NONE)
    {
        dungeon->tail--;
        entity = dungeon->entities[dungeon->tail];
    } 
    dungeon->tail--;
    return entity;
}

int getCurrentRoomPop(struct Room *room){
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
struct Dungeon initDungeon(int num_of_entities){
    // populate dungeon
    int i;
    struct Dungeon dungeon;
    for (i = 0; i < num_of_entities; i++) {
        struct Entity newEntity;
        newEntity.type = ENTITY_WEAPON;
        newEntity.weapon.damage = i;
        dungeon.entities[i] =  newEntity;
    }
    dungeon.head = 0;
    dungeon.tail = num_of_entities - 1;

    return dungeon;
}

struct Player initPlayer(int starting_health){
    struct Player player;
    player.health = starting_health;
    player.last_defeated = 0;
    struct Weapon startingWeapon;
    startingWeapon.damage = 0;
    player.weapon = startingWeapon;
    return player;
};

struct Room initRoom(struct Dungeon *dungeon, int roomSize){
    struct Room room;
    int i;
    for (i = 0; i < roomSize; i++){
        room.entities[i] = spawnEntity(dungeon);
    }
    return room;
}

struct GameState initGame(int numberOfCards, int startingHealth, int roomSize){
    struct Dungeon dungeon = initDungeon(NUMBER_OF_CARDS);
    struct Player player = initPlayer(STARTING_HEALTH);
    struct Room room = initRoom(&dungeon, ROOM_SIZE); 
    struct GameState gameState;
    gameState.dungeon = dungeon;
    gameState.player = player;
    gameState.room = room;
    return gameState;
}

//draw

void drawRoom(struct GameState *gameState, int x, int y){
    int i;
    for (i = 0; i < getCurrentRoomPop(&gameState->room); i++){
        struct Entity entity = gameState->room.entities[i];
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

    struct GameState gameState = initGame(NUMBER_OF_CARDS, STARTING_HEALTH, ROOM_SIZE);

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