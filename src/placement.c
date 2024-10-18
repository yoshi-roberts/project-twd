#include "placement.h"
#include <math.h>

Placement placement_init() {
	Placement placement = {};

	placement.x = 0;
	placement.y = 0;

	placement.normal = (Color){255, 255, 255, 102};
	placement.border = assets_get("assets/images/placement-border.png");

	return  placement;
}

void placement_update(Placement *placement, float mx, float my) {

	placement->x = floor(mx / 16) * 16;	
	placement->y = floor(my / 16) * 16;	
}

void placement_draw(Placement *placement) {

	DrawTexture(placement->border->data.sprite.texture, placement->x, placement->y, WHITE);
}
