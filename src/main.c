#include <stdio.h>
#include "raylib.h"
#include "../include/carddef.h"

void potion_heal(CardDef *cardDef, GameState *gameState){
    printf("Potion is healing\n");
    //Player_addHealth(GameState_getPlayer(gameState), CardDef_getStat(cardDef);
}

int main(void) {
    InitWindow(800, 400, "raylib window");
    SetTargetFPS(60);

    Image potion_image = LoadImage("../resources/potion.png");
    Texture2D potion_texture = LoadTextureFromImage(potion_image);
    UnloadImage(potion_image);

    
    CardDef *potion = CardDef_create("Potion", potion_texture, CARD_ITEM, 5, potion_heal);
    GameState *gameState;

    CardDef_interact(potion, gameState);

    while (!WindowShouldClose()){
        

        BeginDrawing();

            ClearBackground(BLACK);
             

        EndDrawing();
    }

    CloseWindow();
}
