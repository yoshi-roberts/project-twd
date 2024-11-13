#include "placement.h"
#include "log.h"
#include "game.h"
#include "ui.h"
#include "unit.h"
#include <stdio.h>

static Placement placement = {};
static bool initialized = false;

void placement_init() {

	if (initialized) {
		log_error("Placement system already initialized.");
	}

	placement.state = PLACEMENT_IDLE;

	placement.x = 0;
	placement.y = 0;
	placement.gx = 0;
	placement.gy = 0;
	placement.current_tile = 0;

	placement.normal = (Color){255, 255, 255, 102};
	placement.border = assets_get("assets/images/placement-border.png");

	placement.build_menu = ui_panel_new(0, 0);

	ui_panel_add_label(&placement.build_menu, "Build Unit");
	ui_panel_add_button(&placement.build_menu, "Villager", placement_place_villager);
	ui_panel_add_button(&placement.build_menu, "Knight", placement_place_knight);
	ui_panel_add_button(&placement.build_menu, "Cancel", placement_place_cancel);

	initialized = true;
	log_info("Placement System Initialized.");
}

void placement_place_villager() {

	Scene *scn = game_get_scene();

	int money = game_get_money();
	int cost = 20;

	if (money > cost) {
		scn->units[placement.gy][placement.gx] = unit_new(UNIT_VILLAGER, placement.gx, placement.gy);
		game_set_money(money - cost);
	}

	placement.state = PLACEMENT_IDLE;
}

void placement_place_knight() {

	Scene *scn = game_get_scene();

	int money = game_get_money();
	int cost = 50;

	if (money > cost) {
		scn->units[placement.gy][placement.gx] = unit_new(UNIT_KNIGHT, placement.gx, placement.gy);
		game_set_money(money - cost);
	}

	placement.state = PLACEMENT_IDLE;
}

void placement_place_cancel() {
	placement.state = PLACEMENT_IDLE;
}

void placement_update(float mx, float my) {

	Scene *scn = game_get_scene();
	Unit *unit = &scn->units[placement.gy][placement.gx];

	switch (placement.state) {
		case PLACEMENT_IDLE:

			placement.x = (int)(mx / 16) * 16;	
			placement.y = (int)(my / 16) * 16;	
			placement.gx = (int)placement.x / 16;
			placement.gy = (int)placement.y / 16;

			if (unit->asset) {
				placement.selected_unit = unit;
				if (unit->x == placement.gx && unit->y == placement.gy) {
					unit->selected = true;
				} 
			}

			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && placement_can_place()) {

				placement.build_menu.x = placement.x + 17;
				placement.build_menu.y = placement.y;
				placement.state = PLACEMENT_BUILD;


			}
			break;

		case PLACEMENT_BUILD:
			break;
	}

}

void placement_draw() {

	int tile = placement_get_tile(game_get_scene());
	if (tile >= TILE_PATH_UP_RIGHT && tile <= TILE_PATH_RIGHT_UP) {
		DrawRectangle(placement.x, placement.y, 16, 16, (Color){255, 0, 0, 75});
	}

	DrawTexture(placement.border->data.sprite.texture, placement.x, placement.y, WHITE);

	switch (placement.state) {
		case PLACEMENT_IDLE:
			break;

		case PLACEMENT_BUILD:
			ui_panel_draw(&placement.build_menu);
			break;
	}

}

int placement_get_tile(Scene *scene) {
	return scene->tilemap_layer1.tiles[placement.gy][placement.gx];
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
