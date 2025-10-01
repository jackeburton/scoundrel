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
    int isSelected;
    int x;
    int y;
    Rectangle hitBox;
};

LibraryInstanceRenderObject *RenderObject_create(CardInstance *cardInstance, int x, int y){
    LibraryInstanceRenderObject *renderObject = malloc(sizeof(LibraryInstanceRenderObject));

    renderObject->cardInstance = cardInstance;
    renderObject->x = x;
    renderObject->y = y;
    renderObject->isSelected = 0;
    renderObject->hitBox = (Rectangle){x - 5, y - 10,  17 * 5, 18 * 5};

    return renderObject;
};

void render_select(int x, int y, float scale) {
    int height = 22;
    int width = 21;
    // TOP
    DrawRectangle(x - (2 * scale), y - (4 * scale), width * scale, scale, RED);
    // LEFT
    DrawRectangle(x - (2 * scale) - scale, y - (3 * scale), scale, height * scale, RED);
    // BOTTOM
    DrawRectangle(x - (2 * scale), y + (19 * scale), width * scale, scale, RED);
    // RIGHT
    DrawRectangle(x - (2 * scale) + (21 * scale), y - (3 * scale), scale, height * scale, RED);
}

void render_card(int x, int y, float scale){
    // TOP
    DrawRectangle(
        x,
        y - 2 * scale,
        17 * scale,
        scale,
        WHITE
    );
    // LEFT
    DrawRectangle(
        x - scale,
        y - scale,
        scale,
        18 * scale,
        WHITE
    );
    //BOTTOM
    DrawRectangle(
        x,
        y + 17 * scale,
        17 * scale,
        scale,
        WHITE
    );
    //RIGHT
    DrawRectangle(
        x + 17 * scale,
        y - scale,
        scale,
        18 * scale,
        WHITE
    );

};

void RenderObject_destroy(LibraryInstanceRenderObject *renderObject){
    if (!renderObject) return;
    free(renderObject);
};

Rectangle RenderObject_getHitbox(LibraryInstanceRenderObject *renderObject){
    return renderObject->hitBox;
}

void RenderObject_flipSelected(LibraryInstanceRenderObject *renderObject){
    renderObject->isSelected = !renderObject->isSelected;
};

void RenderObject_render(
    struct LibraryInstanceRenderObject *renderObject){
    int scale = 5.f;
    render_card(renderObject->x, renderObject->y, scale);
    if (renderObject->isSelected){
        render_select(renderObject->x, renderObject->y, scale);
    }
    DrawTextureEx(
        CardInstance_getSprite(renderObject->cardInstance),
        (Vector2){
            renderObject->x,
            renderObject->y,
        },
        0.0f,
        scale,
        WHITE
    );
};
