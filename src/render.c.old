#include "raylib.h"
#include "../include/types.h"


int roomSize(Room *room){
	return sizeof(room->entities) / sizeof(room->entities[0]);
}

void drawRoom(GameState *gameState, int x, int y){
    int i;
    for (i = 0; i < roomSize(&gameState->room); i++){
        Entity entity = gameState->room.entities[i];
        if (entity.discarded){
            continue;
        }
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
                y,
                14,
                BLACK
            );
        } else if (entity.type == ENTITY_POTION){
            DrawText(
                TextFormat("POTION : %d", entity.potion.healing),
                x + i * 100,
                y,
                14,
                GREEN
            );
        }
    }
}

void drawPlayer(GameState *gameState, int x, int y){
	Weapon playerWeapon = gameState->player.weapon;
	int health = gameState->player.health;
	int lastDefeated = gameState->player.last_defeated;
	DrawText(TextFormat("PLAYER : %d", playerWeapon.damage), x, y, 14, BLACK);
	DrawText(TextFormat("HEALTH : %d", health), x, y + 30, 14, BLACK);
	DrawText(TextFormat("LAST DEFEATED : %d", lastDefeated), x, y + 60, 14, BLACK);
}

void draw(GameState *gameState, int x, int y){
	drawRoom(gameState, x, y);
	drawPlayer(gameState, x, y + 100);
}
