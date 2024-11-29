#include "unit.h"
#include "assets.h"
#include "enemy.h"
#include "game.h"
#include "scene_builder.h"
#include <math.h>
#include <stdio.h>

Unit unit_new(UNIT_TYPE type, int x, int y) {
	Unit unit = {};

	unit.type = type;
	unit.selected = false;
	unit.x = x;
	unit.y = y;
	unit.asset = assets_get("assets/images/units.png");
	unit.range = 32;
	unit.hp = 100;
	unit.cost = unit_get_cost(type);

	unit.attack_cooldown = 60;
	unit.attack_timer = unit.attack_cooldown; 
	unit.can_attack = true;

	switch (type) {
		case UNIT_KNIGHT:
			unit.range = 2;
			unit.defense = 10;
			break;
		case UNIT_VILLAGER:
			unit.range = 1;
			unit.defense = 5;
			break;
	}

	return unit;
}

void unit_update(Unit *unit) {

	if (unit->can_attack && unit_is_enemy_in_range(unit)) {

		printf("Attacking!\n");
		unit->can_attack = false;
	}

	if (!unit->can_attack) {

		unit->attack_timer--;

		if (unit->attack_timer <= 0) {

			unit->attack_timer = unit->attack_cooldown;
			unit->can_attack = true;
		}
	}
}

bool unit_is_enemy_in_range(Unit *unit) {

	Scene *scn = game_get_scene();

	for (int i = 0; i < scn->last_enemy; i++) {
	
		Enemy *enemy = scn->enemies[i];

		int cx = (unit->x * 16) + 8;
		int cy = (unit->y * 16) + 8;
		int rad = unit->range * 16;
		int dist = (enemy->x - cx)*(enemy->x - cx) + (enemy->y - cy)*(enemy->y - cy);

		if (dist <= rad * rad) {
			printf("Enemy!\n");
			return true;
		}
	}

	return false;
}

void unit_draw(Unit *unit) {

	asset_draw_tile(unit->asset, unit->type, unit->x * 16, unit->y * 16);

	if (unit->selected) {
		Color color = (Color){255, 75, 75, 128};
		DrawCircleLines((unit->x * 16) + 8, (unit->y * 16) + 8, (unit->range * 16) + 8, color);

		char hp[128];
		char defense[128];
	
		sprintf(hp, "HP: %d", unit->hp);
		sprintf(defense, "Defense: %d", unit->defense);

		int hp_size = MeasureText(hp, 10);
		int defense_size = MeasureText(defense, 10);

		Vector2 hp_pos = {
			floor(((unit->x * 16) + 8) - ((float)hp_size / 2)),
			floor((unit->y * 16) - 16) - 10,
		};
		Vector2 defense_pos = {
			floor(((unit->x * 16) + 8) - ((float)defense_size / 2)),
			floor((unit->y * 16) - 16),
		};

		DrawText(hp, hp_pos.x, hp_pos.y, 10, WHITE);
		DrawText(defense, defense_pos.x, defense_pos.y, 10, WHITE);
	}
}

int unit_get_cost(UNIT_TYPE type) {

	switch (type) {
		case UNIT_VILLAGER:
			return 20;
		case UNIT_KNIGHT:
			return 50;
		default:
			return 0;
	}
}
