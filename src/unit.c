#include "unit.h"
#include "animation.h"
#include "assets.h"
#include "enemy.h"
#include "game.h"
#include "healthbar.h"
#include "scene_builder.h"
#include "text_input.h"
#include <math.h>
#include <stdio.h>

static Asset *warning;

Unit unit_new(UNIT_TYPE type, int x, int y) {

	Unit unit = {};

	unit.type = type;
	unit.selected = false;
	unit.x = x;
	unit.y = y;
	unit.asset = assets_get("assets/images/units.png");
	unit.sword_swipe = animation_new("assets/animations/sword-anim.png", 15);
	unit.hp = 100;
	unit.cost = unit_get_cost(type);
	unit.energy = 100;
	unit.target = NULL;

	unit.attack_cooldown = 60;
	unit.attack_timer = unit.attack_cooldown; 
	unit.can_attack = true;

	unit.text_input = text_input_new(game_get_wordlist()->easy);

	if (!warning) {
		warning = assets_get("assets/images/warning.png");
	}

	switch (type) {
		case UNIT_KNIGHT:
			unit.range = 2;
			unit.defense = 10;
			unit.damage = 15;
			break;
		case UNIT_VILLAGER:
			unit.range = 1;
			unit.defense = 5;
			unit.damage = 10;
			break;
	}

	unit.state = UNIT_STATE_IDLE;

	return unit;
}

void unit_update(Unit *unit) {

	unit->target = unit_enemy_in_range(unit);

	animation_update(&unit->sword_swipe);

	switch (unit->state) {
	
		case UNIT_STATE_IDLE:

			if (unit->target) {
				unit->state = UNIT_STATE_ATTACK;
			}

			break;

		case  UNIT_STATE_ATTACK:

			if (unit->target && unit->can_attack && unit->energy > 0) {

				animation_play(&unit->sword_swipe);
				remove_health(&unit->target->healthbar, unit->damage);
				unit->energy -= 10;
				unit->can_attack = false;
			}

			unit->attack_timer--;

			if (unit->attack_timer <= 0) {

				unit->attack_timer = unit->attack_cooldown;
				unit->can_attack = true;
			}

			if (unit->energy <= 0) {
				unit->state = UNIT_STATE_INACTIVE;
			}

			break;

		case UNIT_STATE_INACTIVE:

			if (!game_get_text_input_active()) {

				game_set_text_input_active(true);
				unit->state = UNIT_STATE_TYPE;
			}

			break;

		case UNIT_STATE_TYPE:

			if (text_input_update(&unit->text_input)) {
				unit->energy = 100;
				text_input_reset(&unit->text_input);
				game_set_text_input_active(false);
				unit->state = UNIT_STATE_IDLE;
			}

			break;
	}
}

Enemy* unit_enemy_in_range(Unit *unit) {

	Scene *scn = game_get_scene();

	for (int i = 0; i < scn->last_enemy; i++) {
	
		Enemy *enemy = scn->enemies[i];

		if (enemy->hp <= 0) continue;

		int cx = (unit->x * 16) + 8;
		int cy = (unit->y * 16) + 8;
		int rad = unit->range * 16;
		int dist = (enemy->x - cx)*(enemy->x - cx) + (enemy->y - cy)*(enemy->y - cy);

		if (dist <= rad * rad) {
			return enemy;
		}
	}

	return NULL;
}

void unit_draw(Unit *unit) {

	int ux = (unit->x * 16);
	int uy = (unit->y * 16);

	asset_draw_tile(unit->asset, unit->type, ux, uy);

	switch (unit->state) {
	
		case UNIT_STATE_IDLE:

			break;

		case UNIT_STATE_ATTACK:

			break;

		case UNIT_STATE_INACTIVE:

			DrawTexture(warning->data.sprite.texture, ux, uy - 16, WHITE);
			break;

		case UNIT_STATE_TYPE:

			text_input_draw(&unit->text_input, ux + 8, uy - 6);

			break;
	}

	animation_draw(&unit->sword_swipe, ux, uy + 8);

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

	if (unit->target) {

		DrawCircle(unit->target->x + 8, unit->target->y + 8, 8, RED);
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
