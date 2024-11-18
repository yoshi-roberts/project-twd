#include "enemy.h"

Enemy enemy_new(ENEMY_TYPE type, int x, int y) {

	Enemy enemy;

	enemy.type = type;
	enemy.x = x;
	enemy.y = y;

	return enemy;
}

void enemy_update(Enemy *enemy) {

}

void enemy_draw(Enemy *enemy) {

	DrawRectangle(enemy->x, enemy->y, 16, 16, RED);
}

void enemy_goto_waypoint(Enemy *enemy) {

}
