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

    //TODO change this to print the name
    printf("made new card instance of card : ");

    return cardInstance;
};

void CardInstance_destroy(CardInstance *cardInstance){free(cardInstance);};
