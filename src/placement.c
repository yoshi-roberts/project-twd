#include "placement.h"
#include "log.h"
#include "game.h"
#include "unit.h"
#include <stdio.h>

static Placement placement = {};
static bool initialized = false;

void placement_init() {

	if (initialized) {
		log_error("Placement system already initialized.");
	}

	placement.x = 0;
	placement.y = 0;
	placement.gx = 0;
	placement.gy = 0;
	placement.current_tile = 0;

	placement.normal = (Color){255, 255, 255, 102};
	placement.border = assets_get("assets/images/placement-border.png");

	initialized = true;
	log_info("Placement System Initialized.");
}

void placement_update(float mx, float my) {

	placement.x = (int)(mx / 16) * 16;	
	placement.y = (int)(my / 16) * 16;	
	placement.gx = (int)placement.x / 16;
	placement.gy = (int)placement.y / 16;

	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && placement_can_place()) {
		Scene *scn = game_get_scene();
		scn->units[scn->unit_index] = unit_new(UNIT_KNIGHT, placement.gx, placement.gy);
		scn->unit_index++;
		printf("Added Unit!\n");
	}
}

void placement_draw() {

	int tile = placement_get_tile(game_get_scene());
	if (tile >= TILE_PATH_UP_RIGHT && tile <= TILE_PATH_RIGHT_UP) {
		DrawRectangle(placement.x, placement.y, 16, 16, (Color){255, 0, 0, 75});
	}

	DrawTexture(placement.border->data.sprite.texture, placement.x, placement.y, WHITE);
}

int placement_get_tile(Scene *scene) {
	return scene->tilemap.tiles[placement.gy][placement.gx];
}

bool placement_can_place() {
	int tile = placement_get_tile(game_get_scene());
	if (tile >= TILE_PATH_UP_RIGHT && tile <= TILE_PATH_RIGHT_UP) {
		return false;
	}

	return true;
}
