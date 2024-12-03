#include "enemy.h"
#include "assets.h"
#include "game.h"
#include "scene_path.h"
#include "healthbar.h"
#include "tower.h"
#include "vec.h"
#include <stdio.h>

void enemy_new(ENEMY_TYPE type) {

	Scene *scn = game_get_scene();
	Enemy *enemy = vector_add_dst(&scn->enemies);

	enemy->index = vector_size(scn->enemies) - 1;

	switch (type) {
		case ENEMY_SLIME:
			enemy->hp = 20;
			enemy->damage = 5;
			break;
		case ENEMY_SPIDER:
			enemy->hp = 50;
			enemy->damage = 15;
			break;
		case ENEMY_SKELETON:
			enemy->hp = 35;
			enemy->damage = 20;
			break;
	}

	enemy->type = type;
	enemy->xdir = 0;
	enemy->ydir = 0;
	enemy->asset = assets_get("assets/images/enemies.png");
	enemy->active = true;

	enemy->next_waypoint_index = get_last_waypoint(scn);
	enemy_get_waypoint(enemy);

	enemy->x = (int)enemy->next_waypoint.x;
	enemy->y = (int)enemy->next_waypoint.y;

	enemy->healthbar = create_healthbar(&enemy->hp, 20, 3, RED);
	enemy = NULL;
}

void enemy_update(Enemy *enemy) {

	if (enemy->x == (int)enemy->next_waypoint.x && enemy->y == (int)enemy->next_waypoint.y) {
		enemy_get_waypoint(enemy);

		if ((int)enemy->next_waypoint.x == enemy->x) {
			enemy->xdir = 0;
		} else {
			enemy->xdir = ((int)enemy->next_waypoint.x > enemy->x) ? 1 : -1;
		}

		if ((int)enemy->next_waypoint.y == enemy->y) {
			enemy->ydir = 0;
		} else {
			enemy->ydir = ((int)enemy->next_waypoint.y > enemy->y) ? 1 : -1;
		}

	} else {
		enemy->x += enemy->xdir;
		enemy->y += enemy->ydir;
	}
}

void enemy_draw(Enemy *enemy) {

	asset_draw_tile(enemy->asset, enemy->type, enemy->x, enemy->y - 4);
	draw_healthbar(&enemy->healthbar, enemy->x + 8, enemy->y - 8, RED);
}

void enemy_get_waypoint(Enemy *enemy) {
	Scene *scn = game_get_scene();

	if (enemy->next_waypoint_index > 0) {

		enemy->next_waypoint_index--;
		enemy->next_waypoint = scn->tilemap_layer1.waypoints[enemy->next_waypoint_index];

	} else {

		tower_damage(enemy->damage);
		game_check_state(scn);
		enemy_damage(enemy, 100);
	}
}

void enemy_damage(Enemy *enemy, int amount) {

	enemy->hp -= amount;

	if (enemy->hp <= 0) {

		Scene *scn = game_get_scene();
		vector_remove(scn->enemies, enemy->index);
	}
}
