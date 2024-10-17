#ifndef PLACEMENT_H
#define PLACEMENT_H

#include "../lib/raylib/src/raylib.h"
#include "assets.h"

typedef struct {
	int x; int y;
	Color normal;
	Color blocked;
	Asset *border;
} Placement;

Placement placement_init();
void placement_update(Placement *placement, float mx, float my);
void placement_draw(Placement *placement);

#endif
