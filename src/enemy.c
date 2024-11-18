#include "enemy.h"
#include "../lib/raylib/src/raylib.h"

Enemy enemy_new(ENEMY_TYPE type, int x, int y) {

	Enemy enemy;

	enemy.type = type;
	enemy.x = x;
	enemy.y = y;

	return enemy;
}

void enemy_draw(Enemy *enemy) {

	DrawRectangle(enemy->x, enemy->y, 16, 16, RED);
}
