#ifndef RENDER_H
#define RENDER_H

#include "../include/cardinstance.h"

typedef struct LibraryInstanceRenderObject LibraryInstanceRenderObject;

LibraryInstanceRenderObject *RenderObject_create(CardInstance *cardInstance, int x, int y);
void RenderObject_destroy(LibraryInstanceRenderObject *renderObject);

void RenderObject_render(LibraryInstanceRenderObject *renderObject);

#endif
