#include "placement.h"

Placement placement_init() {
	Placement placement = {};

	placement.x = 0;
	placement.y = 0;
	placement.gx = 0;
	placement.gy = 0;

	placement.normal = (Color){255, 255, 255, 102};
	placement.border = assets_get("assets/images/placement-border.png");

	return  placement;
}

void placement_update(Placement *placement, float mx, float my) {

	placement->x = (int)(mx / 16) * 16;	
	placement->y = (int)(my / 16) * 16;	
	placement->gx = (int)placement->x / 16;
	placement->gy = (int)placement->y / 16;
}

void placement_draw(Placement *placement) {
	DrawTexture(placement->border->data.sprite.texture, placement->x, placement->y, WHITE);
}

int placement_get_tile(Placement *placement, Scene *scene) {
	return scene->tilemap.tiles[placement->gy][placement->gx];
}
