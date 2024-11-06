#ifndef ENEMIES_H
#define ENEMIES_H
#include "assets.h"

typedef enum {
	ENEMY_VILLAGER,
	ENEMY_KNIGHT,
} ENEMY_TYPE;

typedef struct {
	ENEMY_TYPE type;
	Asset *asset;
	int x; int y;
	int range;
	int hp;
	int defense;
	bool selected;
} Enemy;

void enemy_new(ENEMY_TYPE type, int x, int y);
void enemy_update(Enemy *unit);
void enemy_draw(Enemy *unit);

#endif // UNIT_H
