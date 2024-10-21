#include "placement.h"
#include <stdio.h>

Placement placement_init() {
	Placement placement = {};

	placement.x = 0;
	placement.y = 0;
	placement.gx = 0;
	placement.gy = 0;
	placement.current_tile = 0;

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

	if (placement->current_tile >= 4 && placement->current_tile <= 9) {
		DrawRectangle(placement->x, placement->y, 16, 16, (Color){255, 0, 0, 75});
	}

	DrawTexture(placement->border->data.sprite.texture, placement->x, placement->y, WHITE);
}

int placement_get_tile(Placement *placement, Scene *scene) {
	placement->current_tile = scene->tilemap.tiles[placement->gy][placement->gx];
	return placement->current_tile;
}
