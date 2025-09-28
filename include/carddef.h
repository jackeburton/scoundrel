#ifndef CARDDEF_H
#define CARDDEF_H

#include "raylib.h"
#include "gamestate.h"

typedef enum {
    CARD_ITEM,
    CARD_CREATURE,
    CARD_BUFF
} CardType;

typedef struct CardDef CardDef;

typedef void (*CardEffectFn)(CardDef *self, GameState *gameState);
CardDef *CardDef_create(char *name, Texture2D sprite, CardType type, int stat, CardEffectFn interact);
void CardDef_destroy(CardDef *cardDef);

CardEffectFn CardDef_getInteract(CardDef *cardDef);

int *CardDef_getStat(CardDef *cardDef);

char *CardDef_getName(CardDef *cardDef);

#endif

