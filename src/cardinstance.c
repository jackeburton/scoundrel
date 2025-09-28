#include <stdlib.h>
#include <stdio.h>
#include "../include/carddef.h"
#include "../include/cardinstance.h"

struct CardInstance{
    CardDef *cardDef;
};

CardInstance *CardInstance_create(CardDef *cardDef){
    CardInstance *cardInstance = malloc(sizeof(CardInstance));

    cardInstance->cardDef = cardDef;

    printf("made new card instance of card : %s\n", CardDef_getName(cardInstance->cardDef));

    return cardInstance;
};

void CardInstance_destroy(CardInstance *cardInstance){free(cardInstance);};

void CardInstance_interact(CardInstance *cardInstance, GameState *gameState){
    CardDef_getInteract(cardInstance->cardDef)(cardInstance->cardDef, gameState);
};

Texture2D CardInstance_getSprite(CardInstance *cardInstance){
    return CardDef_getSprite(cardInstance->cardDef);
};
