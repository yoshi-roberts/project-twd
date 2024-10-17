#include "placement.h"
#include "../lib/raylib/src/raylib.h"

Placement placement_init() {
	Placement placement = {};

	placement.x = 0;
	placement.y = 0;

	return  placement;
}

void placement_update(Placement *placement, float mx, float my) {

	placement->x = mx;	
	placement->y = my;	
}

void placement_draw(Placement *placement) {

	DrawRectangle(placement->x, placement->y, 16, 16, WHITE);
}
