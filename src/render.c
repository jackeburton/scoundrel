// GAME LOGIC
// I have a bunch of cards, I have a bunch of owned cards
// those owned cards can be in my current spec or not
// once an instance is used in a dungeon it cannot be used again
// THAT IS GAME LOGIC
//
// Ok so what do we do here? we are doing render logic - can I start by rendering just a cardInstance?
//

#include <stdlib.h>
#include <stdio.h>
#include "raylib.h"
#include "../include/cardinstance.h"
#include "../include/render.h"

// NEED STRUCT DRAWINSTANCE
struct LibraryInstanceRenderObject{
    CardInstance *cardInstance;
    int x;
    int y;
};

LibraryInstanceRenderObject *RenderObject_create(CardInstance *cardInstance, int x, int y){
    LibraryInstanceRenderObject *renderObject = malloc(sizeof(LibraryInstanceRenderObject));

    renderObject->cardInstance = cardInstance;
    renderObject->x = x;
    renderObject->y = y;

    return renderObject;
};

void RenderObject_destroy(LibraryInstanceRenderObject *renderObject){
    if (!renderObject) return;
    free(renderObject);
};

void RenderObject_render(
    struct LibraryInstanceRenderObject *renderObject){
    DrawTextureEx(
        CardInstance_getSprite(renderObject->cardInstance),
        (Vector2){
            renderObject->x,
            renderObject->y,
        },
        0.0f,
        10.f,
        WHITE
    );
};
