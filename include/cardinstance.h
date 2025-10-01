#ifndef CARDINSTANCE_H
#define CARDINSTANCE_H

#include "carddef.h"
#include "raylib.h"

typedef struct CardInstance CardInstance;

CardInstance *CardInstance_create(CardDef *cardDef);
void CardInstance_destroy(CardInstance *cardInstance);

CardDef *CardInstance_getCardDef(CardInstance cardInstance);
void CardInstance_interact(CardInstance *cardInstance, GameState *gameState);
Texture2D CardInstance_getSprite(CardInstance *cardInstance);

#endif
