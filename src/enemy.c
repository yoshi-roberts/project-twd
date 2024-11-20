#include "enemy.h"
#include "assets.h"
#include "game.h"
#include "scene_path.h"
#include "healthbar.h"

Enemy enemy_new(ENEMY_TYPE type) {

	Enemy enemy = {};

	enemy.type = type;
	enemy.xdir = 0;
	enemy.ydir = 0;
	enemy.asset = assets_get("assets/images/enemies.png");

	Scene *scn = game_get_scene();
	enemy.next_waypoint_index = get_last_waypoint(scn);
	enemy_get_waypoint(&enemy);

	enemy.x = (int)enemy.next_waypoint.x;
	enemy.y = (int)enemy.next_waypoint.y;

	enemy.healthbar = create_healthbar((Vector2){enemy.x, enemy.y - 10}, 20, 4, 100);
	return enemy;
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

	update_healthbar_position(&enemy->healthbar, (Vector2){enemy->x, enemy->y - 10});
}

void enemy_draw(Enemy *enemy) {
	asset_draw_tile(enemy->asset, enemy->type, enemy->x, enemy->y - 4);
	draw_healthbar(&enemy->healthbar);
}

void enemy_get_waypoint(Enemy *enemy) {

	Scene *scn = game_get_scene();

	if (enemy->next_waypoint_index > 0) {
		enemy->next_waypoint_index--;
		enemy->next_waypoint = scn->tilemap_layer1.waypoints[enemy->next_waypoint_index];
	}
}
