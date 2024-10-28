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

	Scene *scn = game_get_scene();
	Unit *unit = &scn->units[placement.gy][placement.gx];

	if (unit->asset) {
		placement.selected_unit = unit;
		if (unit->x == placement.gx && unit->y == placement.gy) {
			unit->selected = true;
		} 
	}

	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && placement_can_place()) {

		int type = GetRandomValue(UNIT_VILLAGER, UNIT_KNIGHT);

		int money = game_get_money();
		int cost = 0;
		switch (type) {
			case UNIT_VILLAGER:
				cost = 20; break;	
			case UNIT_KNIGHT:
				cost = 50; break;
		}

		if (money > cost) {
			scn->units[placement.gy][placement.gx] = unit_new(type, placement.gx, placement.gy);
			game_set_money(money - cost);
			printf("Added Unit!\n");
		}

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

	Scene *scn = game_get_scene();
	Unit *unit = &scn->units[placement.gy][placement.gx];

	if (unit->asset) {
		return false;
	}

	return true;
}
