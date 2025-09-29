#include <stdio.h>
#include "raylib.h"
#include "../include/carddef.h"
#include "../include/cardinstance.h"
#include "../include/render.h"

void potion_heal(CardDef *cardDef, GameState *gameState){
    printf("Potion is healing\n");
    //Player_addHealth(GameState_getPlayer(gameState), CardDef_getStat(cardDef);
}

void weapon_attack(CardDef *cardDef, GameState *gameState){
    printf("weapon is attaching\n");
    //Player_addHealth(GameState_getPlayer(gameState), CardDef_getStat(cardDef);
}

void enemy_defeated(CardDef *cardDef, GameState *gameState){
    printf("enemy defeating\n");
    //Player_addHealth(GameState_getPlayer(gameState), CardDef_getStat(cardDef);
}

int main(void) {
    InitWindow(1500, 800, "raylib window");
    SetTargetFPS(60);

    Image potion_image = LoadImage("resources/potion.png");
    Texture2D potion_texture = LoadTextureFromImage(potion_image);
    UnloadImage(potion_image);

    Image weapon_image = LoadImage("resources/sword.png");
    Texture2D weapon_texture = LoadTextureFromImage(weapon_image);
    UnloadImage(weapon_image);

    Image enemy_image = LoadImage("resources/enemy.png");
    Texture2D enemy_texture = LoadTextureFromImage(enemy_image);
    UnloadImage(enemy_image);

    CardDef *potion = CardDef_create("Potion", potion_texture, CARD_ITEM, 5, potion_heal);
    CardDef *weapon = CardDef_create("Weapon", weapon_texture, CARD_BUFF, 5, weapon_attack);
    CardDef *enemy = CardDef_create("Enemy", enemy_texture, CARD_CREATURE, 5, enemy_defeated);
    GameState *gameState;

    CardInstance *potion_1 = CardInstance_create(potion);
    CardInstance *potion_2 = CardInstance_create(potion);

    CardInstance *weapon_1 = CardInstance_create(weapon);
    CardInstance *weapon_2 = CardInstance_create(weapon);

    CardInstance *enemy_1 = CardInstance_create(enemy);
    CardInstance *enemy_2 = CardInstance_create(enemy);



    CardInstance_interact(potion_1, gameState);

    LibraryInstanceRenderObject *potionRenderObject = RenderObject_create(potion_1, 200, 100);
    LibraryInstanceRenderObject *weaponRenderObject = RenderObject_create(weapon_1, 350, 100);
    LibraryInstanceRenderObject *enemyRenderObject = RenderObject_create(enemy_1, 500, 100);

    while (!WindowShouldClose()){
        

        BeginDrawing();

            ClearBackground(BLACK);
            RenderObject_render(potionRenderObject);
            RenderObject_render(weaponRenderObject);
            RenderObject_render(enemyRenderObject);

        EndDrawing();
    }

    CloseWindow();
}
