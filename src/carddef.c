#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/carddef.h"

struct CardDef {
    CardType type;
    Texture2D sprite;
    char *name;
    int stat;
    CardEffectFn effect;
};

CardDef *CardDef_create(char *name, Texture2D sprite, CardType type, int stat, CardEffectFn effect){
    CardDef *cardDef = malloc(sizeof(CardDef));

    cardDef->name = strdup(name);
    cardDef->sprite = sprite;
    cardDef->type = type;
    cardDef->stat = stat;
    cardDef->effect = effect;

    printf("made card : %s\n", name);

    return cardDef;
};

void CardDef_destroy(CardDef *cardDef){
    if (!cardDef) return;
    UnloadTexture(cardDef->sprite);
    free(cardDef->name);
    free(cardDef);
};

CardEffectFn CardDef_getInteract(CardDef *cardDef){
    return cardDef->effect;
};

int *CardDef_getStat(CardDef *cardDef) {return &cardDef->stat;};

char *CardDef_getName(CardDef *cardDef) {return cardDef->name;};

Texture2D CardDef_getSprite(CardDef *cardDef) {return cardDef->sprite;};
